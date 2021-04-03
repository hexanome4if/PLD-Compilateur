#pragma once

#include <string>

using namespace std;

typedef enum
{
	INT_64,
	INT_32,
	CHAR,
} TypeName;

int getMemorySizeFromType(TypeName type);

TypeName getSymbolTypeFromString(string string_type);
