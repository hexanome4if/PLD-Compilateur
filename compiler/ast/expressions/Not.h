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

private:
	Expr *expr1;
};
