#include "ast.h"	// Value *NumberExprAST::codegen()
#include "parser.h"	// LogError()

#include "llvm/ADT/APFloat.h"	// APFloat
#include "llvm/IR/BasicBlock.h"	// BasicBlock
#include "llvm/IR/Constants.h"	// ConstantFP
#include "llvm/IR/DerivedTypes.h"	// FunctionType
#include "llvm/IR/Function.h"	// Function
#include "llvm/IR/IRBuilder.h"	// IRBuilder
#include "llvm/IR/LLVMContext.h"	// LLVMContext
#include "llvm/IR/Module.h"	// Module
#include "llvm/IR/Value.h"	// Value, Type
#include "llvm/IR/Verifier.h"	// verifyFunction()

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

	// �ж������
	switch (Op)
	{
	case '+':
		return Builder.CreateFAdd(L, R, "addtmp");	// L��R�ֱ��ǲ�������"addtmp"��LLVM IR��
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

llvm::Function *PrototypeAST::codegen()
{
	// Make the function type: double(double, double) etc.
	std::vector<llvm::Type *> Doubles(Args.size(), llvm::Type::getDoubleTy(TheContext));
	llvm::FunctionType *FT = 
		llvm::FunctionType::get(llvm::Type::getDoubleTy(TheContext), Doubles, false);
	
	llvm::Function *F =
		llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule.get());

	// Set names for all arguments.
	unsigned Idx = 0;
	for (auto &Arg : F->args())
		Arg.setName(Args[Idx++]);

	return F;
}

llvm::Function *FunctionAST::codegen()
{
	//fprintf(stderr, "go into *FunctionAST::codegen\r\n");
	// First, check for an existing function from a previous 'extern' declaration
	llvm::Function *TheFunction = TheModule->getFunction(Proto->getName());
	//fprintf(stderr, "get *TheFunction in *FunctionAST::codegen\r\n");
	if (!TheFunction)
		TheFunction = Proto->codegen();
	
	if (!TheFunction)
		return nullptr;
	//fprintf(stderr, "get *TheFunction after !TheFunction in *FunctionAST::codegen\r\n");
	
	// Create a new basic block to start insertion into.
	llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
	Builder.SetInsertPoint(BB);

	// Record the function arguments in the NamedValues map.
	NamedValues.clear();
	for (auto &Arg : TheFunction->args())
		NamedValues[Arg.getName()] = &Arg;

	if (llvm::Value *RetVal = Body->codegen())
	{
		// Finish off the function
		Builder.CreateRet(RetVal);

		// Validate the generated code, checking for consistency
		llvm::verifyFunction(*TheFunction);

		return TheFunction;
	}
	
	// Error reading body, remove function.
	TheFunction->eraseFromParent();
	return nullptr;
}
