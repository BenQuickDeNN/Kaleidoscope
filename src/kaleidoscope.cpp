#include "driver.h"	// MainLoop()
#include "ir.h"
#include "lexer.h"	// gettok()
#include "parser.h"	// BinopPrecedence

#include "llvm/IR/Module.h"	// Module
#include "llvm/Support/raw_ostream.h"	// errs()

#include <cstdio>	// fprintf()

void initialize_binopPrecedence();
void test_driver();

int main()
{
	initialize_binopPrecedence();
	test_driver();
	return 0;
}

/**
* @brief ��ʼ����Ԫ����������ȼ�
*/
void initialize_binopPrecedence()
{
	// Install standard library operator
	// 1 is the lowest precedence
	BinopPrecedence['<'] = 10;
	BinopPrecedence['+'] = 20;
	BinopPrecedence['-'] = 20;
	BinopPrecedence['*'] = 40;
}

void test_driver()
{
	// Prime the first token.
	fprintf(stderr, "ready> ");
	getNextToken();

	// Make the module, which holds all the code.
	//TheModule = std::make_unique<llvm::Module>("my cool jit", TheContext);

	// Run the main "interpreter loop" now
	MainLoop();

	// Print out all of the generated code.
	TheModule->print(llvm::errs(), nullptr);
}