#include "ast.h"	// ExprAST
#include "lexer.h"	// gettok()

#define AST_H
#define LEXER_H

#ifndef MEMORY
#include <memory>	// unique_ptr
#define MEMORY
#endif // !MEMORY_H
#ifndef STDIO_H
#include <stdio.h>	// fprintf()
#define STDIO_H
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
		while (1)
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