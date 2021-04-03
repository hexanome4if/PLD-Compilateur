#pragma once

#include "../Expr.h"

class UnOp : public Expr
{
public:
	UnOp(Expr *e, Expr::Operation op) : Expr(UN_OP), expr(e), operation(op) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << (operation == NEGL ? "-" : "") << "(";
		expr->debug(stream, space);
		stream << ")";
	}

	// Get
	Expr *getExpr() { return expr; }

private:
	Expr *expr;
	Expr::Operation operation;
};
