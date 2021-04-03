#pragma once

#include "../Expr.h"

class BinOp : public Expr
{
public:
	BinOp(Expr *e1, Expr *e2, Expr::Operation op) : Expr(BIN_OP), expr1(e1), expr2(e2), operation(op) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(";
		expr1->debug(stream, space);
		stream << (operation == SUBS ? " - " : operation == ADD ? " + " : operation == MULT ? " * " : " / ");
		expr2->debug(stream, space);
		stream << ")";
	}

	virtual bool hasFunctionCall() override { return expr1->hasFunctionCall() || expr2->hasFunctionCall(); }

	// Get
	Expr *getExpr1() { return expr1; }
	Expr *getExpr2() { return expr2; }
	Expr::Operation getOperation() { return operation; }

private:
	Expr *expr1;
	Expr *expr2;
	Expr::Operation operation;
};
