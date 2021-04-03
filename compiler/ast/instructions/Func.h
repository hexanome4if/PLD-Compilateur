#pragma once

#include "Node.h"
#include "Block.h"
#include "../../type.h"

class Func : public Node
{
public:
	Func(TypeName t, string n, Block *b) : Node(FUNCTION), type(t), name(n), block(b) {}

	void addParam(string p) { params.push_back(p); }

	void addInstr(Instr *i) { block->addInstr(i); }

	virtual void debug(ostream &stream, int space) override
	{
		showSpaces(stream, space);
		stream << "Function " << name << endl;
		block->debug(stream, ++space);
	}

	// Get
	string getName() { return name; }
	Block *getBlock() { return block; }
	vector<string> getParams() { return params; }

private:
	TypeName type;
	string name;
	vector<string> params;
	Block *block;
};
