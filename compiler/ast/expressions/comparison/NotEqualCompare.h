#pragma once

#include "../Expr.h"

class NotEqualCompare : public Expr
{
public:
	NotEqualCompare(Expr *e1, Expr *e2) : Expr(NEQ_COMP), expr1(e1), expr2(e2) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(";
		expr1->debug(stream, space);
		stream << " != ";
		expr2->debug(stream, space);
		stream << ")";
	}

	// Get
	Expr *getExpr1() { return expr1; }
	Expr *getExpr2() { return expr2; }

private:
	Expr *expr1;
	Expr *expr2;
};
