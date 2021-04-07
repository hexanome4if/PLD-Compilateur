int g()
{
	int a;
	return 0;
}

int func(int a, int b, int c, int d, int e, int f)
{
				int t = 1;
				g();
				return a + b + c + t;
}

int main()
{
				int a = 5;

				int ret = func(5, 6, 7, 8, 9, 12);

				return ret + a;
}
