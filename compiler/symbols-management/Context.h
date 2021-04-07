#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "Symbol.h"

using namespace std;

class Context
{
public:
	Context(Context *parentContext) : parentContext(parentContext)
	{
		currentChild = 0;
	}
	bool symbolExists(string name, SymbolType symbolType);
	void addSymbol(Symbol *symbol);
	Symbol *getSymbol(string name);
	Context *getParentContext();
	vector<Symbol *> getAllSymbols();
	void addChildContext(Context *context);
	Context *getNextChild();
	void reinitRun();
	void assignMemoryAddresses(int nextAddress);

    void findVariableDependencyCycle();

	int getTotalContextSize();

    void reinitUsedSymbols();

	void debug(ostream &stream, int space);
	void showSpace(ostream &stream, int space);

private:
	map<string, Symbol *> symbols;
	Context *parentContext;
	vector<Context *> childrenContexts;
	int currentChild;
};
