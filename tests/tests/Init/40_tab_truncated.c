int main()
{
    int tab[3]={1,2,3,4,5,6};
    tab[1] = 2;
    tab[tab[0]] = 64;
    return tab[tab[0]];
}
