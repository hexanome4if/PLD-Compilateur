
#pragma once

#include <string>

using namespace std;

typedef enum
{
	ERROR,
	WARNING
} ErrorSeverity;

class AbstractError
{

public:
	AbstractError(ErrorSeverity severity) : severity(severity) {}
	virtual string getMessage() = 0;
	ErrorSeverity getSeverity() { return severity; }

protected:
	ErrorSeverity severity;
};
