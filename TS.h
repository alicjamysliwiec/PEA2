#include"Graf.h"
#include"Ruch.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <ctime>

class TS
{
private:
	double czas_stopu;				//zmienna przechowująca kryterium stopu
	int** tab;						//tablica dwuwymiarowa przechowująca reprezentację grafu
	int ilosc_wierzcholkow;			//zmienna przechowująca ilość wierzchołków w grafie (liczba miast)
	int kadencja = 100;				//zmienna przechowująca informację jak długo ruch jest zakazany
	vector<Ruch> ruchy_zakazane;	//lista zawierająca ruchy zakazane
	int poczatek = 0;				//zmienna przechowująca początek ostatniego ruchu
	int koniec = 0;					//zmienna przechowująca koniec ostatniego ruchu

public:
	TS(double czas, Graf graf);											//konstruktor algorytmu
	~TS();																//destruktor algorytmu
	void start();														//funkcja rozpoczynająca algorytm
	int liczSciezke(vector<int> sciezka);								//funkcja licząca długość ścieżki dla podanego wektora
	vector<int> losowaPermutacja(int rozmiar);							//funkcja zwraca losową kolejność wierzchołków
	void wypisz(vector<int> droga, double czas_znalezienia, int wynik);	//funkcja wyświetlająca wyniki algorytmu
	vector<int> algorytmZachlanny();									//funkcja zwracjąca ścieżkę obliczoną za pomocą algorytmu zachłannego
	vector<int> znajdzNajlepszyRuch(vector<int> sciezka, int najlepsza);//funkcja znajdująca najlepszy dozwolony ruch
};