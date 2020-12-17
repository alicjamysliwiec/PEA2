#include"Graf.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <ctime>


class SW
{
private:
	double temperatura;				//zmiennna przechowuj¹ca wartoœæ temperatury
	double stopien_ochlodzenia;		//zmienna przechowuj¹ca wspó³czynnik zmiany temperatury
	double czas_stopu;				//zmienna przechowuj¹ca kryterium stopu
	int** tab;						//zmienna przechowuj¹ca macierzow¹ reprezentacjê grafu
	int ilosc_wierzcholkow;			//zmienna przechowuj¹ca iloœæ wierzcholkow w grafie
	int epoka;						//zmienna przechowuj¹ca wartoœæ epoki

public:
	SW(double czas, Graf graf, double ochlodzenia);						//kontruktor 
	~SW();																//destruktor
	int liczEpoke();													//funkcja licz¹ca wartoœæ epoki w zale¿noœci od parametrów
	void start();														//funkcja startuj¹ca algorytm
	double obliczTemperature();											//funkcja licz¹ca pocz¹tkow¹ wartoœæ temperatury
	double liczPrawdopodobienstwo(int roznica, double temperatura);		//funckja obliczaj¹ca prawdopodobieñstwo, na podstawie którego mo¿emy zaakceptowaæ gorszy wynik
	int liczSciezke(vector<int> sciezka);								//funkcja licz¹ca d³ugoœæ œcie¿ki dla podanego wektora
	vector<int> losowaPermutacja(int rozmiar);							//funkcja zwraca losow¹ kolejnoœæ wierzcho³ków
	void wypisz(vector<int> droga, double czas_znalezienia, int wynik);	//funkcja wyœwietlaj¹ca wyniki algorytmu
	vector<int> algorytmZachlanny();									//funkcja zwracj¹ca œcie¿kê obliczon¹ za pomoc¹ algorytmu zach³annego
};

