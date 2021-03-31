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
	vector<Node *> nodes;
private:
	

};
