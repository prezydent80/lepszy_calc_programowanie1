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

int text_to_num(char bufor[], int i) {
      int liczba = 0;
      while (czy_cyfra(bufor[i]) == 1) {
            liczba = 10 * liczba + (bufor[i] - '0');
            i++;
      }
      return liczba;
}

int del_spaces(char bufor[], int i) {
      while (bufor[i] == ' ' || bufor[i] == '\n' || bufor[i] == '\r'|| bufor[i] == '\t') {
            i++;
      }
      return i;
}

int skip_num(char bufor[], int i) {
      while (czy_cyfra(bufor[i]) == 1) {
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
}

double sqrt(int numb) {
      if (numb < 0) {
            return -1;
      }
      if (numb == 0) {
            return 0;
      }

      double strzal = numb / 2;
      double pop_strzal = 0;

      for (int i = 0; i < 50; i++) {
            pop_strzal = strzal;
            strzal = (pop_strzal + (numb / pop_strzal)) / 2;
      }

      return strzal;
}


int main()
{
      char bufor[1024];
      read_from_stdin(bufor);
      int liczbaA;
      int liczbaB;
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
            printf("[%d]\n", liczbaA + liczbaB);
      else if (dzialanie == 2)
            printf("[%d]\n", liczbaA - liczbaB);
      else if (dzialanie == 3)
            printf("[%d]\n", liczbaA * liczbaB);
      else if (dzialanie == 4)
            printf("[%d]\n", liczbaA / liczbaB);

}
