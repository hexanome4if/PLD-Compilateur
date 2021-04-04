#include <stdio.h>

int func()
{
	int a = 2;
}

void f()
{
	return 2;
}

int main()
{
	int a = 5;
	int ret = func();
	return ret + a;
}
