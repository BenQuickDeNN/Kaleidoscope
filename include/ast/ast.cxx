#include "llvm/IR/Function.h"	// function
#include "llvm/IR/LLVMContext.h"	// LLVMContext
#include "llvm/IR/Value.h"	// Value

#include <memory>	// unique_ptr
#include <string>	// string
#include <vector>	// vector

/// ExprAST - Base class for all expression nodes
class ExprAST
{
public:
	virtual ~ExprAST(){}			// Ϊʲô��������Ҫ���⻯
	virtual llvm::Value *codegen() = 0;	// ��������Ĵ������ɺ���
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST :public ExprAST
{
	double Val;
public:
	NumberExprAST(double Val) :Val(Val) {}
	virtual llvm::Value *codegen();
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST :public ExprAST
{
	std::string Name;

public:
	VariableExprAST(const std::string &Name) : Name(Name) {}
	virtual llvm::Value *codegen();
};

/// BinaryExperAST - Expression class for a binary operator
class BinaryExprAST :public ExprAST
{
	char Op;
	std::unique_ptr<ExprAST> LHS, RHS;

public:
	BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, 
		std::unique_ptr<ExprAST> RHS)
		: Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
	virtual llvm::Value *codegen();
};

/// CallExprAST - Expression class for function calls.
class CallExprAST :public ExprAST
{
	std::string Callee;
	std::vector<std::unique_ptr<ExprAST>> Args;

public:
	CallExprAST(const std::string &Callee,
		std::vector<std::unique_ptr<ExprAST>> Args)
		: Callee(Callee), Args(std::move(Args)) {}
	virtual llvm::Value *codegen();
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST
{
	std::string Name;
	std::vector<std::string> Args;

public:
	PrototypeAST(const std::string &name, std::vector<std::string> Args)
		:Name(name), Args(std::move(Args)) {}
	virtual llvm::Function *codegen();
	const std::string &getName() const { return Name; }
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST
{
	std::unique_ptr<PrototypeAST> Proto;
	std::unique_ptr<ExprAST> Body;

public:
	FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body)
		:Proto(std::move(Proto)), Body(std::move(Body)) {}
	virtual llvm::Function *codegen();
};
