#pragma once

#include <string>
#include "Symbol.h"

using namespace std;

class FuncSymbol : public Symbol
{
public:
	FuncSymbol(string name, string returnType) : Symbol(name, FUNCTION), returnType(returnType) {}

	void used() { isUsed = true; }

	// Get
	bool getIsUsed() { return isUsed; }

private:
	string returnType;
	bool isUsed;
};
