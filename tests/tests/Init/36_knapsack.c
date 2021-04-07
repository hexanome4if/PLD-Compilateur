int main()
{
	int capacite = 24;
	int sac[25];
	sac[capacite] = 0;
	int i =1;
	while (capacite - i)
	{
		sac[i] = 0;
		i = i+1;
	}
	sac[0] = 1;
	int poids[3] = {3,5,2};
	int estRemplissable = 0;
	int j = 0;
	while (3-j)
	{
		i = poids[j];
		while (capacite - i)
		{
			if (sac[i - poids[j]] -1)
			{

			}else{
				sac[i] = 1;
			}
			i = i+1;
		}
		if (sac[capacite] - 1)
		{

		}else{
			estRemplissable = 1;
		}
		j = j+1;
	}

	int res;

	if (estRemplissable)
	{
		res = 1;
	}
	else
	{
		res = 0;
	}
	return res;
}
