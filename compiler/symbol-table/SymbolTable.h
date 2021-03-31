#pragma once

#include "Context.h"
#include "var-symbol.h"

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
	Symbol *addTempSymbol(string type);
	void setCurrentContext(Context *context);

private:
	Context *rootContext;
	Context *currentContext;
	bool creationDone;
	int tempNumber;
};
