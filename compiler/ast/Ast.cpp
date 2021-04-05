#include "Ast.h"
#include "instructions/Node.h"
#include "../symbols-management/SymbolTable.h"
#include "../symbols-management/Context.h"

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

void Ast::removeUnusedSymbols(SymbolTable* symbolTable)
{
    symbolTable->reinitRun();
    Context* context = symbolTable->currentContext;
    int removed;
    do {
        removed = 0;
        vector<int> indexToRemove;
        for (int i = 0; i < nodes.size(); ++i)
        {
            removed += nodes[i]->removeUnusedSymbols([&indexToRemove, &i](Node* toRemove) {
                indexToRemove.push_back(i);
            }, context);
        }

        for(int i = 0; i < indexToRemove.size(); ++i)
        {
            nodes.erase(nodes.begin() + indexToRemove[i] - i);
        }
        checkUsedSymbols(symbolTable);
    } while(removed > 0);

}

void Ast::checkUsedSymbols(SymbolTable* symbolTable)
{
    symbolTable->reinitRun();
    symbolTable->reinitUsedSymbols();

    for (int i = 0; i < nodes.size(); ++i)
    {
        nodes[i]->checkUsedSymbols(nullptr);
    }
}