#pragma once

#include <string>
#include "Symbol.h"
#include "type.h"

using namespace std;

class VarSymbol : public Symbol
{
public:
	// Constructors
	VarSymbol(string name, TypeName varType) : Symbol(name, VARIABLE), varType(varType), isInitialized(false), isUsed(false) {}

	VarSymbol(string name, TypeName varType, bool initialized) : Symbol(name, VARIABLE), varType(varType), isInitialized(initialized), isUsed(false) {}

	virtual int getMemorySize() override
	{
		return getMemorySizeFromType(varType);
	}

	// Setters
	void initialized() { isInitialized = true; }

	void used() { isUsed = true; }

	void setMemoryAddress(int memoryAddress) { this->memoryAddress = memoryAddress; }

	// Getters
	TypeName getVarType() { return varType; }

	int getMemoryAddress() { return memoryAddress; }

	bool getIsInitialized() { return isInitialized; }
	bool getIsUsed() { return isUsed; }

private:
	TypeName varType;
	int memoryAddress;
	bool isInitialized;
	bool isUsed;
};
