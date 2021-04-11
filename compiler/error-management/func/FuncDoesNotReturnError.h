#pragma once

#include "../AbstractError.h"

class FuncDoesNotReturnError : public AbstractError
{
public:
	FuncDoesNotReturnError(string funcName) : AbstractError(ERROR), funcName(funcName) {}

	virtual string getMessage() override
	{
		return "The function " + funcName + " does not return";
	}

private:
	string funcName;
};
