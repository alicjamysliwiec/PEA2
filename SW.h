#include"Graf.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <ctime>


class SW
{
private:
	double temperatura;				//zmiennna przechowuj�ca warto�� temperatury
	double stopien_ochlodzenia;		//zmienna przechowuj�ca wsp�czynnik zmiany temperatury
	double czas_stopu;				//zmienna przechowuj�ca kryterium stopu
	int** tab;						//zmienna przechowuj�ca macierzow� reprezentacj� grafu
	int ilosc_wierzcholkow;			//zmienna przechowuj�ca ilo�� wierzcholkow w grafie
	int epoka;						//zmienna przechowuj�ca warto�� epoki

public:
	SW(double czas, Graf graf, double ochlodzenia);						//kontruktor 
	~SW();																//destruktor
	int liczEpoke();													//funkcja licz�ca warto�� epoki w zale�no�ci od parametr�w
	void start();														//funkcja startuj�ca algorytm
	double obliczTemperature();											//funkcja licz�ca pocz�tkow� warto�� temperatury
	double liczPrawdopodobienstwo(int roznica, double temperatura);		//funckja obliczaj�ca prawdopodobie�stwo, na podstawie kt�rego mo�emy zaakceptowa� gorszy wynik
	int liczSciezke(vector<int> sciezka);								//funkcja licz�ca d�ugo�� �cie�ki dla podanego wektora
	vector<int> losowaPermutacja(int rozmiar);							//funkcja zwraca losow� kolejno�� wierzcho�k�w
	void wypisz(vector<int> droga, double czas_znalezienia, int wynik);	//funkcja wy�wietlaj�ca wyniki algorytmu
	vector<int> algorytmZachlanny();									//funkcja zwracj�ca �cie�k� obliczon� za pomoc� algorytmu zach�annego
};

