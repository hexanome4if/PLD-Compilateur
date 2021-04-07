char getLetter(int i)
{
	char alphabet[6] = {'a','b','c','d','e','f'};
	return alphabet[i];
}
int main()
{
				char res[2];
				res[0] = getLetter(0);
				res[1] = getLetter(4);
				char result = res[0];
				return result;
}

