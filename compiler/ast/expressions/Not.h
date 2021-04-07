#pragma once

#include "Expr.h"

class Not : public Expr
{
public:
	Not(Expr *e1) : Expr(NOT), expr1(e1) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(";
		stream << " ! ";
		expr1->debug(stream, space);
		stream << ")";
	}

	Expr *getExpr() { return expr1; }
	virtual bool hasFunctionCall() override { return expr1->hasFunctionCall(); }

private:
	Expr *expr1;
};
