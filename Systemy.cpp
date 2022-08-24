/*
wejscie:
>> string (od 0 do 9 & od A do Z)
>> int (od 2 do 36)     system wejsciowy
>> int (od 2 do 36)     system wyjsciowy

wyjscie:
<< string
*/
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;
char tablica[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int BASE = 1000000000; /* podstawa */
const int DIGS = 9; /* liczba cyfr dziesietnych kazdej cyfry w zapisie
                         przy powyzszej podstawie */
const int LEN = 10000; /* stala dlugosc liczb */

struct liczba
{
    int t[LEN];
    int l; /* faktyczna dlugosc liczby */
};
void czytaj(liczba &x)
{
    char s[LEN * DIGS + 1];
    scanf("%s", s); /* czytamy lancuch - zakladamy, ze nie ma zer wiodacych */
    /* Ustalamy dlugosc liczby */
    int j = strlen(s); /* pozycja w lancuchu s */
    if (j % DIGS == 0)
        x.l = j / DIGS;
    else
        x.l = j / DIGS + 1;
    j--;
    for (int i = 0; i < x.l; i++)
    {
        /* ustalamy i-ta cyfre */
        x.t[i] = 0;
        for (int k = max(0, j - DIGS + 1); k <= j; k++)
            x.t[i] = 10 * x.t[i] + (s[k] - '0');
        j -= DIGS;
    }
}
void wypisz(liczba x)
{
    printf("%d", x.t[x.l - 1]);
    for (int i = x.l - 2; i >= 0; i--)
        printf("%0*d", DIGS, x.t[i]);
}
liczba operator+ (liczba x, liczba y)
{
    liczba z; /* wynik */
    /* Do dlugosci mniejszej z liczb: */
    z.l = min(x.l, y.l);
    int c = 0; /* na poczatek zerowy bit przeniesienia */
    for (int i = 0; i < z.l; i++)
    {
        z.t[i] = (x.t[i] + y.t[i] + c) % BASE;
        c = (x.t[i] + y.t[i] + c) / BASE;
    }
    /* Jezeli liczba x jest dluzsza: */
    while (z.l < x.l)
    {
        z.t[z.l] = (x.t[z.l] + c) % BASE;
        c = (x.t[z.l] + c) / BASE;
        z.l++;
    }
    /* Jezeli liczba y jest dluzsza: */
    while (z.l < y.l)
    {
        z.t[z.l] = (y.t[z.l] + c) % BASE;
        c = (y.t[z.l] + c) / BASE;
        z.l++;
    }
    /* Jezeli pozostalo jakies przeniesienie (to c=1): */
    if (c > 0)
    {
        z.t[z.l] = c;
        z.l++;
    }
    return z;
  }
liczba operator- (liczba x, liczba y)
{
    liczba z; /* wynik */
    z.l = x.l;
    int c = 0; /* nie ma pozyczki na poczatek */
    for (int i = 0; i < x.l; i++)
    {
        if (i < y.l) /* odjemnik sie jeszcze nie skonczyl */
            z.t[i] = x.t[i] - y.t[i] + c;
        else /* odjemnik sie skonczyl */
            z.t[i] = x.t[i] + c;
        if (z.t[i] < 0) /* musimy pozyczyc */
        {
            z.t[i] += BASE;
            c = -1;
        }
        else
            c = 0;
    }
    /* Ucinamy ewentualne zera wiodace */
    while (z.l > 1 && z.t[z.l - 1] == 0)
        z.l--;
    return z;
  }
int operator% (liczba x, int y)
{
    long long z = (long long)(x.t[x.l - 1]) % y;
    for (int i = x.l - 2; i >= 0; i--)
        z = (z * BASE + x.t[i]) % y;
    return int(z);
}
liczba operator/ (liczba x, int y)
{
    liczba z;
    int c = 0; /* przeniesienie */
    z.l = x.l;
    for (int i = x.l - 1; i >= 0; i--)
    {
        z.t[i] = int(((long long)(c) * BASE + (long long)x.t[i]) / y);
        c = int(((long long)(c) * BASE + (long long)x.t[i]) % y);
    }
    /* Usuwamy ewentualne nowopowstale zera wiodace */
    while (z.l > 1 && z.t[z.l - 1] == 0)
        z.l--;
    return z;
}
liczba operator* (liczba x, int y)
{
    liczba z;
    z.l = x.l;
    int c = 0;
    for (int i = 0; i < x.l; i++)
    {
        z.t[i] = int(((long long)(x.t[i]) * y + c) % BASE);
        c = int(((long long)(x.t[i]) * y + c) / BASE);
    }
    while (c > 0)
    {
        z.t[z.l] = c % BASE;
        c /= BASE;
        z.l++;
    }
    return z;
}
bool operator< (liczba x, liczba y)
{
    if (x.l < y.l)
        return true;
    if (x.l > y.l)
        return false;
    int i = x.l - 1;
    while (i >= 0 && x.t[i] == y.t[i])
        i--;
    if (i < 0)
        return false;
    if (x.t[i] < y.t[i])
        return true;
    return false;
}
bool operator> (liczba x, liczba y)
{
    return y < x;
}
bool operator== (liczba x, liczba y)
{
    return !(x < y) && !(y < x);
}

string zamien(liczba l,int system)
{
    string wyjscie;
    string str_tmp;

    while(l.t[0] != 0 || l.l != 1)
    {
        str_tmp += tablica[l % system];
        l = l / system;
    }
    for(int i = str_tmp.size() - 1;i >= 0; i--)
        wyjscie += str_tmp[i];
    return wyjscie;
}
int af(char a, int b)
{
    int x = 0;
    while(a != tablica[x])x++;
    return x;
}
int main()
{
    liczba suma;
    suma.l=1;
    suma.t[0]=0;

    int x1, x3;
    string a;
    cin >> a;									//liczba
    cin >> x1; 									//z jakiego systemu (od 2 do 36)
    liczba suma1;
    suma1.l=1;
    suma1.t[0]=1;
    for(int x = 0; x < a.size(); x++)           //obliczanie wartosci liczby w systemie dziesietnym
    {
        suma = suma + suma1 * af(a[a.size() - 1 - x], x1);
        suma1 = suma1 * x1;
    }
    cin >> x3; // = 3;							//na jaki system (od 2 do 36)
    cout << zamien(suma, x3) << endl;
    return 0;
}
