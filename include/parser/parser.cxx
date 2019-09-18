#ifndef AST_H
#include "ast.h"	// ExprAST
#define AST_H
#endif // !AST_H
#ifndef LEXER_H
#include "lexer.h"	// gettok()
#define LEXER_H
#endif // !LEXER_H

#ifndef IOSTREAM
#include <iostream>	// std::count, std::endl
#define IOSTREAM
#endif // !IOSTREAM
#ifndef MAP
#include <map>
#define MAP
#endif // !MAP
#ifndef MEMORY
#include <memory>	// unique_ptr
#define MEMORY
#endif // !MEMORY_H
#ifndef CSTDIO
#include <cstdio>	// fprintf()
#define CSTDIO
#endif // !STDIO_H
#ifndef VECTOR
#include <vector>	// vector
#define VECTOR
#endif // !VECTOR


/// CurTok/getNextToken - Provide a simple token buffer. CurTok is the current
/// token the parser is looking at. getNextToken reads another token from the
/// lexer and updates CurTok with its results.

static int CurTok;
static int getNextToken()
{
	return CurTok = gettok(); // look one token ahead, L1ģʽ
}

/// LogError* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> LogError(const char *Str)
{
	fprintf(stderr, "LogError: %s\n", Str);
	return nullptr;
}
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str)
{
	LogError(Str);
	return nullptr;
}

/// numberexpr ::= number
static std::unique_ptr<ExprAST> ParseNumberExpr()
{
	auto Result = std::make_unique<NumberExprAST>(NumVal);
	getNextToken();	// consume the number
	return std::move(Result);
}

static std::unique_ptr<ExprAST> ParseExpression();
/// parenexpr ::= '(' expression ')'
static std::unique_ptr<ExprAST> ParseParenExpr()
{
	getNextToken();	// eat (.
	auto V = ParseExpression();
	if (!V)
		return nullptr;

	if (CurTok != ')')
		return LogError("expected ')'");
	getNextToken(); // eat ).
	return V;
}

/// identifierexpr
/// ::= identifier
/// ::= identifier '(' expression* ')'
static std::unique_ptr<ExprAST> ParseIdentifierExpr()
{
	std::string IdName = IdentifierStr;

	getNextToken();	// eat identifier.

	if (CurTok != '(')	// Simple variable ref
		return std::make_unique<VariableExprAST>(IdName);

	// Call.
	getNextToken();	// eat '('
	std::vector<std::unique_ptr<ExprAST>> Args;
	if (CurTok != ')')
	{
		while (true)
		{
			if (auto Arg = ParseExpression())
				Args.push_back(std::move(Arg));
			else
				return nullptr;

			if (CurTok == ')')
				break;

			if (CurTok != ',')
				return LogError("Expected ')' or ',' in argument list");
			getNextToken();
		}
	}

	// Eat the ')'
	getNextToken();

	return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

/// primary
///		::= identifierexpr
///		::= numberexpr
///		::= parenexpr
static std::unique_ptr<ExprAST> ParsePrimary()
{
	switch (CurTok)
	{
	case tok_identifier:
		return ParseIdentifierExpr();
	case tok_number:
		return ParseNumberExpr();
	case '(':
		return ParseParenExpr();
	default:
		//std::cout << "CurTok = " << CurTok << std::endl;
		return LogError("unknown token when expecting and expression");
	}
}

/// 定义运算符的优先级
/// BinopPrecedence - This holds the precedence for each binary operator that is
/// defined.
static std::map<char, int> BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence()
{
	if (!isascii(CurTok))
		return -1;

	// Make sure it's a declared binop.
	int TokPrec = BinopPrecedence[CurTok]; // 获取运算符优先级
	if (TokPrec <= 0) return -1;
	return TokPrec;
}

static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
	std::unique_ptr<ExprAST> LHS);
/// expression
///		::= primary binoprhs
///
static std::unique_ptr<ExprAST> ParseExpression()
{
	auto LHS = ParsePrimary();
	if (!LHS)
		return nullptr;

	return ParseBinOpRHS(0, std::move(LHS));
}

/// binoprhs
///		::= ('+' primary)*
static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
	std::unique_ptr<ExprAST> LHS)
{
	// If this is a binop, find its precedence.
	while (true)
	{
		int TokPrec = GetTokPrecedence();

		// If this is a binop that binds at least as tightly as the current binop
		// consume it, otherwise we are done
		if (TokPrec < ExprPrec)
			return LHS;

		// well this is a binop
		int BinOp = CurTok;
		getNextToken();	// eat binop

		// Parse the primary expression after the binary operator
		auto RHS = ParsePrimary();
		if (!RHS)
			return nullptr;

		// 如果下一个token的优先级比当前token的优先级更高，那么就把RHS当做LHS
		// 优先用右边两个token构造语法树节点
		int NextPrec = GetTokPrecedence();
		if (TokPrec < NextPrec)
		{
			RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
			if (!RHS)
				return nullptr;
		}

		// Merge LHS/RHS, generate AST node
		LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS),
			std::move(RHS));
	}
}

/// prototype
///		::= id '(' id* ')'
static std::unique_ptr<PrototypeAST> ParsePrototype()
{
	if (CurTok != tok_identifier)
		return LogErrorP("Expected function name in prototype");

	std::string FnName = IdentifierStr;
	getNextToken();

	if (CurTok != '(')
		return LogErrorP("Expected '(' in prototype");

	// Read the list of argument names.
	std::vector<std::string> ArgNames;
	while (getNextToken() == tok_identifier)
		ArgNames.push_back(IdentifierStr);
	if (CurTok != ')')
		return LogErrorP("Expected ')' in prototype");

	// success
	getNextToken();	// eat ')'

	return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}

/// definition ::= 'def' prototype expression
static std::unique_ptr<FunctionAST> ParseDefinition()
{
	getNextToken();		// eat def.
	auto Proto = ParsePrototype();
	if (!Proto) 
		return nullptr;

	if (auto E = ParseExpression())
		return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
	return nullptr;
}

/// external ::= 'extern' prototype
static std::unique_ptr<PrototypeAST> ParseExtern()
{
	getNextToken();		// eat extern.
	return ParsePrototype();
}

/// toplevelexpr ::= expression
static std::unique_ptr<FunctionAST> ParseTopLevelExpr()
{
	if (auto E = ParseExpression())
	{
		// Make an anonymous proto.
		auto Proto = std::make_unique<PrototypeAST>("__anon_expr", // 为什么这里填"__anon_expr"？
			std::vector<std::string>());
		return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
	}
	return nullptr;
}