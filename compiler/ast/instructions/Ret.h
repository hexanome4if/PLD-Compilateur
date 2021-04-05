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

    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) override { return 0; }

    virtual void checkUsedSymbols(Context* context) override {
	    expr->checkUsedSymbols(context);
	}

	// Get
	Expr *getExpr() { return expr; }

private:
	Expr *expr;
};
