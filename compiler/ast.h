#pragma once
#include <vector>
#include "instr.h"

using namespace std;

class Ast {

public:

Ast() {
}
void addNode(Node* n);

private:
vector<Node*> nodes;
};
