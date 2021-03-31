#include <inttypes.h>
#include <stdio.h>
/*int func()
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
        char ch = 'c';
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
   }*/

/*int main() {
				int abw = 3 & 1; /* result = 1
				int obw = 5 | 2; /* result = 7
				int xbw = 7 ^ 5; /* result =  2
				return 0;
}*/

/*int main()
{
  int a = 3 < 5;
  int b = !a;
  int c = !(5 + 9);
  int d = !8;

  if ( a ){
    b = 2;
  }

  printf("/%d/%d/%d/%d", a, b, c, d);
  return 0;
}*/
int main()
{
  int a = 42;
	int b = 12;
	int c;
	int d = (a==42) && (b==12);
	if (a == 42 || b == 10) {
		c = 13;
	}
	while (a < 44 && b == 12) {
		c = 50;
	}
  return c;
}
