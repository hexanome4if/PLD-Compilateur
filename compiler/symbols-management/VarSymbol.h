#pragma once

#include <string>
#include "Symbol.h"

using namespace std;

class VarSymbol : public Symbol
{
public:
	// Constructors
	VarSymbol(string name, string varType) : Symbol(name, VARIABLE), varType(varType), isInitialized(false), isUsed(false) {}

	VarSymbol(string name, string varType, bool initialized) : Symbol(name, VARIABLE), varType(varType), isInitialized(initialized), isUsed(false) {}

	// Setters
	void initialized() { isInitialized = true; }

	void used() { isUsed = true; }

	void setMemoryAddress(int memoryAddress) { this->memoryAddress = memoryAddress; }

	// Getters
	string getVarType() { return varType; }

	int getMemoryAddress() { return memoryAddress; }

	int getMemorySize()
	{
		if (varType == "int32")
		{
			return 4;
		}
		return 8;
	}

	bool getIsInitialized() { return isInitialized; }
	bool getIsUsed() { return isUsed; }

private:
	string varType;
	int memoryAddress;
	bool isInitialized;
	bool isUsed;
};
