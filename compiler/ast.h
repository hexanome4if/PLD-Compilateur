#pragma once
#include <vector>
#include "instr.h"

using namespace std;

class Ast
{

public:
	Ast()
	{
	}
	void addNode(Node *n);
	void debug(ostream &stream);

private:
	vector<Node *> nodes;
};
