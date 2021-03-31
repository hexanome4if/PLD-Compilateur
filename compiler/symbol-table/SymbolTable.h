#pragma once

#include "Context.h"

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

private:
	Context *rootContext;
	Context *currentContext;
	bool creationDone;
};
