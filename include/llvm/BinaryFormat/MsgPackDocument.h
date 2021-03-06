//===-- MsgPackDocument.h - MsgPack Document --------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// This file declares a class that exposes a simple in-memory representation
/// of a document of MsgPack objects, that can be read from MsgPack, written to
/// MsgPack, and inspected and modified in memory. This is intended to be a
/// lighter-weight (in terms of memory allocations) replacement for
/// MsgPackTypes.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_BINARYFORMAT_MSGPACKDOCUMENT_H
#define LLVM_BINARYFORMAT_MSGPACKDOCUMENT_H

#include "llvm/BinaryFormat/MsgPackReader.h"
#include <map>

namespace llvm {
namespace msgpack {

class ArrayDocNode;
class Document;
class MapDocNode;

/// The kind of a DocNode and its owning Document.
struct KindAndDocument {
  Document *Doc;
  Type Kind;
};

/// A node in a MsgPack Document. This is a simple copyable and
/// passable-by-value type that does not own any memory.
class DocNode {
  friend Document;

public:
  typedef std::map<DocNode, DocNode> MapTy;
  typedef std::vector<DocNode> ArrayTy;

private:
  // Using KindAndDocument allows us to squeeze Kind and a pointer to the
  // owning Document into the same word. Having a pointer to the owning
  // Document makes the API of DocNode more convenient, and allows its use in
  // YAMLIO.
  const KindAndDocument *KindAndDoc;

protected:
  // The union of different values.
  union {
    int64_t Int;
    uint64_t UInt;
    bool Bool;
    double Float;
    StringRef Raw;
    ArrayTy *Array;
    MapTy *Map;
  };

public:
  DocNode() : KindAndDoc(nullptr) {}

  // Type methods
  bool isMap() const { return getKind() == Type::Map; }
  bool isArray() const { return getKind() == Type::Array; }
  bool isScalar() const { return !isMap() && !isArray(); }
  bool isString() const { return getKind() == Type::String; }

  // Accessors
  bool isEmpty() const { return !KindAndDoc; }
  Type getKind() const { return KindAndDoc->Kind; }
  Document *getDocument() const { return KindAndDoc->Doc; }

  int64_t &getInt() {
    assert(getKind() == Type::Int);
    return Int;
  }

  uint64_t &getUInt() {
    assert(getKind() == Type::UInt);
    return UInt;
  }

  bool &getBool() {
    assert(getKind() == Type::Boolean);
    return Bool;
  }

  double &getFloat() {
    assert(getKind() == Type::Float);
    return Float;
  }

  int64_t getInt() const {
    assert(getKind() == Type::Int);
    return Int;
  }

  uint64_t getUInt() const {
    assert(getKind() == Type::UInt);
    return UInt;
  }

  bool getBool() const {
    assert(getKind() == Type::Boolean);
    return Bool;
  }

  double getFloat() const {
    assert(getKind() == Type::Float);
    return Float;
  }

  StringRef getString() const {
    assert(getKind() == Type::String);
    return Raw;
  }

  /// Get an ArrayDocNode for an array node. If Convert, convert the node to an
  /// array node if necessary.
  ArrayDocNode &getArray(bool Convert = false) {
    if (getKind() != Type::Array) {
      assert(Convert);
      convertToArray();
    }
    // This could be a static_cast, except ArrayDocNode is a forward reference.
    return *reinterpret_cast<ArrayDocNode *>(this);
  }

  /// Get a MapDocNode for a map node. If Convert, convert the node to a map
  /// node if necessary.
  MapDocNode &getMap(bool Convert = false) {
    if (getKind() != Type::Map) {
      assert(Convert);
      convertToMap();
    }
    // This could be a static_cast, except MapDocNode is a forward reference.
    return *reinterpret_cast<MapDocNode *>(this);
  }

