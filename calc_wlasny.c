#include <stdio.h>

typedef struct {
	int typ; // 1 - wartosc, 2 - dzialanie
	double wartosc;
	int dzialanie;
} Token;

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

void pusz_liczb(double stos_liczb[], int *top_liczb, double liczba){
	stos_liczb[*top_liczb] = liczba;
	(*top_liczb)++;
}

double pop_liczb(double stos_liczb[], int *top_liczb) {
	(*top_liczb)--;
	return stos_liczb[*top_liczb];
}

void pusz_znak(char stos_znak[], int* top_znak, int znak) {
	stos_znak[*top_znak] = znak;
	(*top_znak)++;
}

char pop_znak(char stos_znak[], int* top_znak) {
	(*top_znak)--;
	return stos_znak[*top_znak];
}

int piorytet(char znak) {
	if(znak == '(')
		return 0;
	if (znak == '+' || znak == '-')
		return 1;
	if (znak == '*' || znak == '/')
		return 2;
	if (znak == '$' || znak == '^')
		return 3;

	return 0;
}


int main()
{
	char bufor[1024];
	Token token[100];
	Token ONP[100];

	int ONP_index = 0;
	int token_index = 0;
	double liczbaA;
	double liczbaB;
	int dzialanie;
	int i = 0;

	double stos_liczb[100];
	int top_liczb = 0;
	char stos_znak[100];
	int top_znak = 0;



	read_from_stdin(bufor);

	while (bufor[i] != 0) {
		i = del_spaces(bufor, i);

		if (bufor[i] == 0) {
			break;
		}

		if (czy_cyfra(bufor[i]) == 1 ||( bufor[i] == '-' && (token_index == 0 || (token[token_index - 1].typ == 2 && token[token_index].dzialanie != ')')))) {

			token[token_index].typ = 1;
			token[token_index].wartosc = text_to_num(bufor, i);

			i = skip_num(bufor, i);
			token_index++;
		}
		else if (bufor[i] == '+' || bufor[i] == '*' || bufor[i] == '/' || bufor[i] == '$' || bufor[i] == '^' || bufor[i] == '(' || bufor[i] == ')') {
			
			
			token[token_index].typ = 2;
			token[token_index].dzialanie = bufor[i];
			token_index++;
			i++;
			
		}
		else {
			i++;
		}
	}

	for (i = 0; i < token_index; i++) {
		if (token[i].typ == 2) {

			if (token[i].dzialanie == '(') {
				pusz_znak(stos_znak, &top_znak, token[i].dzialanie);
			}else if (token[i].dzialanie == ')') {
				while (stos_znak[top_znak - 1] != '(') {
					char zdjety_znak = pop_znak(stos_znak, &top_znak);

					ONP[ONP_index].typ = 2;
					ONP[ONP_index].dzialanie = zdjety_znak;
					ONP_index++;
				}
				char kosz = pop_znak(stos_znak, &top_znak);
			}
			else {

				while (top_znak > 0 && piorytet(stos_znak[top_znak - 1]) >= piorytet(token[i].dzialanie)) {
					char zdjety_znak = pop_znak(stos_znak, &top_znak);

					ONP[ONP_index].typ = 2;
					ONP[ONP_index].dzialanie = zdjety_znak;
					ONP_index++;

				}
				pusz_znak(stos_znak, &top_znak, token[i].dzialanie);
			}
		} else if (token[i].typ == 1) {
			ONP[ONP_index] = token[i];
			ONP_index++;
		}
	}

	while (top_znak != 0) {
		char zdjety_znak = pop_znak(stos_znak, &top_znak);
		ONP[ONP_index].typ = 2;
		ONP[ONP_index].dzialanie = zdjety_znak;
		ONP_index++;
	}

	for (i = 0; i < ONP_index; i++) {
		if (ONP[i].typ == 1) {
			pusz_liczb(stos_liczb, &top_liczb, ONP[i].wartosc);
		}
		else if (ONP[i].typ == 2) {	
			liczbaA = pop_liczb(stos_liczb, &top_liczb);
			
			if (ONP[i].dzialanie != '$') {
				liczbaB = pop_liczb(stos_liczb, &top_liczb);
			}


			double wynik;
			if (ONP[i].dzialanie == '+') {
				wynik = liczbaB + liczbaA;
			}
			else if (ONP[i].dzialanie == '-') {
				wynik = liczbaB - liczbaA;
			}
			else if (ONP[i].dzialanie == '*') {
				wynik = liczbaB * liczbaA;
			}
			else if (ONP[i].dzialanie == '/') {
				wynik = liczbaB / liczbaA;
			}
			else if (ONP[i].dzialanie == '$') {
				wynik = sqrt(liczbaA);
			}
			else if (ONP[i].dzialanie == '^') {
				wynik = potega(liczbaB, liczbaA);
			}
			pusz_liczb(stos_liczb, &top_liczb, wynik);
		}
	}
	printf("%.4f\n", stos_liczb[0]);

}
