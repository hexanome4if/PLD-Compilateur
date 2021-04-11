#pragma once

#include "SymbolError.h"

class VoidCannotBeUsedAsVarTypeError : public SymbolError
{
public:
	VoidCannotBeUsedAsVarTypeError(string symbolName, antlr4::tree::TerminalNode *context) : SymbolError(symbolName, context, ERROR) {}
	string getMessage() override
	{
		return "Variable " + symbolName + " cannot use the type void. At " + getPositionInfos();
	}
};
