#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Node;
class SymbolTable;

class Ast
{

public:
	Ast()
	{
	}
	void addNode(Node *n);
	void debug(ostream &stream);

	vector<Node *> getNodes() { return nodes; }

	// Optimizations
	void removeUnusedSymbols(SymbolTable* symbolTable);
	void calculateExpressions(SymbolTable* symbolTable);
	void checkUsedSymbols(SymbolTable* symbolTable);

private:
	vector<Node *> nodes;
};
