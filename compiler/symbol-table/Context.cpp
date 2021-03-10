#include "Context.h"


bool Context::symbolExists(string name) {
    if (symbols.find(name) != symbols.end()) {
        return true;
    }

    if (parentContext != nullptr) {
        return parentContext->symbolExists(name);
    }

    return false;
}

Symbol* Context::addSymbol(string name, string type, string value, int memoryAddress) {
    if (symbols.find(name) != symbols.end()) {
        return nullptr;
    }

    Symbol* newSymbol = new Symbol(name, type, value, memoryAddress);

    symbols[name] = newSymbol;
    return newSymbol;
}

Symbol * Context::getSymbol(string name) {
    if (symbols.find(name) != symbols.end()) {
        return symbols[name];
    }

    if (parentContext != nullptr) {
        return parentContext->getSymbol(name);
    }
    return nullptr;
}

Context * Context::getParentContext() {
    return parentContext;
}