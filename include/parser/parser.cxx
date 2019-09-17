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