#include "driver.h"	// MainLoop()
#include "ir.h"
#include "lexer.h"	// gettok()
#include "parser.h"	// BinopPrecedence

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
* @brief 初始化二元运算符的优先级
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

	// Run the main "interpreter loop" now
	MainLoop();
}