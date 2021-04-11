int main()
{
	int a[10000];
	a[6789] = 6;
	a[9876] = a[6789];
	return a[9876];
}
