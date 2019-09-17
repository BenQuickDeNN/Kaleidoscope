#include "lexer.h"
#include <iostream>

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