#include <stdio.h>

void read_from_stdin(char buf[]) {
	int znak;

	for (int i = 0; (znak = getchar()) != '\n'; buf[++i] = 0) {
		buf[i] = znak;
	}
}

int czy_cyfra(int znak) {
	return znak >= 48 && znak <= 57;
}

double text_to_num(char bufor[], int i) {
	double liczba = 0;
	int negative = 0;

	if (bufor[i] == '-') {
		negative = 1;
		i++;
	}
	while (czy_cyfra(bufor[i]) == 1) {
		liczba = 10 * liczba + (bufor[i] - '0');
		i++;
	}
	//sprawdzanie czy jest przecinek
	if (bufor[i] == '.') {
		i++;
		double multiplier = 1;
		while (czy_cyfra(bufor[i]) == 1){
			multiplier = multiplier / 10;
			liczba = liczba + ((bufor[i] - '0') * multiplier);
			i++;
		}
	}
	if (negative == 1) {
		liczba = -liczba;
	}

	return liczba;
}

int del_spaces(char bufor[], int i) {
	while (bufor[i] == ' ' || bufor[i] == '\n' || bufor[i] == '\r' || bufor[i] == '\t') {
		i++;
	}
	return i;
}

int skip_num(char bufor[], int i) {
	if (bufor[i] == '-') {
		i++;
	}

	while (czy_cyfra(bufor[i]) == 1 || bufor[i] == '.') {
		i++;
	}

	return i;
}


int znak_dzial(char bufor[], int i) {
	if (bufor[i] == '+') {
		i++;
		return 1;
	}
	if (bufor[i] == '-') {
		i++;
		return 2;
	}
	if (bufor[i] == '*') {
		i++;
		return 3;
	}
	if (bufor[i] == '/') {
		i++;
		return 4;
	}
	if (bufor[i] == '$') {
		i++;
		return 5;
	}
	if (bufor[i] == '^') {
		i++;
		return 6;
	}
}

double sqrt(double numb) {
	if (numb < 0) {
		return -1;
	}
	if (numb == 0) {
		return 0;
	}

	double strzal = numb / 2;
	double pop_strzal = 0;

	while (pop_strzal != strzal) {
		pop_strzal = strzal;
		strzal = (pop_strzal + (numb / pop_strzal)) / 2;
		printf("Strzal: %.20f\n", strzal);
	}
	return strzal;
}

double potega(double liczba, int wykladnik) {
	double wynik = 1;
	for (int i = 0; i < wykladnik; i++) {
		wynik *= liczba;
	}
	return wynik;
}


int main()
{
	char bufor[1024];
	read_from_stdin(bufor);
	double liczbaA;
	double liczbaB;
	int dzialanie;
	int i = 0;

	i = del_spaces(bufor, i);

	liczbaA = text_to_num(bufor, i);
	i = skip_num(bufor, i);
	i = del_spaces(bufor, i);

	dzialanie = znak_dzial(bufor, i);
	//sprawdzanie czy jest pierwiastek

	if (dzialanie == 5) {
		printf("[%.20f]\n", sqrt(liczbaA));
	}
	i++;

	i = del_spaces(bufor, i);
	liczbaB = text_to_num(bufor, i);


	if (dzialanie == 1)
		printf("[%.4f]\n", liczbaA + liczbaB);
	else if (dzialanie == 2)
		printf("[%.4f]\n", liczbaA - liczbaB);
	else if (dzialanie == 3)
		printf("[%.4f]\n", liczbaA * liczbaB);
	else if (dzialanie == 4)
		printf("[%.4f]\n", liczbaA / liczbaB);
	else if (dzialanie == 6)
		printf("[%.4f]\n", potega(liczbaA, liczbaB));

}
