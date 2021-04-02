#include "symbol-visitor.h"
#include "symbol-table/func-symbol.h"
#include "symbol-table/var-symbol.h"

SymbolVisitor::SymbolVisitor(SymbolTable *symbolTable)
{
	this->symbolTable = symbolTable;
	this->errorManager = new ErrorManager();
}

antlrcpp::Any SymbolVisitor::visitFunc(ifccParser::FuncContext *context)
{
	vector<antlr4::tree::TerminalNode *> types = context->TYPE();
	vector<antlr4::tree::TerminalNode *> names = context->NAME();
	string functionType = types[0]->getText();
	string functionName = names[0]->getText();

	if (symbolTable->symbolExists(functionName, FUNCTION))
	{
		throwError(new AlreadydeclaredSymbolError(functionName, names[0]));
		return nullptr;
	}

	symbolTable->addSymbol(new FuncSymbol(functionName, functionType));

	if (types.size() > 1)
	{
		symbolTable->openContext();
		for (int i = 1; i < types.size(); ++i)
		{
			if (symbolTable->symbolExists(names[i]->getText(), VARIABLE))
			{
				throwError(new AlreadydeclaredSymbolError(names[i]->getText(), names[i]));
				return nullptr;
			}
		}
	}

	visitChildren(context);

	if (types.size() > 1)
	{
		symbolTable->closeContext();
	}

	return nullptr;
}

antlrcpp::Any SymbolVisitor::visitBlock(ifccParser::BlockContext *context)
{
	Context *ctx = symbolTable->openContext();

	visitChildren(context);

	// Check symbol usage
	vector<Symbol *> symbols = ctx->getAllSymbols();
	for (int i = 0; i < symbols.size(); ++i)
	{
		if (symbols[i]->getSymbolType() == FUNCTION)
		{
			FuncSymbol *symbol = (FuncSymbol *)symbols[i];
			if (!symbol->isUsed)
			{
				throwError(new UnusedSymbolWarn(symbol->getName()));
			}
		}
		else if (symbols[i]->getSymbolType() == VARIABLE)
		{
			VarSymbol *symbol = (VarSymbol *)symbols[i];
			if (!symbol->isInitialized)
			{
				throwError(new UndefinedSymbolWarn(symbol->getName()));
			}
			if (!symbol->isUsed)
			{
				throwError(new UnusedSymbolWarn(symbol->getName()));
			}
		}
	}
	symbolTable->closeContext();

	return nullptr;
}

antlrcpp::Any SymbolVisitor::visitVardefaff(ifccParser::VardefaffContext *context)
{
	string varType = context->TYPE()->getText();
	string varName = context->NAME()->getText();

	if (symbolTable->symbolExists(varName, VARIABLE))
	{
		throwError(new AlreadydeclaredSymbolError(varName, context->NAME()));
		return nullptr;
	}

	symbolTable->addSymbol(new VarSymbol(varName, varType, true));

	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitVardef(ifccParser::VardefContext *context)
{
	string varType = context->TYPE()->getText();
	string varName = context->NAME()->getText();

	if (symbolTable->symbolExists(varName, VARIABLE))
	{
		throwError(new AlreadydeclaredSymbolError(varName, context->NAME()));
		return nullptr;
	}

	// Add the variable in the symbol table
	symbolTable->addSymbol(new VarSymbol(varName, varType));

	vector<ifccParser::VirgulenameContext *> virgulename = context->virgulename();
	vector<ifccParser::VirgulenameContext *>::iterator it;

	for (it = virgulename.begin(); it != virgulename.end(); ++it)
	{
		string varname = visit(*it);

		if (symbolTable->symbolExists(varname, VARIABLE))
		{
			throwError(new AlreadydeclaredSymbolError(varName, (*it)->NAME()));
			return nullptr;
		}

		// Add the variable in the symbol table
		symbolTable->addSymbol(new VarSymbol(varname, varType));
	}

	return nullptr;
}

antlrcpp::Any SymbolVisitor::visitVirgulename(ifccParser::VirgulenameContext *context)
{
	return context->NAME()->getText();
}

antlrcpp::Any SymbolVisitor::visitVaraff(ifccParser::VaraffContext *context)
{
	string varName = context->NAME()->getText();

	if (!symbolTable->symbolExists(varName, VARIABLE))
	{
		throwError(new UndeclaredSymbolError(varName, context->NAME()));
		return nullptr;
	}

	VarSymbol *symbol = (VarSymbol *)symbolTable->getSymbol(varName);
	symbol->initialized();

	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitFunccall(ifccParser::FunccallContext *context)
{
	string funcName = context->NAME()->getText();

	if (!symbolTable->symbolExists(funcName, FUNCTION))
	{
		throwError(new AlreadydeclaredSymbolError(funcName, context->NAME()));
		return nullptr;
	}

	FuncSymbol *symbol = (FuncSymbol *)symbolTable->getSymbol(funcName);
	symbol->used();

	return nullptr;
}

antlrcpp::Any SymbolVisitor::visitExpr(ifccParser::ExprContext *context)
{
	vector<antlr4::tree::TerminalNode *> name = context->NAME();

	for (int i = 0; i < name.size(); ++i)
	{
		if (!symbolTable->symbolExists(name[i]->getText(), VARIABLE))
		{
			throwError(new UndeclaredSymbolError(name[i]->getText(), name[i]));
			return nullptr;
		}
		VarSymbol *symbol = (VarSymbol *)symbolTable->getSymbol(name[i]->getText());
		symbol->initialized();
		symbol->used();
	}

	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitName(ifccParser::NameContext *context)
{
	string varName = context->NAME()->getText();
	if (!symbolTable->symbolExists(varName, VARIABLE))
	{
		throwError(new UndeclaredSymbolError(varName, context->NAME()));
		return nullptr;
	}

	VarSymbol *symbol = (VarSymbol *)symbolTable->getSymbol(varName);
	symbol->used();

	return nullptr;
}

antlrcpp::Any SymbolVisitor::visitAffecsimple(ifccParser::AffecsimpleContext *context)
{
	string varName = context->NAME()->getText();
	if (!symbolTable->symbolExists(varName, VARIABLE))
	{
		throwError(new UndeclaredSymbolError(varName, context->NAME()));
		return nullptr;
	}

	VarSymbol *symbol = (VarSymbol *)symbolTable->getSymbol(varName);
	symbol->initialized();

	return nullptr;
}

void postAnalysis()
{
}

void SymbolVisitor::throwError(AbstractError *error)
{
	errorManager->registerError(error);
}

ErrorManager *SymbolVisitor::getErrorManager()
{
	return errorManager;
}
