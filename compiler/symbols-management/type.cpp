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
				case VOID:
								return 0;
				}
}

TypeName getSymbolTypeFromString(string string_type)
{
				if (string_type == "int")
				{
								return INT_32;
				}
				if (string_type == "short")
				{
								return INT_32;
				}
				if (string_type == "int64_t")
				{
								return INT_64;
				}
				if (string_type == "long")
				{
								return INT_64;
				}
				if (string_type == "char")
				{
								return CHAR;
				}
				if (string_type == "void")
				{
								return VOID;
				}
				return INT_32;
}
