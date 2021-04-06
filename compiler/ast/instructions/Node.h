#pragma once

#include <string>
#include <iostream>
#include <functional>
#include "../../symbols-management/Context.h"

using namespace std;

class Node
{
public:
	typedef enum
	{
		FUNCTION,
		INSTRUCTION,
		BLOCK,
	} Type;

	Node(Type type) : nodeType(type) {}

	virtual void debug(ostream &stream, int space) {}

	void showSpaces(ostream &stream, int space)
	{
		for (int i = 0; i < space; ++i)
		{
			stream << "  ";
		}
	}

    virtual void checkUsedSymbols(Context* context) = 0;
    virtual void computeVarDependencies(Context* context) = 0;

	// Optimizations
    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) = 0;
    virtual void calculateExpressions(Context* context) = 0;

	// Get
	Type getNodeType() { return nodeType; }

private:
	Type nodeType;
};
