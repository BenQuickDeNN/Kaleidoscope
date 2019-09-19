#include "ast.h"	// Value *NumberExprAST::codegen()
#include "parser.h"	// LogError()

#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Constants.h"	// ConstantFP
#include "llvm/IR/IRBuilder.h"	// IRBuilder
#include "llvm/IR/LLVMContext.h"	// LLVMContext
#include "llvm/IR/Value.h"	// Value

#include <memory>	// unique_ptr
#include <string>	// string

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<std::string, llvm::Value *> NamedValues;

llvm::Value *LogErrorV(const char *Str)
{
	LogError(Str);
	return nullptr;
}

llvm::Value *NumberExprAST::codegen()
{
	return llvm::ConstantFP::get(TheContext, llvm::APFloat(Val));
}

llvm::Value *VariableExprAST::codegen()
{
	// Lock this variable up in the function
	llvm::Value *V = NamedValues[Name];
	if (!V)
		LogErrorV("Unknown variable name");
	return V;
}

llvm::Value *BinaryExprAST::codegen()
{
	llvm::Value *L = LHS->codegen();
	llvm::Value *R = RHS->codegen();
	if (!L || !R)
		return nullptr;

	// 判断运算符
	switch (Op)
	{
	case '+':
		return Builder.CreateFAdd(L, R, "addtmp");	// L、R分别是操作数，"addtmp"是LLVM IR吗？
	case '-':
		return Builder.CreateFSub(L, R, "subtmp");
	case '*':
		return Builder.CreateFMul(L, R, "multmp");
	case '<':
		L = Builder.CreateFCmpULT(L, R, "cmptmp");	// less than
		// Convert bool 0/1 to double 0.0 or 1.0
		return Builder.CreateUIToFP(L, )
	default:
		return LogErrorV("invalid binary operator");
	}
}

