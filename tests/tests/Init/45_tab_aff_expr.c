int main()
{
    int tab[3];
    tab[0] = 5*2+6;
    tab[1] = 2;
    tab[tab[1]] = 64;
    return tab[2];
}