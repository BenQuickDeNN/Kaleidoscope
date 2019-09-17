#include "lexer.h"
#include <iostream>


int main()
{
	//printf("tok = %d, iden = %s, val = %f\r\n", gettok(), IdentifierStr, NumVal);
	int tok = gettok();
	std::cout << "tok = " << tok << ", iden = " << IdentifierStr << ", val = " << NumVal << std::endl;
	return 0;
}