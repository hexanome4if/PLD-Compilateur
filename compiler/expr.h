#ifndef EXPR_H
#define EXPR_H

#include <string>
#include "IR.h"

typedef enum
{
	ADD,
	MULT,
	DIV,
	SUBS,
	NEGL
} Operation;

class Expr
{
public:
	virtual void debug(ostream &stream, int space) {}
	virtual string buildIR(CFG* cfg) {return "buildExpr";}
};

class BinOp : public Expr
{
public:
	BinOp(Expr *e1, Expr *e2, Operation op) : expr1(e1), expr2(e2), operation(op)
	{
	}
	virtual string buildIR(CFG* cfg) override;
	virtual void debug(ostream &stream, int space) override
	{
		stream << "(";
		expr1->debug(stream, space);
		stream << (operation == SUBS ? " - " : operation == ADD ? " + " : operation == MULT ? " * " : " / ");
		expr2->debug(stream, space);
		stream << ")";
	}
	Expr *expr1;
	Expr *expr2;
	Operation operation;
};

class UnOp : public Expr
{
public:

	UnOp(Expr *e, Operation op) : expr(e), operation(op)
	{
	}
	virtual string buildIR(CFG* cfg) override;
	virtual void debug(ostream &stream, int space) override
	{
		stream << (operation == NEGL ? "-" : "") << "(";
		expr->debug(stream, space);
		stream << ")";
	}
	Expr *expr;
	Operation operation;

};

class ConstExpr : public Expr
{
public:
	ConstExpr(string v) : val(v)
	{
	}
	virtual string buildIR(CFG* cfg) override;
	virtual void debug(ostream &stream, int space) override
	{
		stream << "const " << val;
	}
	string val;
};

class VarExpr : public Expr
{
public:
	VarExpr(string v) : varName(v)
	{
	}
	virtual string buildIR(CFG* cfg) override;
	virtual void debug(ostream &stream, int space) override
	{
		stream << "var " << varName;
	}
	string varName;
};

#endif