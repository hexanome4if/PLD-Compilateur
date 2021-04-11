#pragma once

#include "SymbolError.h"

class UndefinedSymbolWarn : public SymbolError
{
public:
	UndefinedSymbolWarn(string name) : SymbolError(name, nullptr, WARNING) {}

	string getMessage() override
	{
		return "Symbol " + symbolName + " not initialized";
	}
};
