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
	int a = 65;
	int ret = a + func();
	f();

	int userInput = getchar();

	putchar(userInput);
	return 0;
}
