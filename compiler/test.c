#include <inttypes.h>
/*
int func()
{
	if (1)
	{
		int b = 3;
		return b;
	}
	return 2;
}

int main()
{
	int a = 5;

	if (a + 3)
	{
		int b, c;
		int d = a = b = 2;
		d = 2 + (a = 3);
	}
	else
	{
		func();
		int d = func();
	}

	return a + 10 - 5 * 2;
}
*/

int main()
{
	int a, b;
	int d = a = b = 2;
	return a + 10 - 5 * 2;
}
