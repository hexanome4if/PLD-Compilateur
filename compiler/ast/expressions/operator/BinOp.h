#pragma once

#include "../Expr.h"
#include "../ConstExpr.h"

class BinOp : public Expr
{
public:
	BinOp(Expr *e1, Expr *e2, Expr::Operation op) : Expr(BIN_OP), expr1(e1), expr2(e2), operation(op) {}

    virtual void checkUsedSymbols(Context* context) override {
        expr1->checkUsedSymbols(context);
        expr2->checkUsedSymbols(context);
    }

    virtual string getGuessedValue(Context* context, function<void(Expr*)> replaceWith) override
    {
	    string val1 = expr1->getGuessedValue(context, [this](Expr* rep) {
	        this->expr1 = rep;
	    });
	    string val2 = expr2->getGuessedValue(context, [this](Expr* rep) {
	        this->expr2 = rep;
	    });
	    if (val1 != "undefined" && val2 != "undefined")
        {
	        string v;
	        int v1 = stoi(val1);
	        int v2 = stoi(val2);
            switch(operation)
            {
                case Expr::Operation::ADD:
                    if (v1 == 0)
                    {
                        replaceWith(expr2);
                    }
                    else if (v2 == 0)
                    {
                        replaceWith(expr1);
                    }
                    v = to_string(v1 + v2);
                    break;
                case Expr::Operation::DIV:
                    if (v1 == 0)
                    {
                        replaceWith(new ConstExpr("0"));
                    }
                    else if (v2 == 1)
                    {
                        replaceWith(expr1);
                    }
                    v = to_string(v1 / v2);
                    break;
                case Expr::Operation::MULT:
                    if (v1 == 1)
                    {
                        replaceWith(expr2);
                    }
                    else if (v2 == 1)
                    {
                        replaceWith(expr1);
                    }
                    if (v1 == 0 || v2 == 0)
                    {
                        replaceWith(new ConstExpr("0"));
                    }
                    v = to_string(v1 * v2);
                    break;
                case Expr::Operation::SUBS:
                    if (v2 == 0)
                    {
                        replaceWith(expr1);
                    }
                    v = to_string(v1 - v2);
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
