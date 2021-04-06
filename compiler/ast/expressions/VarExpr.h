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

    virtual string getGuessedValue(Context* context, function<void(Expr*)> replaceWith) override
    {
	    VarSymbol* varSymbol = (VarSymbol*)context->getSymbol(varName);
	    string val = varSymbol->getValue();
	    if (varSymbol->getHasDependencyCycle())
        {
	        val = "undefined";
        }
	    return val;
    }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override
    {
	    if (varSymbol != nullptr)
        {
            VarSymbol* var = (VarSymbol*)context->getSymbol(varName);
            varSymbol->addDependency(var);
        }
    }

	string getVarName() { return varName; }

private:
	string varName;
};
