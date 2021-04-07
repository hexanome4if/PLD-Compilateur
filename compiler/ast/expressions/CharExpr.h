#pragma once

#include "Expr.h"

class CharExpr : public Expr
{
public:
	CharExpr(string v) : Expr(CHAR), val(v) {}

    virtual void checkUsedSymbols(Context* context) override {}
    virtual string getGuessedValue(Context* context, function<void(Expr*)> replaceWith) override { return val; }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "charac " << val;
	}

	// Get
	string getVal() { return val; }
	char getChar() { return val[0]; }

private:
	string val;
};
