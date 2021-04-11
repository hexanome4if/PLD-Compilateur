#pragma once

#include "../AbstractError.h"

class VoidFuncReturnError : public AbstractError
{
public:
	VoidFuncReturnError(string funcName) : AbstractError(ERROR), funcName(funcName) {}

	virtual string getMessage() override
	{
		return "The function " + funcName + " should not return";
	}

private:
	string funcName;
};
