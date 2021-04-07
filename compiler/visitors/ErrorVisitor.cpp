#include "ErrorVisitor.h"

#include "../error-management/func/FuncDoesNotReturnError.h"
#include "../error-management/func/VoidFuncReturnError.h"

antlrcpp::Any ErrorVisitor::visitFunc(ifccParser::FuncContext *context)
{
	string funcType = context->TYPE()[0]->getText();
	currentFuncType = getSymbolTypeFromString(funcType);
	doesFunctionReturn = false;

	visitChildren(context);

	// Function return
	if (!doesFunctionReturn && currentFuncType != VOID)
	{
		auto funcName = context->NAME()[0];
		throwError(new FuncDoesNotReturnError(funcName->getText()));
	}
	else if (doesFunctionReturn && currentFuncType == VOID)
	{
		auto funcName = context->NAME()[0];
		throwError(new VoidFuncReturnError(funcName->getText()));
	}

	return nullptr;
}

antlrcpp::Any ErrorVisitor::visitFunc_return(ifccParser::Func_returnContext *context)
{
	doesFunctionReturn = true;
	return nullptr;
}
