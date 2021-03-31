#pragma once

#include <string>
#include "Symbol.h"

using namespace std;

class FuncSymbol : public Symbol
{
public:
	FuncSymbol(string name, string returnType) : Symbol(name, FUNCTION), returnType(returnType) {}

	void used() { isUsed = true; }
	bool isUsed;

private:
	string returnType;
};
