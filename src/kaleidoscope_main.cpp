#ifndef LEXER_H
#include "lexer.h"	// gettok()
#define LEXER_H
#endif // !LEXER_H
#ifndef IOSTREAM
#include <iostream>	// std::count, std::endl
#define IOSTREAM
#endif // !IOSTREAM

void test_lexer();

int main()
{
	test_lexer();
	return 0;
}

void test_lexer()
{
	int tok = gettok();
	std::cout << "tok = " << tok << ", iden = " << IdentifierStr << ", val = " << NumVal << std::endl;
}