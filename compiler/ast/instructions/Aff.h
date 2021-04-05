#pragma once

#include "../expressions/Expr.h"
#include "Instr.h"
#include "../../symbols-management/VarSymbol.h"

class Aff : public Instr, public Expr
{
public:
	Aff(string varName, Expr *ex) : Instr(Instr::AFF), Expr(Expr::AFF), varName(varName), expr(ex) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(" << varName << " = ";
		expr->debug(stream, space);
		stream << ")";
	}

	virtual bool hasFunctionCall() override { return expr->hasFunctionCall(); }

    virtual void checkUsedSymbols(Context* context) override {
        expr->checkUsedSymbols(context);
    }

    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) override
    {
	    VarSymbol* var = (VarSymbol*)context->getSymbol(varName);
	    if (!var->getIsUsed())
        {
	        remove(this);
	        return 1;
        }
	    return 0;
    }

	// Get
	string getVarName() { return varName; }
	Expr *getExpr() { return expr; }

private:
	string varName;
	Expr *expr;
};
