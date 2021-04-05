#pragma once

#include "../Expr.h"

class LogicalAND : public Expr
{
public:
	LogicalAND(Expr *e1, Expr *e2) : Expr(LOGIC_AND), expr1(e1), expr2(e2) {}

    virtual void checkUsedSymbols(Context* context) override {
        expr1->checkUsedSymbols(context);
        expr2->checkUsedSymbols(context);
    }

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(";
		expr1->debug(stream, space);
		stream << " && ";
		expr2->debug(stream, space);
		stream << ")";
	}

	virtual bool hasFunctionCall() override { return expr1->hasFunctionCall() || expr2->hasFunctionCall(); }

	// Get
	Expr *getExpr1() { return expr1; }
	Expr *getExpr2() { return expr2; }

private:
	Expr *expr1;
	Expr *expr2;
};
