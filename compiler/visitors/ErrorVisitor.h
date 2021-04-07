#pragma once

#include "antlr4-runtime.h"
#include "../antlr4-generated/ifccBaseVisitor.h"
#include "../symbols-management/type.h"
#include "BaseVisitor.h"

class ErrorVisitor : public BaseVisitor
{
public:
	antlrcpp::Any visitFunc(ifccParser::FuncContext *context) override;
	antlrcpp::Any visitFunc_return(ifccParser::Func_returnContext *context) override;

private:
	TypeName currentFuncType;
	bool doesFunctionReturn;
};
