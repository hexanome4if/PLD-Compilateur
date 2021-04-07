#pragma once

#include <string>

using namespace std;

typedef enum
{
	FUNCTION,
	VARIABLE,
} SymbolType;

class Symbol
{
public:
	Symbol(string name, SymbolType symbolType) : name(name), symbolType(symbolType)
	{
	}

	string getName() { return name; }
	SymbolType getSymbolType() { return symbolType; }

	virtual int getMemorySize() { return 0; }

    virtual void reinitUsedSymbols() = 0;

protected:
	SymbolType symbolType;
	string name;
};
