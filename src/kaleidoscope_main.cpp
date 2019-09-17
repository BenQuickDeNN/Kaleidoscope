#ifndef LEXER_H
#include "lexer.h"	// gettok()
#define LEXER_H
#endif // !LEXER_H
#ifndef PARSER_H
#include "parser.h"
#define PARSER_H
#endif // !PARSER_H

#ifndef IOSTREAM
#include <iostream>	// std::count, std::endl
#define IOSTREAM
#endif // !IOSTREAM

void initialize_binopPrecedence();
void test_lexer();

int main()
{
	initialize_binopPrecedence();
	test_lexer();
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

void test_lexer()
{
	int tok = gettok();
	std::cout << "tok = " << tok << ", iden = " << IdentifierStr << ", val = " << NumVal << std::endl;
}