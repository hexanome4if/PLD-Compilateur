#pragma once

#include "antlr4-runtime.h"
#include "../AbstractError.h"
#include <sstream>

using namespace std;

class SymbolError : public AbstractError
{

public:
	SymbolError(string symbolName, antlr4::tree::TerminalNode *context, ErrorSeverity severity) : AbstractError(severity), symbolName(symbolName), context(context) {}

protected:
	string symbolName;

	antlr4::tree::TerminalNode *context;

	string getPositionInfos()
	{
		stringstream ss;
		auto token = context->getSymbol();
		int line = token->getLine();

		return "line " + to_string(line) + " column " + to_string(token->getCharPositionInLine());
	}
};
