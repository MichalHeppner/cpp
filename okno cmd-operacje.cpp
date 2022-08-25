/* program zmienia polozenie i rozmiar "znaku" z ascii podanego na wejsciu (z jednego znaku char)
za pomoca funkcji rysuj mozna latwo zmienic ksztalt znaku
wejscie:
>> char (z czego ma byc zrobiony ksztalt)

sterowanie:
strzalki i znaki +, -
*/
#include <iostream>
#include <windows.h>
#include <Winuser.h>

using namespace std;

void wyswietl(char c, bool tab[][50]) {                 // wyswietlanie tablicy
	char d = ' ';
	system("cls");
	ios_base::sync_with_stdio(false);
	for (int y = 0; y < 50; y++)
		for (int x = 0; x < 120; x++)
			cout << ((tab[x][y] == true) ? c : d);
    cout << endl;
}
void rysuj(int x, int y, char c, int r) {               // rysowanie znaku
	bool tab[120][50];
	for (int i = 0; i < 120; i++)
		for (int j = 0; j < 50; j++)
			tab[i][j] = false;
	for (int i = x; i >= x - r; i--)
		tab[i][y + x - i] = true;
	for (int i = x; i >= x - r; i--)
		tab[i][y + 2 * r + i - x] = true;
	wyswietl(c, tab);
}

int main()
{
    int XX = 119, YY = 0, r = 10;                       //rozmiar tablicy i okna cmd
	char c;
	cin >> c;
	rysuj(XX, YY, c, r);
	while (1) {
		if (GetAsyncKeyState(0x25) == -32767)			// strzalka w lewo
		{
			if (XX - 1 - r >= 0) {
				XX--;
				rysuj(XX, YY, c, r);
			}
		}
		if (GetAsyncKeyState(0x26) == -32767)			// strzalka w gore
		{
			if (YY - 1 >= 0) {
				YY--;
				rysuj(XX, YY, c, r);
			}
		}
		if (GetAsyncKeyState(0x27) == -32767)			// strzalka w prawo
		{
			if (XX + 1 < 120) {
				XX++;
				rysuj(XX, YY, c, r);
			}
		}
		if (GetAsyncKeyState(0x28) == -32767)			// strzalka w dol
		{
			if (YY + 1 + 2 * r < 50) {
				YY++;
				rysuj(XX, YY, c, r);
			}
		}
		if (GetAsyncKeyState(0xBB) == -32767)			// +
		{
			if (YY + 2 + 2 * r < 50 && XX - 1 - r >= 0) {
                r++;
                rysuj(XX, YY, c, r);
			}
		}
		if (GetAsyncKeyState(0xBD) == -32767)			// -
		{
			r--;
			rysuj(XX, YY, c, r);
		}
	}
	return 0;
}


