#include "SymbolVisitor.h"
#include "../symbols-management/FuncSymbol.h"
#include "../symbols-management/VarSymbol.h"
#include "../error-management/symbol/VoidCannotBeUsedAsVarTypeError.h"

SymbolVisitor::SymbolVisitor(SymbolTable *symbolTable) : BaseVisitor()
{
	this->symbolTable = symbolTable;
}

antlrcpp::Any SymbolVisitor::visitFunc(ifccParser::FuncContext *context)
{
	vector<antlr4::tree::TerminalNode *> types = context->TYPE();
	vector<antlr4::tree::TerminalNode *> names = context->NAME();
	string functionType = types[0]->getText();
	string functionName = names[0]->getText();

	if (symbolTable->symbolExists(functionName, FUNCTION))
	{
		throwError(new AlreadyDeclaredSymbolError(functionName, names[0]));
		return nullptr;
	}

	FuncSymbol *funcSymbol = new FuncSymbol(functionName, functionType);
	if (functionName == "main")
	{
		funcSymbol->used();
	}
	symbolTable->addSymbol(funcSymbol);

	symbolTable->openContext();
	if (types.size() > 1)
	{
		for (int i = 1; i < types.size(); ++i)
		{
			if (symbolTable->symbolExists(names[i]->getText(), VARIABLE))
			{
				throwError(new AlreadyDeclaredSymbolError(names[i]->getText(), names[i]));
				return nullptr;
			}
			if (types[i]->getText() == "void")
			{
				throwError(new VoidCannotBeUsedAsVarTypeError(names[i]->getText(), types[i]));
				return nullptr;
			}
			funcSymbol->addParam(getSymbolTypeFromString(types[i]->getText()), names[i]->getText());
			symbolTable->addSymbol(new VarSymbol(names[i]->getText(), getSymbolTypeFromString(types[i]->getText())));
		}
	}

	visitChildren(context);

	symbolTable->closeContext();

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
			if (!symbol->getIsUsed())
			{
				throwError(new UnusedSymbolWarn(symbol->getName()));
			}
		}
		else if (symbols[i]->getSymbolType() == VARIABLE)
		{
			VarSymbol *symbol = (VarSymbol *)symbols[i];
			if (!symbol->getIsInitialized())
			{
				throwError(new UndefinedSymbolWarn(symbol->getName()));
			}
			if (!symbol->getIsUsed())
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
		throwError(new AlreadyDeclaredSymbolError(varName, context->NAME()));
		return nullptr;
	}
	if (varType == "void")
	{
		throwError(new VoidCannotBeUsedAsVarTypeError(varName, context->TYPE()));
		return nullptr;
	}

	symbolTable->addSymbol(new VarSymbol(varName, getSymbolTypeFromString(varType), context->expr() != nullptr));
	vector<ifccParser::VirgulenameContext *> virgulename = context->virgulename();
	vector<ifccParser::VirgulenameContext *>::iterator it;

	for (it = virgulename.begin(); it != virgulename.end(); ++it)
	{
		string varname = visit(*it);

		if (symbolTable->symbolExists(varname, VARIABLE))
		{
			throwError(new AlreadyDeclaredSymbolError(varName, (*it)->NAME()));
			return nullptr;
		}

		// Add the variable in the symbol table
		symbolTable->addSymbol(new VarSymbol(varname, getSymbolTypeFromString(varType), (*it)->expr() != nullptr));
	}

	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitVirgulename(ifccParser::VirgulenameContext *context)
{
	visitChildren(context);
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
		throwError(new AlreadyDeclaredSymbolError(funcName, context->NAME()));
		return nullptr;
	}

	FuncSymbol *symbol = (FuncSymbol *)symbolTable->getSymbol(funcName);
	symbol->used();

	visitChildren(context);

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

	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitArraydef(ifccParser::ArraydefContext *context)
{
	string arrType = context->TYPE()->getText();
	string arrName = context->NAME()->getText();
	int arrSize = stoi(context->CONST()->getText());

	if (symbolTable->symbolExists(arrName, VARIABLE))
	{
		throwError(new AlreadyDeclaredSymbolError(arrName, context->NAME()));
		return nullptr;
	}
	// Add the array in the symbol table
	symbolTable->addSymbol(new ArrSymbol(arrName, getSymbolTypeFromString(arrType), arrSize));
	return nullptr;
}

antlrcpp::Any SymbolVisitor::visitArraydefaff(ifccParser::ArraydefaffContext *context)
{
	string arrType = context->TYPE()->getText();
	string arrName = context->NAME()->getText();

	if (symbolTable->symbolExists(arrName, VARIABLE))
	{
		throwError(new AlreadyDeclaredSymbolError(arrName, context->NAME()));
		return nullptr;
	}

	if (context->CONST() != nullptr)
	{
		int arrSize = stoi(context->CONST()->getText());
		symbolTable->addSymbol(new ArrSymbol(arrName, getSymbolTypeFromString(arrType), arrSize));
	}
	else
	{
		if (context->arraycontent() != nullptr)
		{
			int arrSize = context->arraycontent()->expr().size();
			symbolTable->addSymbol(new ArrSymbol(arrName, getSymbolTypeFromString(arrType), arrSize));
		}
		else
		{
			symbolTable->addSymbol(new ArrSymbol(arrName, getSymbolTypeFromString(arrType), 0));
		}
	}

	ArrSymbol *symbol = (ArrSymbol *)symbolTable->getSymbol(arrName);
	symbol->initialized();

	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitArraycontent(ifccParser::ArraycontentContext *context)
{
	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitArrayaff(ifccParser::ArrayaffContext *context)
{
	string arrName = context->arrayaccess()->NAME()->getText();

	if (!symbolTable->symbolExists(arrName, VARIABLE))
	{
		throwError(new UndeclaredSymbolError(arrName, context->arrayaccess()->NAME()));
		return nullptr;
	}

	ArrSymbol *symbol = (ArrSymbol *)symbolTable->getSymbol(arrName);
	symbol->initialized();
	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitArrayexpr(ifccParser::ArrayexprContext *context)
{
	return visitChildren(context);
}

antlrcpp::Any SymbolVisitor::visitArrayaccess(ifccParser::ArrayaccessContext *context)
{
	string arrName = context->NAME()->getText();

	if (!symbolTable->symbolExists(arrName, VARIABLE))
	{
		throwError(new UndeclaredSymbolError(arrName, context->NAME()));
		return nullptr;
	}

	ArrSymbol *symbol = (ArrSymbol *)symbolTable->getSymbol(arrName);
	symbol->used();

	return visitChildren(context);
}

void postAnalysis()
{
}
