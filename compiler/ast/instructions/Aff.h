#pragma once

#include "../expressions/Expr.h"
#include "Instr.h"

class Aff : public Instr, public Expr
{
public:
	Aff(string varName, Expr *ex) : Instr(Instr::AFF), Expr(Expr::AFF), varName(varName), expr(ex) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(" << varName << " = ";
		expr->debug(stream, space);
		stream << ")";
	}

	virtual bool hasFunctionCall() override { return expr->hasFunctionCall(); }

	// Get
	string getVarName() { return varName; }
	Expr *getExpr() { return expr; }

private:
	string varName;
	Expr *expr;
};
