#pragma once

#include <string>
#include <map>
#include "Symbol.h"

using namespace std;

class Context {
public:
    Context(Context* parentContext): parentContext(parentContext) {}
    bool symbolExists(string name);
    Symbol* addSymbol(string name, string type, string value, int memoryAddress);
    Symbol* getSymbol(string name);
    Context* getParentContext();

private:
    map<string, Symbol*> symbols;
    Context* parentContext;
};