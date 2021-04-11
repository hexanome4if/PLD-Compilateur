#pragma once

#include "SymbolError.h"

class UndeclaredSymbolError : public SymbolError
{
public:
	UndeclaredSymbolError(string symbolName, antlr4::tree ::TerminalNode *context) : SymbolError(symbolName, context, ERROR) {}
	string getMessage() override
	{
		return "Undeclared symbol " + symbolName + " on " + getPositionInfos();
	}
};
