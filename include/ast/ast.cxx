#include <string> // string
#include <memory> // unique_ptr

/// ExprAST - Base class for all expression nodes
class ExprAST
{
public:
	virtual ~ExprAST(){}	// 为什么析构函数要虚拟化
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST :public ExprAST
{
	double Val;
public:
	NumberExprAST(double Vale) :Val(Val) {}
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST :public ExprAST
{
	std::string Name;

public:
	VariableExprAST(const std::string &Name) : Name(Name) {}
};

/// BinaryExperAST - Expression class for a binary operator
class BinaryExprAST :public ExprAST
{
	char Op;
	std::unique_ptr<ExprAST> LHS, RHS;

public:
	BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
		: Op(op), LHS(std::move(LHS)), RHS(std::move(RHS))
};