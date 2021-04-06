#pragma once

#include "../Expr.h"

class BinOp : public Expr
{
public:
	BinOp(Expr *e1, Expr *e2, Expr::Operation op) : Expr(BIN_OP), expr1(e1), expr2(e2), operation(op) {}

    virtual void checkUsedSymbols(Context* context) override {
        expr1->checkUsedSymbols(context);
        expr2->checkUsedSymbols(context);
    }

    virtual string getGuessedValue(Context* context) override
    {
	    string val1 = expr1->getGuessedValue(context);
	    string val2 = expr2->getGuessedValue(context);
	    if (val1 != "undefined" && val2 != "undefined")
        {
	        string v;
            switch(operation)
            {
                case Expr::Operation::ADD:
                    v = to_string(stoi(val1) + stoi(val2));
                    break;
                case Expr::Operation::DIV:
                    v = to_string(stoi(val1) / stoi(val2));
                    break;
                case Expr::Operation::MULT:
                    v = to_string(stoi(val1) * stoi(val2));
                    break;
                case Expr::Operation::SUBS:
                    v = to_string(stoi(val1) - stoi(val2));
                    break;
                default:
                    v = "undefined";
                    break;
            }
            return v;
        }
	    return "undefined";
    }

    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) override
    {
        expr1->computeVarDependencies(varSymbol, context);
        expr2->computeVarDependencies(varSymbol, context);
    }

	virtual void debug(ostream &stream, int space) override
	{
		stream << "(";
		expr1->debug(stream, space);
		stream << (operation == SUBS ? " - " : operation == ADD ? " + " : operation == MULT ? " * " : " / ");
		expr2->debug(stream, space);
		stream << ")";
	}

	virtual bool hasFunctionCall() override { return expr1->hasFunctionCall() || expr2->hasFunctionCall(); }

	// Get
	Expr *getExpr1() { return expr1; }
	Expr *getExpr2() { return expr2; }
	Expr::Operation getOperation() { return operation; }

private:
	Expr *expr1;
	Expr *expr2;
	Expr::Operation operation;
};
