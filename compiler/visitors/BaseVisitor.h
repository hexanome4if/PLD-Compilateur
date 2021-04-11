#pragma once

#include "antlr4-runtime.h"
#include "../antlr4-generated/ifccBaseVisitor.h"

#include "../error-management/ErrorManager.h"

class BaseVisitor : public ifccBaseVisitor
{
public:
	BaseVisitor() { this->errorManager = new ErrorManager(); }
	void throwError(AbstractError *error) { errorManager->registerError(error); }
	ErrorManager *getErrorManager() { return errorManager; }

private:
	ErrorManager *errorManager;
};
