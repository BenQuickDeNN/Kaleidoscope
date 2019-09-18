/* 写一个驱动，来控制parser和lexer */

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif // !STDIO_H


/// top ::= definition | external | expression | ';'
static void MainLoop()
{
	while (1)
	{
		fprintf(stderr, "ready> ");
	}
}