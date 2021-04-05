#pragma once

#include "Expr.h"
#include "../../symbols-management/VarSymbol.h"

class VarExpr : public Expr
{
public:
	VarExpr(string v) : Expr(VAR), varName(v) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "var " << varName;
	}

    virtual void checkUsedSymbols(Context* context) override
    {
	    VarSymbol* var = (VarSymbol*)context->getSymbol(varName);
	    var->used();
    }

	string getVarName() { return varName; }

private:
	string varName;
};
