#include "SymbolTable.h"


SymbolTable::SymbolTable() {
				currentContext = new Context(nullptr);
}

Context* SymbolTable::openContext() {
				currentContext = new Context(currentContext);
				return currentContext;
}

void SymbolTable::closeContext() {
				currentContext = currentContext->getParentContext();
}

bool SymbolTable::symbolExists(string name) {
				return currentContext->symbolExists(name);
}

Symbol* SymbolTable::addSymbol(string name, string type) {
				return currentContext->addSymbol(name, type);
}

Symbol * SymbolTable::getSymbol(string name) {
				return currentContext->getSymbol(name);
}

Symbol* SymbolTable::addTempSymbol(string type) {
				return currentContext->addSymbol(to_string(currentTemp++) + "_temp", type);
}
