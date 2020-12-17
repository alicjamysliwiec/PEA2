#include "Ruch.h"

//konstruktor z ustawieniem parametrów
Ruch::Ruch(int poczatek, int koniec, int kadencja) {
	this->poczatek = poczatek; //
	this->koniec = koniec;
	this->kadencja = kadencja;
}

//destruktor
Ruch::~Ruch() {

}

//funkcja zmniejszająca kadencję
bool Ruch::zmniejszenieKadencji() {
	kadencja--;			//zmniejszamy kadencję
	if (kadencja) {		//jeśli kadencja jest różna od zera 
		return false;	//zwracamy fałsz (nie usuwamy wierzcholka z listy ruchow zakazanych)
	}
	else {
		return true;	//jeśli kadencja się skończyła możemy usunać wierzcholek z listy ruchow zakazanych
	}
}
