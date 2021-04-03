#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Node;

class Ast
{

public:
	Ast()
	{
	}
	void addNode(Node *n);
	void debug(ostream &stream);

	vector<Node *> getNodes() { return nodes; }

private:
	vector<Node *> nodes;
};
