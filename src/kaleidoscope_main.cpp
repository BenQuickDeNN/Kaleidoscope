#ifndef DRIVER_H
#include "driver.h"	// MainLoop()
#define DRIVER_H
#endif // !DRIVER_H
#ifndef LEXER_H
#include "lexer.h"	// gettok()
#define LEXER_H
#endif // !LEXER_H
#ifndef PARSER_H
#include "parser.h"	// BinopPrecedence
#define PARSER_H
#endif // !PARSER_H

#ifndef IOSTREAM
#include <iostream>	// std::count, std::endl
#define IOSTREAM
#endif // !IOSTREAM
#ifndef CSTDIO
#include <cstdio>	// fprintf()
#define CSTDIO
#endif // !STDIO_H


void initialize_binopPrecedence();
void test_driver();
void test_lexer();

int main()
{
	initialize_binopPrecedence();
	test_driver();
	//test_lexer();
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

void test_lexer()
{
	int tok = gettok();
	std::cout << "tok = " << tok << ", iden = " << IdentifierStr << ", val = " << NumVal << std::endl;
}