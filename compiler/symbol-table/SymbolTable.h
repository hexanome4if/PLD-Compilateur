#pragma once

#include "Context.h"


class SymbolTable {
public:
SymbolTable();
void openContext();
void closeContext();
Symbol* addSymbol(string name, string type, string value);
Symbol* getSymbol(string name);
bool symbolExists(string name);

private:
Context* currentContext;
int memoryAddress = 0;
};
