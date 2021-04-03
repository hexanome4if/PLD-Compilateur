#include "type.h"

int getMemorySizeFromType(TypeName type)
{
	switch (type)
	{
	case INT_64:
		return 8;
	case INT_32:
		return 4;
	case CHAR:
		return 1;
	}
}

TypeName getSymbolTypeFromString(string string_type)
{
	if (string_type == "int")
	{
		return INT_32;
	}
	if (string_type == "char")
	{
		return CHAR;
	}
	return INT_32;
}
