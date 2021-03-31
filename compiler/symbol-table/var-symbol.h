#pragma once

#include <string>
#include "Symbol.h"

using namespace std;

class VarSymbol : public Symbol
{
public:
	VarSymbol(string name, string varType) : Symbol(name, VARIABLE), varType(varType), isInitialized(false), isUsed(false) {}
	VarSymbol(string name, string varType, bool initialized) : Symbol(name, VARIABLE), varType(varType), isInitialized(initialized), isUsed(false) {}
	void initialized() { isInitialized = true; }
	void used() { isUsed = true; }
	string getVarType() {return varType;}
	bool isInitialized;
	bool isUsed;

private:
	string varType;
};
