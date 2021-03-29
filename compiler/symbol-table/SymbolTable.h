#pragma once

#include "Context.h"


class SymbolTable {
public:
SymbolTable();
Context* openContext();
void closeContext();
Symbol* addSymbol(string name, string type);
Symbol* getSymbol(string name);
bool symbolExists(string name);
Symbol* addTempSymbol(string type);

private:
Context* currentContext;
int currentTemp = 0;
};
