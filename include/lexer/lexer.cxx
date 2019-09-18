#include <cctype>	// isspace(), isalpha(), isalnum(), isdigit(),
#include <cstdio>	// getchar()
#include <cstdlib>	// strtod()
#include <string>	// string

#define CCTYPE
#define CSTDIO
#define CSTDLIB
#define STRING

// the lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things
enum Token
{
	tok_eof = -1,

	// commands
	tok_def = -2,
	tok_extern = -3,

	// primary
	tok_identifier = -4,
	tok_number = -5
};

static std::string IdentifierStr;	// Filled in if tok_identifier
static double NumVal;				// Filled in if tok_number

/// gettok - return the next token from standard input
static int gettok()
{
	// 清空IdentifierStr
	IdentifierStr = "";
	static int LastChar = ' ';
	// Skip any whitespace
	while (isspace(LastChar))
		LastChar = getchar();
	// letter
	if (isalpha(LastChar))
	{
		// identifier: [a-zA-Z][a-zA-Z0-9]*
		// check if the following characters are letter or number
		//IdentifierStr = "";
		//while (isalnum(LastChar = getchar()))
		do
			IdentifierStr += LastChar;
		while (isalnum(LastChar = getchar()));

		if (IdentifierStr == "def")
			return tok_def;
		if (IdentifierStr == "extern")
			return tok_extern;
		return tok_identifier;
	}
	// digit
	if (isdigit(LastChar) || LastChar == '.')
	{
		// Number: [0-9.]+
		std::string NumStr;
		do
		{
			NumStr += LastChar;
			LastChar = getchar();
		} while (isdigit(LastChar) || LastChar == '.'); // 条件判断第二条有点疑问，为什么还要判断小数点？
		NumVal = strtod(NumStr.c_str(), 0); // string to double
		return tok_number;
	}
	// comment
	if (LastChar == '#')
	{
		// comment until end of line.
		do
			LastChar = getchar();
		while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

		if (LastChar != EOF)
			return gettok();
	}
	// end of file. Don't eat the EOF.
	if (LastChar == EOF)
		return tok_eof;

	// Otherwise, just return the character as its ascii value.
	int ThisChar = LastChar;
	LastChar = getchar(); // 这句也很奇怪
	return ThisChar;
}