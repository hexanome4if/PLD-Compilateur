#pragma once

#include <vector>
#include <iostream>
#include "abstract-error.h"

using namespace std;

class ErrorManager
{

public:
	ErrorManager() {}
	void registerError(AbstractError *error)
	{
		errors.push_back(error);
	}

	bool hasError()
	{
		for (int i = 0; i < errors.size(); ++i)
		{
			if (errors[i]->getSeverity() == ERROR)
				return true;
		}
		return false;
	}
	bool hasErrorOrWarning() { return errors.size() > 0; }
	void showAll(ostream &stream)
	{
		for (int i = 0; i < errors.size(); ++i)
		{
			auto error = errors[i];
			if (error->getSeverity() == ERROR)
			{
				stream << "\033[0;31m";
			}
			else if (error->getSeverity() == WARNING)
			{
				stream << "\033[0;33m";
			}
			stream << error->getMessage() << endl;
			stream << "\033[0m";
		}
	}

private:
	vector<AbstractError *> errors;
};
