//===- DWARFDebugAranges.h --------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_DWARFDEBUGARANGES_H
#define LLVM_DEBUGINFO_DWARFDEBUGARANGES_H

#include "llvm/ADT/DenseSet.h"
#include "llvm/Support/DataExtractor.h"
#include <cstdint>
#include <vector>

namespace llvm {

class DWARFContext;

class DWARFDebugAranges {
public:
  void generate(DWARFContext *CTX);
  uint32_t findAddress(uint64_t Address) const;

private:
  void clear();
  void extract(DataExtractor DebugArangesData);

  /// Call appendRange multiple times and then call construct.
  void appendRange(uint32_t CUOffset, uint64_t LowPC, uint64_t HighPC);
  void construct();

  struct Range {
    explicit Range(uint64_t LowPC = -1ULL, uint64_t HighPC = -1ULL,
                   uint32_t CUOffset = -1U)
      : LowPC(LowPC), Length(HighPC - LowPC), CUOffset(CUOffset) {}

    void setHighPC(uint64_t HighPC) {
      if (HighPC == -1ULL || HighPC <= LowPC)
        Length = 0;
      else
        Length = HighPC - LowPC;
    }

    uint64_t HighPC() const {
      if (Length)
        return LowPC + Length;
      return -1ULL;
    }

    bool operator<(const Range &other) const {
      return LowPC < other.LowPC;
    }

    uint64_t LowPC; /// Start of address range.
    uint32_t Length; /// End of address range (not including this address).
    uint32_t CUOffset; /// Offset of the compile unit or die.
  };

  struct RangeEndpoint {
    uint64_t Address;
    uint32_t CUOffset;
    bool IsRangeStart;

    RangeEndpoint(uint64_t Address, uint32_t CUOffset, bool IsRangeStart)
        : Address(Address), CUOffset(CUOffset), IsRangeStart(IsRangeStart) {}

    bool operator<(const RangeEndpoint &Other) const {
      return Address < Other.Address;
    }
  };

  using RangeColl = std::vector<Range>;
  using RangeCollIterator = RangeColl::const_iterator;

  std::vector<RangeEndpoint> Endpoints;
  RangeColl Aranges;
  DenseSet<uint32_t> ParsedCUOffsets;
};

} // end namespace llvm

#endif // LLVM_DEBUGINFO_DWARFDEBUGARANGES_H
