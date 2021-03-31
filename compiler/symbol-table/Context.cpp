#include <algorithm>

#include "Context.h"
#include "var-symbol.h"

bool Context::symbolExists(string name, SymbolType symbolType)
{
	if (symbols.find(name) != symbols.end())
	{
		if (symbols[name]->getSymbolType() == symbolType)
		{
			return true;
		}
		return false;
	}

	if (parentContext != nullptr)
	{
		return parentContext->symbolExists(name, symbolType);
	}

	return false;
}

void Context::addSymbol(Symbol *symbol)
{
	if (symbols.find(symbol->getName()) != symbols.end())
	{
		return;
	}

	symbols[symbol->getName()] = symbol;
}

Symbol *Context::getSymbol(string name)
{
	if (symbols.find(name) != symbols.end())
	{
		return symbols[name];
	}

	if (parentContext != nullptr)
	{
		return parentContext->getSymbol(name);
	}
	return nullptr;
}

Context *Context::getParentContext()
{
	return parentContext;
}

vector<Symbol *> Context::getAllSymbols()
{
	vector<Symbol *> symbolsVect;
	transform(symbols.begin(), symbols.end(), back_inserter(symbolsVect), [](const map<string, Symbol *>::value_type &val) { return val.second; });
	return symbolsVect;
}

void Context::addChildContext(Context *context)
{
	childrenContexts.push_back(context);
}

Context *Context::getNextChild()
{
	if (currentChild < childrenContexts.size())
	{
		return childrenContexts[currentChild++];
	}
	return nullptr;
}

void Context::reinitRun()
{
	currentChild = 0;
	for (int i = 0; i < childrenContexts.size(); ++i)
	{
		childrenContexts[i]->reinitRun();
	}
}

void Context::debug(ostream &stream, int space)
{
	map<string, Symbol *>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); ++it)
	{
		showSpace(stream, space);
		stream << "var: " << it->second->getName() << endl;
	}
}
void Context::showSpace(ostream &stream, int space)
{
	for (int i = 0; i < space; ++i)
	{
		stream << "  ";
	}
}

void Context::assignMemoryAddresses(int nextAddress)
{
	map<string, Symbol *>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); ++it)
	{
		if (it->second->getSymbolType() == VARIABLE)
		{
			VarSymbol *var = (VarSymbol *)it->second;
			var->setMemoryAddress(nextAddress);
			nextAddress += var->getMemorySize();
		}
	}

	for (int i = 0; i < childrenContexts.size(); ++i)
	{
		childrenContexts[i]->assignMemoryAddresses(nextAddress);
	}
}
