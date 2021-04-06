#pragma once

#include "../Expr.h"

class EqualCompare : public Expr
{
public:
	EqualCompare(Expr *e1, Expr *e2) : Expr(EQ_COMP), expr1(e1), expr2(e2) {}

    virtual void checkUsedSymbols(Context* context) override {
        expr1->checkUsedSymbols(context);
        expr2->checkUsedSymbols(context);
    }

    virtual string getGuessedValue(Context* context, function<void(Expr*)> replaceWith) override { return "undefined"; }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override
    {
        expr1->computeVarDependencies(varSymbol, context);
        expr2->computeVarDependencies(varSymbol, context);
    }

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(";
		expr1->debug(stream, space);
		stream << " == ";
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