  /// Comparison operator, used for map keys.
  friend bool operator<(const DocNode &Lhs, const DocNode &Rhs) {
    // This has to cope with one or both of the nodes being default-constructed,
    // such that KindAndDoc is not set.
    if (Lhs.KindAndDoc != Rhs.KindAndDoc) {
      if (!Rhs.KindAndDoc)
        return false;
      if (!Lhs.KindAndDoc)
        return true;
      return (unsigned)Lhs.getKind() < (unsigned)Rhs.getKind();
    }
    switch (Lhs.getKind()) {
    case Type::Int:
      return Lhs.Int < Rhs.Int;
    case Type::UInt:
      return Lhs.UInt < Rhs.UInt;
    case Type::Nil:
      return false;
    case Type::Boolean:
      return Lhs.Bool < Rhs.Bool;
    case Type::Float:
      return Lhs.Float < Rhs.Float;
    case Type::String:
    case Type::Binary:
      return Lhs.Raw < Rhs.Raw;
    default:
      llvm_unreachable("bad map key type");
    }
  }

  /// Equality operator
  friend bool operator==(const DocNode &Lhs, const DocNode &Rhs) {
    return !(Lhs < Rhs) && !(Rhs < Lhs);
  }

  /// Convert this node to a string, assuming it is scalar.
  std::string toString() const;

  /// Convert the StringRef and use it to set this DocNode (assuming scalar). If
  /// it is a string, copy the string into the Document's strings list so we do
  /// not rely on S having a lifetime beyond this call. Tag is "" or a YAML tag.
  StringRef fromString(StringRef S, StringRef Tag = "");

private:
  // Private constructor setting KindAndDoc, used by methods in Document.
  DocNode(const KindAndDocument *KindAndDoc) : KindAndDoc(KindAndDoc) {}

  void convertToArray();
  void convertToMap();
};

/// A DocNode that is a map.
class MapDocNode : public DocNode {
public:
  MapDocNode() {}
  MapDocNode(DocNode &N) : DocNode(N) { assert(getKind() == Type::Map); }

  // Map access methods.
  size_t size() const { return Map->size(); }
  bool empty() const { return !size(); }
  MapTy::iterator begin() { return Map->begin(); }
  MapTy::iterator end() { return Map->end(); }
  MapTy::iterator find(DocNode Key) { return Map->find(Key); }
  MapTy::iterator find(StringRef Key);
  /// Member access. The string data must remain valid for the lifetime of the
  /// Document.
  DocNode &operator[](StringRef S);
  /// Member access.
  DocNode &operator[](DocNode Key);
};

/// A DocNode that is an array.
class ArrayDocNode : public DocNode {
public:
  ArrayDocNode() {}
  ArrayDocNode(DocNode &N) : DocNode(N) { assert(getKind() == Type::Array); }

  // Array access methods.
  size_t size() const { return Array->size(); }
  bool empty() const { return !size(); }
  ArrayTy::iterator begin() { return Array->begin(); }
  ArrayTy::iterator end() { return Array->end(); }
  void push_back(DocNode N) {
    assert(N.getDocument() == getDocument());
    Array->push_back(N);
  }

  /// Element access. This extends the array if necessary.
  DocNode &operator[](size_t Index);
};

/// Simple in-memory representation of a document of msgpack objects with
/// ability to find and create array and map elements.  Does not currently cope
/// with any extension types.
class Document {
  // Maps, arrays and strings used by nodes in the document. No attempt is made
  // to free unused ones.
  std::vector<std::unique_ptr<DocNode::MapTy>> Maps;
  std::vector<std::unique_ptr<DocNode::ArrayTy>> Arrays;
  std::vector<std::unique_ptr<char[]>> Strings;

  // The root node of the document.
  DocNode Root;

  // The KindAndDocument structs pointed to by nodes in the document.
  KindAndDocument KindAndDocs[size_t(Type::Extension) + 1];

  // Whether YAML output uses hex for UInt.
  bool HexMode = false;

public:
  Document() {
    clear();
    for (unsigned T = 0; T != size_t(Type::Extension) + 1; ++T)
      KindAndDocs[T] = {this, Type(T)};
  }

  /// Get ref to the document's root element.
  DocNode &getRoot() { return Root; }

  /// Restore the Document to an empty state.
  void clear() { getRoot() = getNode(); }

