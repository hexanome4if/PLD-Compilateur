

#pragma once

#include "symbol-error.h"

class AlreadydeclaredSymbolError : public SymbolError
{
public:
	AlreadydeclaredSymbolError(string symbolName, antlr4::tree::TerminalNode *context) : SymbolError(symbolName, context, ERROR) {}
	string getMessage() override
	{
		return "Symbol " + symbolName + " is already declared. At " + getPositionInfos();
	}
};
