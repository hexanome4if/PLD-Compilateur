#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
	currentContext = new Context(nullptr);
	rootContext = currentContext;
	creationDone = false;
}

Context *SymbolTable::openContext()
{
	Context *newContext = new Context(currentContext);
	currentContext->addChildContext(newContext);
	currentContext = newContext;
	return currentContext;
}

Context *SymbolTable::getNextInnerContext()
{
	Context *context = currentContext->getNextChild();
	if (context != nullptr)
	{
		currentContext = context;
	}
	return context;
}

void SymbolTable::closeContext()
{
	currentContext = currentContext->getParentContext();
}

bool SymbolTable::symbolExists(string name, SymbolType symbolType)
{
	return currentContext->symbolExists(name, symbolType);
}

void SymbolTable::addSymbol(Symbol *symbol)
{
	currentContext->addSymbol(symbol);
}

Symbol *SymbolTable::getSymbol(string name)
{
	return currentContext->getSymbol(name);
}

void SymbolTable::reinitRun()
{
	currentContext = rootContext;
	currentContext->reinitRun();
}

void SymbolTable::setCreationDone()
{
	creationDone = true;
}
