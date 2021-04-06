#pragma once

#include "Node.h"
#include "Block.h"
#include "../../symbols-management/type.h"

class Func : public Node
{
public:
typedef struct
{
				string name;
				TypeName type;
} Param;

Func(TypeName t, string n, Block *b) : Node(FUNCTION), type(t), name(n), block(b) {
}

void addParam(TypeName type, string name) {
				params.push_back({name = name, type = type});
}

void addInstr(Instr *i) {
				block->addInstr(i);
}

virtual void debug(ostream &stream, int space) override
{
				showSpaces(stream, space);
				stream << "Function " << name << endl;
				block->debug(stream, ++space);
}

// Get
string getName() {
				return name;
}
Block *getBlock() {
				return block;
}
vector<Param> getParams() {
				return params;
}
TypeName getType() {
				return type;
}

private:
TypeName type;
string name;
vector<Param> params;
Block *block;
};