  /// Create a nil node associated with this Document.
  DocNode getNode() {
    auto N = DocNode(&KindAndDocs[size_t(Type::Nil)]);
    return N;
  }

  /// Create an Int node associated with this Document.
  DocNode getNode(int64_t V) {
    auto N = DocNode(&KindAndDocs[size_t(Type::Int)]);
    N.Int = V;
    return N;
  }

  /// Create an Int node associated with this Document.
  DocNode getNode(int V) {
    auto N = DocNode(&KindAndDocs[size_t(Type::Int)]);
    N.Int = V;
    return N;
  }

  /// Create a UInt node associated with this Document.
  DocNode getNode(uint64_t V) {
    auto N = DocNode(&KindAndDocs[size_t(Type::UInt)]);
    N.UInt = V;
    return N;
  }

  /// Create a UInt node associated with this Document.
  DocNode getNode(unsigned V) {
    auto N = DocNode(&KindAndDocs[size_t(Type::UInt)]);
    N.UInt = V;
    return N;
  }

  /// Create a Boolean node associated with this Document.
  DocNode getNode(bool V) {
    auto N = DocNode(&KindAndDocs[size_t(Type::Boolean)]);
    N.Bool = V;
    return N;
  }

  /// Create a Float node associated with this Document.
  DocNode getNode(double V) {
    auto N = DocNode(&KindAndDocs[size_t(Type::Float)]);
    N.Float = V;
    return N;
  }

  /// Create a String node associated with this Document. If !Copy, the passed
  /// string must remain valid for the lifetime of the Document.
  DocNode getNode(StringRef V, bool Copy = false) {
    if (Copy)
      V = addString(V);
    auto N = DocNode(&KindAndDocs[size_t(Type::String)]);
    N.Raw = V;
    return N;
  }

  /// Create a String node associated with this Document. If !Copy, the passed
  /// string must remain valid for the lifetime of the Document.
  DocNode getNode(const char *V, bool Copy = false) {
    return getNode(StringRef(V), Copy);
  }

  /// Create an empty Map node associated with this Document.
  MapDocNode getMapNode() {
    auto N = DocNode(&KindAndDocs[size_t(Type::Map)]);
    Maps.push_back(std::unique_ptr<DocNode::MapTy>(new DocNode::MapTy));
    N.Map = Maps.back().get();
    return N.getMap();
  }

  /// Create an empty Array node associated with this Document.
  ArrayDocNode getArrayNode() {
    auto N = DocNode(&KindAndDocs[size_t(Type::Array)]);
    Arrays.push_back(std::unique_ptr<DocNode::ArrayTy>(new DocNode::ArrayTy));
    N.Array = Arrays.back().get();
    return N.getArray();
  }

  /// Read a MsgPack document from a binary MsgPack blob.
  /// The blob data must remain valid for the lifetime of this Document (because
  /// a string object in the document contains a StringRef into the original
  /// blob).
  /// If Multi, then this sets root to an array and adds top-level objects to
  /// it. If !Multi, then it only reads a single top-level object, even if there
  /// are more, and sets root to that.
  /// Returns false if failed due to illegal format.
  bool readFromBlob(StringRef Blob, bool Multi);

  /// Write a MsgPack document to a binary MsgPack blob.
  void writeToBlob(std::string &Blob);

  /// Copy a string into the Document's strings list, and return the copy that
  /// is owned by the Document.
  StringRef addString(StringRef S) {
    Strings.push_back(std::unique_ptr<char[]>(new char[S.size()]));
    memcpy(&Strings.back()[0], S.data(), S.size());
    return StringRef(&Strings.back()[0], S.size());
  }

  /// Set whether YAML output uses hex for UInt. Default off.
  void setHexMode(bool Val = true) { HexMode = Val; }

  /// Get Hexmode flag.
  bool getHexMode() const { return HexMode; }

  /// Convert MsgPack Document to YAML text.
  void toYAML(raw_ostream &OS);

  /// Read YAML text into the MsgPack document. Returns false on failure.
  bool fromYAML(StringRef S);
};

} // namespace msgpack
} // namespace llvm

#endif // LLVM_BINARYFORMAT_MSGPACKDOCUMENT_H
