#pragma once

#include <algorithm>
#include "Node.h"
#include "Instr.h"
#include "../../symbols-management/Context.h"

class Block : public Node
{
public:
	Block(Context *c) : Node(BLOCK), context(c) {}

	void addInstr(Instr *instr) { instrs.push_back(instr); }

	virtual void debug(ostream &stream, int space) override
	{
		showSpaces(stream, space);
		stream << "Block" << endl;
		context->debug(stream, space);
		for (int i = 0; i < instrs.size(); ++i)
		{
			showSpaces(stream, space + 1);
			instrs[i]->debug(stream, space);
			stream << endl;
		}
	}

	bool hasFunctionCall()
	{
		for (int i = 0; i < instrs.size(); ++i)
		{
			if (instrs[i]->hasFunctionCall())
			{
				return true;
			}
		}
		return false;
	}

	virtual void checkUsedSymbols(Context* context) override
    {
        for(int i = 0; i < instrs.size(); ++i)
        {
            instrs[i]->checkUsedSymbols(this->context);
        }
    }

    virtual void computeVarDependencies(Context* context) override
    {
        for(int i = 0; i < instrs.size(); ++i)
        {
            instrs[i]->computeVarDependencies(this->context);
        }
    }

    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) override
    {
	    vector<int> indexToRemove;
	    int res = 0;
	    for(int i = 0; i < instrs.size(); ++i)
        {
	        res += instrs[i]->removeUnusedSymbols([&indexToRemove, &i](Node* node) {
	            indexToRemove.push_back(i);
	            }, this->context);
        }
	    for(int i = 0; i < indexToRemove.size(); ++i)
        {
	        instrs.erase(instrs.begin() + indexToRemove[i] - i);
        }
	    return res;
    }

    virtual void calculateExpressions(Context* context) override
    {
	    for(int i = 0; i < instrs.size(); ++i)
        {
	        instrs[i]->calculateExpressions(this->context);
        }
        for (int i = 0; i < instrs.size(); ++i)
        {
            instrs[i]->resetVariables(this->context);
        }
    }

    void removeInstr(Instr* instr)
    {
	    remove(instrs.begin(), instrs.end(), instr);
    }

	// Get
	Context *getContext() { return context; }
	vector<Instr *> getInstrs() { return instrs; }

private:
	vector<Instr *> instrs;
	Context *context;
};
