#include "ast.h"

void Ast::addNode(Node *n)
{
	nodes.push_back(n);
}

void Ast::debug(ostream &stream)
{
	stream << "AST" << endl;
	for (int i = 0; i < nodes.size(); ++i)
	{
		nodes[i]->debug(stream, 1);
	}
}
