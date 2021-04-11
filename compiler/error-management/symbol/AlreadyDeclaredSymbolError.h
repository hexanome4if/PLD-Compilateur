

#pragma once

#include "SymbolError.h"

class AlreadyDeclaredSymbolError : public SymbolError
{
public:
	AlreadyDeclaredSymbolError(string symbolName, antlr4::tree::TerminalNode *context) : SymbolError(symbolName, context, ERROR) {}
	string getMessage() override
	{
		return "Symbol " + symbolName + " is already declared. At " + getPositionInfos();
	}
};
