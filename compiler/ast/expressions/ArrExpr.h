#pragma once

#include "Expr.h"

class ArrExpr : public Expr
{
public:
	ArrExpr(string an, Expr* index, TypeName type) : Expr(ARRAFF), arrName(an), indexExpr(index), type(type) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "arr " << arrName << "[" ;
        indexExpr->debug(stream,space) ;
        stream << "]" ;
	}

    virtual bool hasFunctionCall() override { return indexExpr->hasFunctionCall(); }

    virtual void checkUsedSymbols(Context* context) override {
        VarSymbol* var = (VarSymbol*)context->getSymbol(arrName);
        var->used();
	    indexExpr->checkUsedSymbols(context);
    }

    virtual string getGuessedValue(Context* context, function<void(Expr*)> replaceWith) override { return "undefined"; }

    virtual TypeName getExprSymbolType() override { return type; }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override
    {
	    indexExpr->computeVarDependencies(varSymbol, context);
    }


    string getArrName() { return arrName; }
    Expr* getIndexExpr() {return indexExpr;}
    TypeName getType() { return type; }

private:
	string arrName;
    Expr* indexExpr;
    TypeName type;
};
