#pragma once

#include "Context.h"
#include "VarSymbol.h"

class SymbolTable
{
public:
	SymbolTable();
	Context *openContext();
	void closeContext();
	void addSymbol(Symbol *);
	Symbol *getSymbol(string name);
	bool symbolExists(string name, SymbolType symbolType);
	Context *getNextInnerContext();
	void reinitRun();
	void setCreationDone();
	Symbol *addTempSymbol(TypeName type);
	void setCurrentContext(Context *context);
	void assignMemoryAddresses();
	void reinitUsedSymbols();

	void findVariableDependencyCycle();

	Context *currentContext;

private:
	Context *rootContext;

	bool creationDone;
	int tempNumber;
};
