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

private:
	SymbolType symbolType;
	string name;
};