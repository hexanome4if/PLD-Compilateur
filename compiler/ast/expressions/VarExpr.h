#pragma once

#include "Expr.h"

class VarExpr : public Expr
{
public:
	VarExpr(string v) : Expr(VAR), varName(v) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "var " << varName;
	}

	string getVarName() { return varName; }

private:
	string varName;
};
