#pragma once

#include "../Expr.h"

class UnOp : public Expr
{
public:
	UnOp(Expr *e, Expr::Operation op) : Expr(UN_OP), expr(e), operation(op) {}

    virtual void checkUsedSymbols(Context* context) override {
        expr->checkUsedSymbols(context);
    }

	virtual void debug(ostream &stream, int space) override
	{
		stream << (operation == NEGL ? "-" : "") << "(";
		expr->debug(stream, space);
		stream << ")";
	}

	virtual bool hasFunctionCall() override { return expr->hasFunctionCall(); }

	// Get
	Expr *getExpr() { return expr; }

private:
	Expr *expr;
	Expr::Operation operation;
};
