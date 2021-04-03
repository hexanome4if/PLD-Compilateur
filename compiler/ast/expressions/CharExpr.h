#pragma once

#include "Expr.h"

class CharExpr : public Expr
{
public:
	CharExpr(string v) : Expr(CHAR), val(v) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "charac " << val;
	}

private:
	string val;
};
