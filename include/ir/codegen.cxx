#include "ast.h"	// Value *NumberExprAST::codegen()
#include "parser.h"	// LogError()

#include "llvm/ADT/APFloat.h"	// APFloat
#include "llvm/IR/Constants.h"	// ConstantFP
#include "llvm/IR/Function.h"	// Function
#include "llvm/IR/IRBuilder.h"	// IRBuilder
#include "llvm/IR/LLVMContext.h"	// LLVMContext
#include "llvm/IR/Module.h"	// Module
#include "llvm/IR/Value.h"	// Value, Type

#include <map>		// map
#include <memory>	// unique_ptr
#include <string>	// string
#include <vector>	// vector

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::Value *> NamedValues;

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
		return Builder.CreateUIToFP(L, llvm::Type::getDoubleTy(TheContext), "booltmp");
	default:
		return LogErrorV("invalid binary operator");
	}
}

llvm::Value *CallExprAST::codegen()
{
	// Lock up the name in the global module table
	llvm::Function *CalleeF = TheModule->getFunction(Callee);
	if (!CalleeF)
		return LogErrorV("Unknown function referenced");

	// If argument mismatch error.
	if (CalleeF->arg_size() != Args.size())
		return LogErrorV("Incorrect # arguments passed");

	std::vector<llvm::Value *> ArgsV;
	for (unsigned i = 0, e = Args.size(); i != e; ++i)
	{
		ArgsV.push_back(Args[i]->codegen());
		if (!ArgsV.back())	// check if the last argument is empty
			return nullptr;
	}

	return Builder.CreateCall(CalleeF, ArgsV, "calltmp");	// put call IR
}
