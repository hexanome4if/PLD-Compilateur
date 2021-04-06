#pragma once

#include "../expressions/Expr.h"
#include "Instr.h"

class ArrAff : public Instr, public Expr
{
public:
	ArrAff(string arrName, Expr* index, Expr * ex) : Instr(Instr::ARRAFF), Expr(Expr::ARRAFF), arrName(arrName), indexExpr(index), expr(ex) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(" << arrName << "[" ;
        indexExpr->debug(stream, space);
        stream << "] = " ;;
		expr->debug(stream, space);
		stream << ")";
	}

	virtual bool hasFunctionCall() override { return (expr->hasFunctionCall() || indexExpr->hasFunctionCall()); }

    virtual string getGuessedValue(Context *context, function<void(Expr *)> replaceWith) override { return "undefined"; }

    virtual void calculateExpressions(Context *context) override
    {
        string val = expr->getGuessedValue(context, [this](Expr *rep) {
            this->expr = rep;
        });
        if (val != "undefined")
        {
            expr = new ConstExpr(val, getExprSymbolType());
        }
        val = indexExpr->getGuessedValue(context, [this](Expr* rep) {
            this->indexExpr = rep;
        });
        if (val != "undefined")
        {
            indexExpr = new ConstExpr(val, getExprSymbolType());
        }
    }

    virtual void resetVariables(Context *context) override {}

    virtual int removeUnusedSymbols(function<void(Node *)> remove, Context *context) override
    {
        VarSymbol *var = (VarSymbol *)context->getSymbol(arrName);
        if (!var->getIsUsed())
        {
            remove(this);
            return 1;
        }
        return 0;
    }

    virtual void computeVarDependencies(VarSymbol *varSymbol, Context *context) override
    {
        VarSymbol *var = (VarSymbol *)context->getSymbol(arrName);
        if (varSymbol != nullptr)
        {
            varSymbol->addDependency(var);
        }
        expr->computeVarDependencies(nullptr, context);
        indexExpr->computeVarDependencies(nullptr, context);
    }

    virtual void computeVarDependencies(Context *context) override
    {
        expr->computeVarDependencies(nullptr, context);
    }

    virtual void checkUsedSymbols(Context *context) override
    {
        expr->checkUsedSymbols(context);
        indexExpr->checkUsedSymbols(context);
    }

	// Get
	string getArrName() { return arrName; }
	Expr *getExpr() { return expr; }
    Expr *getIndexExpr() { return indexExpr; }

private:
	string arrName;
	Expr *expr;
    Expr *indexExpr;
};