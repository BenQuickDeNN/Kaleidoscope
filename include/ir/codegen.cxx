#ifndef AST_H
#include "ast.h"	// Value *NumberExprAST::codegen()
#define AST_H
#endif
#ifndef PARSER_H
#include "parser.h"	// LogError()
#define PARSER_H
#endif // !PARSER_H

#ifndef LLVM_ADT_APFLOAT_H
#include "llvm/ADT/APFloat.h"
#define LLVM_ADT_APFLOAT_H
#endif
#ifndef LLVM_IR_CONSTANTS_H
#include "llvm/IR/Constants.h"	// ConstantFP
#define LLVM_IR_CONSTANTS_H
#endif
#ifndef LLVM_IR_IRBUILDER_H
#include "llvm/IR/IRBuilder.h"	// IRBuilder
#define LLVM_IR_IRBUILDER_H
#endif // !IRBUILDER_H
#ifndef LLVM_IR_LLVMCONTEXT_H
#include "llvm/IR/LLVMContext.h"	// LLVMContext
#define LLVM_IR_LLVMCONTEXT_H
#endif // !LLVM_CONTEXT_H
#ifndef LLVM_IR_VALUE_H
#include "llvm/IR/Value.h"	// Value
#define LLVM_IR_VALUE_H
#endif

#ifndef MEMORY
#include <memory>	// unique_ptr
#define MEMORY
#endif // !MEMORY
#ifndef STRING
#include <string>	// string
#define STRING
#endif // !STRING

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<std::string, Value *> NamedValues;

Value *LogErrorV(const char *Str)
{
	LogError(Str);
	return nullptr;
}

Value *NumberExprAST::codegen()
{
	return ConstantFP::get(TheContext, APFloat(Val));
}

Value *VariableExprAST::codegen()
{
	// Lock this variable up in the function
	Value *V = NamedValues[Name];
	if (!V)
		LogErrorV("Unknown variable name");
	return V;
}

