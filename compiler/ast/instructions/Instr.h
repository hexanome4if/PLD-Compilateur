#pragma once

#include "./Node.h"

class Instr : public Node
{
public:
	typedef enum
	{
		AFF,
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

	// Get
	Type getInstrType() { return instrType; }

private:
	Type instrType;
};