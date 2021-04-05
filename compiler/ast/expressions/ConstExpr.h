#pragma once

#include <string>
#include "Expr.h"

using namespace std;

class ConstExpr : public Expr
{
public:
	ConstExpr(string v) : Expr(CONST), val(v) {}

	virtual void debug(ostream &stream, int space) override
	{
		stream << "const " << val;
	}

    virtual void checkUsedSymbols(Context* context) override {}

	// Get
	string getVal() { return val; }

private:
	string val;
};
