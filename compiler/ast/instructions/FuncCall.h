#pragma once

#include <vector>

#include "../expressions/Expr.h"
#include "../../symbols-management/FuncSymbol.h"
#include "Instr.h"
#include "../expressions/ConstExpr.h"

using namespace std;

class FuncCall : public Instr, public Expr
{
public:
	FuncCall(string fn) : Instr(FUNCCALL), Expr(FUNC_CALL), funcName(fn) {}

	void addParam(Expr *expr) { params.push_back(expr); }

	virtual void debug(ostream &stream, int space) override
	{
		stream << "call to function " << funcName << " with parameters ";
		for (int i = 0; i < params.size(); ++i)
		{
			params[i]->debug(stream, space);
			stream << " | ";
		}
	}

    virtual void checkUsedSymbols(Context* context) override {
        FuncSymbol* funcSymbol = (FuncSymbol*)context->getSymbol(funcName);
        funcSymbol->used();
        for(int i = 0; i < params.size(); ++i)
        {
            params[i]->checkUsedSymbols(context);
        }
    }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override {}

    virtual void computeVarDependencies(Context* context) override
    {
        for (int i = 0; i < params.size(); ++i)
        {
            params[i]->computeVarDependencies(nullptr, context);
        }
    }

    virtual void calculateExpressions(Context* context) override
    {
        for (int i = 0; i < params.size(); ++i)
        {
            string val = params[i]->getGuessedValue(context);
            if (val == "undefined")
            {
                params[i] = new ConstExpr(val);
            }
        }
    }

    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) override { return 0; }

    virtual string getGuessedValue(Context* context) override { return "undefined"; }

	virtual bool hasFunctionCall() override { return true; }

	// Get
	string getFuncName() { return funcName; }
	vector<Expr *> getParams() { return params; }

private:
	string funcName;
	vector<Expr *> params;
};
