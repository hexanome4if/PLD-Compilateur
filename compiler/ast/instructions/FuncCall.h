#pragma once

#include <vector>

#include "../expressions/Expr.h"
#include "Instr.h"

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

	virtual bool hasFunctionCall() override { return true; }

	// Get
	string getFuncName() { return funcName; }
	vector<Expr *> getParams() { return params; }

private:
	string funcName;
	vector<Expr *> params;
};
