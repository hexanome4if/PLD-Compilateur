#pragma once

#include "symbol-error.h"

class UnusedSymbolWarn : public SymbolError
{
public:
	UnusedSymbolWarn(string name) : SymbolError(name, nullptr, WARNING) {}
	string getMessage() override
	{
		return "Unused symbol " + symbolName;
	}
};
