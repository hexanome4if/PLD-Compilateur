#include "SymbolTable.h"


SymbolTable::SymbolTable() {
    currentContext = new Context(nullptr);
}

void SymbolTable::openContext() {
    currentContext = new Context(currentContext);
}

void SymbolTable::closeContext() {
    currentContext = currentContext->getParentContext();
}

bool SymbolTable::symbolExists(string name) {
    return currentContext->symbolExists(name);
}

Symbol* SymbolTable::addSymbol(string name, string type, string value) {
    return currentContext->addSymbol(name, type, value, memoryAddress = memoryAddress + 4);
}

Symbol * SymbolTable::getSymbol(string name) {
    return currentContext->getSymbol(name);
}