#pragma once
class Ruch
{
private:
	int poczatek;	//zmienna przechowująca indeks mniejszego wierzchołka
	int koniec;		//zmienna przechowująca indeks większego wierzchołka
	int kadencja;	//zmienna przechowująca czas występowania wierzchołka na liście ruchów zakazanych

public:
	Ruch(int poczatek, int koniec, int kadencja);	//konstruktor
	~Ruch();										//destruktor
	int getPoczatek() {
		return poczatek;							//funkcja zwracajaca wartosc indeksu mniejszego wierzcholka
	}
	int getKoniec() {
		return koniec;								//funkcja zwracająca wartość indeksu większego wierzchołka
	}
	bool zmniejszenieKadencji();					//funkcja zmniejszająca czas i sprawdzająca czy wierzchołek powinien zostać usunięty z listy ruchów zakazanych
};

