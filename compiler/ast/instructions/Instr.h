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

	// Get
	Type getInstrType() { return instrType; }

private:
	Type instrType;
};
