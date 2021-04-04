#pragma once

#include "../expressions/Expr.h"
#include "Instr.h"

class Ret : public Instr
{
public:
	Ret(Expr *ex) : Instr(RETURN), expr(ex) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "return ";
		expr->debug(stream, space);
	}

	virtual bool hasFunctionCall() override { return expr->hasFunctionCall(); }

	// Get
	Expr *getExpr() { return expr; }

private:
	Expr *expr;
};