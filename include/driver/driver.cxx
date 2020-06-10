/* дһ��������������parser��lexer */
#include "ir.h"	// TheModule, TheContext
#include "lexer.h"	// tok_eof
#include "parser.h"	// ParseDefinition(), CurTok, getNextToken()

#include "llvm/IR/Module.h"	// Module
#include "llvm/Support/raw_ostream.h"	// errs()

#include <cstdio>	// fprintf()

static void InitializeModuleAndPassManager()
{
	// Open a new Module
	TheModule = std::make_unique<llvm::Module>("my cool jit", TheContext);
}

static void HandleDefinition()
{
	if (auto FnAST = ParseDefinition())
	{
		if (auto *FnIR = FnAST->codegen())
		{
			//fprintf(stderr, "Parsed a function definition.\n");
			fprintf(stderr, "Read function definition:");
			FnIR->print(llvm::errs());
			fprintf(stderr, "\n");
		}
	}
	else
	{
		// Skip token for error recovery.
		getNextToken();
	}
}

static void HandleExtern()
{
	if (auto ProtoAST = ParseExtern())
	{
		if (auto *FnIR = ProtoAST->codegen())
		{
			//fprintf(stderr, "Parsed an extern\n");
			fprintf(stderr, "Read extern: ");
			FnIR->print(llvm::errs());
			fprintf(stderr, "\n");
		}
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
	if (auto FnAST = ParseTopLevelExpr())
	{
		//fprintf(stderr, "get FnAST in HandleTopLevelExpression()\r\n");
		if (auto *FnIR = FnAST->codegen())
		{
			//fprintf(stderr, "get FnIR in HandleTopLevelExpression\r\n");
			//fprintf(stderr, "Parsed a top-level expr\n");
			fprintf(stderr, "Read top-level expression:");
			FnIR->print(llvm::errs());
			fprintf(stderr, "\n");
		}
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