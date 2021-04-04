#include <stdio.h>

int func()
{
	int a = 2; // Un autre commentaire
	// Un commentaire
	return a;
}

void f()
{
}

int main()
{
	int a = 5;
	int ret = func();
	return ret + a;
}
