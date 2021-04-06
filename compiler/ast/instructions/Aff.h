#pragma once

#include "../expressions/Expr.h"
#include "Instr.h"
#include "../../symbols-management/VarSymbol.h"
#include "../expressions/ConstExpr.h"

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

    virtual void computeVarDependencies(Context* context) override
    {
        VarSymbol* var = (VarSymbol*)context->getSymbol(varName);
        expr->computeVarDependencies(var, context);
    }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override
    {
        VarSymbol* var = (VarSymbol*)context->getSymbol(varName);
	    if (varSymbol != nullptr)
        {
            varSymbol->addDependency(var);
        }
	    expr->computeVarDependencies(var, context);
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

    virtual void resetVariables(Context* context) override
    {
        VarSymbol* var = (VarSymbol*)context->getSymbol(varName);
        var->setValue("undefined");
    }

    virtual void calculateExpressions(Context* context) override
    {
	    string val = expr->getGuessedValue(context, [this](Expr* rep) {
	        this->expr = rep;
	    });
        VarSymbol* varSymbol = (VarSymbol*)context->getSymbol(varName);
        varSymbol->setValue(val);
	    if (val != "undefined")
        {
	        expr = new ConstExpr(val);
        }
    }

    virtual string getGuessedValue(Context* context, function<void(Expr*)> replaceWith) override
    {
	    return expr->getGuessedValue(context, [this](Expr* rep){
	        this->expr = rep;
	    });
	}

	// Get
	string getVarName() { return varName; }
	Expr *getExpr() { return expr; }

private:
	string varName;
	Expr *expr;
};
