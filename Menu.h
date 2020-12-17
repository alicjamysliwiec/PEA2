#include <string>
#include <conio.h>
#include<iostream>
#include "Graf.h"
#include "SW.h"
#include "TS.h"
using namespace std;
class Menu
{
private:
	Graf graf;								//zmienna przechowująca reprezentację grafu
	SW* algorytmSW;							//zmienna odpowiedzialna za algorytm symulowanego wyżarzania
	TS* algorytmTS;							//zmienna odpowiedzialna za algorytm tabu search


public:
	Menu();									//konstruktor
	~Menu();								//destruktor
	void NacisnijKlawiszByKontynuwoac();	//funkcja pomocnicza obslugujaca klawisze
};

