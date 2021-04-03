#pragma once

#include <string>
#include <iostream>

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

	// Get
	Type getNodeType() { return nodeType; }

private:
	Type nodeType;
};
