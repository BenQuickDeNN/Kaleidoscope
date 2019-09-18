/* дһ��������������parser��lexer */
#ifndef LEXER_H
#include "lexer.h"	// tok_eof
#define LEXER_H
#endif // !LEXER_H
#ifndef PARSER_H
#include "parser.h"	// ParseDefinition(), CurTok, getNextToken()
#define PARSER_H
#endif // !PARSER_H

#ifndef CSTDIO
#include <cstdio>	// fprintf()
#define CSTDIO
#endif // !STDIO_H

static void HandleDefinition()
{
	if (ParseDefinition())
	{
		fprintf(stderr, "Parsed a function definition.\n");
	}
	else
	{
		// Skip token for error recovery.
		getNextToken();
	}
}

static void HandleExtern()
{
	if (ParseExtern())
	{
		fprintf(stderr, "Parsed an extern\n");
	}
	else
	{
		// Skip token for error recovery.
		getNextToken();
	}
}

static void HandleTopLevelExpression()
{
	// Evaluate a top-level expression into an anonymous function.
	if (ParseTopLevelExpr())
	{
		fprintf(stderr, "Parsed a top-level expr\n");
	}
	else
	{
		// Skip token for error recovery.
		getNextToken();
	}
}

/// top ::= definition | external | expression | ';'
static void MainLoop()
{
	while (true)
	{
		fprintf(stderr, "ready> ");
		switch (CurTok)
		{
		case tok_eof:	// �ļ�����
			return;
		case ';':		// ignore top-level semicolons.
			getNextToken();
			break;
		case tok_def:
			HandleDefinition();
			break;
		case tok_extern:
			HandleExtern();
			break;
		default:
			HandleTopLevelExpression();
			break;
		}
		// ���IdentifierStr
		//IdentifierStr = "";
	}
}