#pragma once

#include "symbol-error.h"

class UndefinedSymbolWarn : public SymbolError
{
public:
	UndefinedSymbolWarn(string name) : SymbolError(name, nullptr, WARNING) {}

	string getMessage() override
	{
		return "Symbol " + symbolName + " not initialized";
	}
};
