#include<stdio.h>

void czytaj_z_wejscia(char bufor[])
{
	int znaczek;
	for (int i = 0; (znaczek = getchar()) != '\n'; bufor[++i] = 0)
	{
		bufor[i] = znaczek;
	}
}

int czy_jest_cyfra_na_wejsciu(int znaczek)
{
	return (znaczek >= '0') * (znaczek <= '9');
}

int tekst_na_liczbe(char bufor[], int i) {
	int znaczek = 0;
	while (czy_jest_cyfra_na_wejsciu(bufor[i]) == 1)
	{
		znaczek = znaczek * 10 + (bufor[i] - '0');
		i++;
	}
	return znaczek;
}
int pomin_liczby(char bufor[], int i)
{
	while (czy_jest_cyfra_na_wejsciu(bufor[i]) == 1) {
		i++;
	}
	return i;
}

int okresl_dzialanie(char bufor[], int i)
{
	if (bufor[i] == '+')
	{
		i++;
		return 1;
	}
	else if (bufor[i] == '-')
	{
		i++;
		return 2;
	}
	else if (bufor[i] == '*')
	{
		i++;
		return 3;
	}
	else if (bufor[i] == '/')
	{
		i++;
		return 4;
	}
}




void czytaj_linijke_z_wejscia(char bufor[])
{
	for (int i = 0, znaczek; (znaczek = getchar()) != '\n'; bufor[++i] = 0)
		bufor[i] = znaczek;
}

int skonsumuj_biale_znaki(char bufor[], int indeks)
{
	while (bufor[indeks] == ' ' || bufor[indeks] == '\n' || bufor[indeks] == '\r' || bufor[indeks] == '\t') {
		indeks++;
	}
	return indeks;
}
int main()
{
	char bufor[1024];
	czytaj_linijke_z_wejscia(bufor);
	int liczbaA;
	int liczbaB;
	int dzialanie;
	int i = 0;

	i = skonsumuj_biale_znaki(bufor, i);

	liczbaA = tekst_na_liczbe(bufor, i);
	i = pomin_liczby(bufor, i);
	i = skonsumuj_biale_znaki(bufor, i);

	dzialanie = okresl_dzialanie(bufor, i);
	i++;

	i = skonsumuj_biale_znaki(bufor, i);
	liczbaB = tekst_na_liczbe(bufor, i);

	if (!dzialanie) {
		fprintf(stderr, "Son I'm crine\n");
	}

	i = skonsumuj_biale_znaki(bufor, i);
	if (dzialanie == 1)
		printf("[%d]\n", liczbaA + liczbaB);
	else if (dzialanie == 2)
		printf("[%d]\n", liczbaA - liczbaB);
	else if (dzialanie == 3)
		printf("[%d]\n", liczbaA * liczbaB);
	else if (dzialanie == 4)
	{
		if (liczbaB != 0)
		{
			printf("%d\n", liczbaA / liczbaB);
		}
	}
}
