#pragma once

#include "./Node.h"

class Instr : public Node
{
public:
	typedef enum
	{
		AFF,
		ARRAFF,
		RETURN,
		IF,
		WHILE,
		FOR,
		FUNCCALL
		// DECL,
		// DECLAFF,
	} Type;

	Instr(Type type) : Node(INSTRUCTION), instrType(type) {}

	virtual bool hasFunctionCall() = 0;
	virtual void resetVariables(Context* context) {}

    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) override { return 0; }

	// Get
	Type getInstrType() { return instrType; }

private:
	Type instrType;
};
