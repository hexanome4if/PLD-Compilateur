#pragma once

#include <string>
#include "Expr.h"

using namespace std;

class ConstExpr : public Expr
{
public:
    ConstExpr(string v, TypeName type) : Expr(CONST), constType(type), val(v) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "const " << val;
	}

    virtual void checkUsedSymbols(Context* context) override {}

    virtual string getGuessedValue(Context* context, function<void(Expr*)> replaceWith) override
    {
	    return val;
    }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override {}

	// Get
	string getVal() { return val; }
    TypeName getConstType() { return constType; }
    virtual TypeName getExprSymbolType() override { return constType; }

private:
	string val;
    TypeName constType;
};
