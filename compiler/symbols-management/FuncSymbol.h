#pragma once

#include <string>
#include "Symbol.h"

using namespace std;

class FuncSymbol : public Symbol
{
public:
	FuncSymbol(string name, string returnType) : Symbol(name, FUNCTION), returnType(returnType) {}

	void used() { isUsed = true; }

    virtual void reinitUsedSymbols() override
    {
	    if (name != "main")
        {
            isUsed = false;
        }
    }

	// Get
	bool getIsUsed() { return isUsed; }

private:
	string returnType;
	bool isUsed;
};
