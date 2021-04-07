#pragma once

#include "Expr.h"

class Not : public Expr
{
public:
	Not(Expr *e1) : Expr(NOT), expr1(e1) {}

    virtual void checkUsedSymbols(Context* context) override {
	    expr1->checkUsedSymbols(context);
	}

    virtual string getGuessedValue(Context* context, function<void(Expr*)> replaceWith) override { return "undefined"; }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override
    {
	    expr1->computeVarDependencies(varSymbol, context);
    }

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
