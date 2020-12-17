#include "Graf.h"

//konstruktor grafu
Graf::Graf() {
}

//destruktor grafu
Graf::~Graf() {
}

//funkcja wczytuj¹ca graf z pliku
bool Graf::wczytajPlik(string nazwa_pliku) {
	ifstream plik;											//utworzenie zmienniej
	plik.open(nazwa_pliku);									//otworzenie pliku
	if (!plik.good()) return false;							//jesli nie udalo sie otworzyc pliku zwracamy fa³sz

	for (int i = 0; i < ilosc_wierzcholkow; i++) {
		delete[] tab[i];									//usuwamy to co obecnie jest ustawione jako graf
	}
	delete[] tab;

	string linia;											//utworzenie dwóch stringów
	string costam;
	for (int i = 0; i < 7; i++) {
		getline(plik, costam);								//pobieramy kolejne linie	
		if (i == 3) linia = costam;							//w 3 lini mamy ilosc wierzcholkow
	}

	ilosc_wierzcholkow = stoi(linia.erase(0, 11));			//usuwamy znaki z danej lini

	tab = new int* [ilosc_wierzcholkow];					
	for (int i = 0; i < ilosc_wierzcholkow; i++) {
		tab[i] = new int[ilosc_wierzcholkow];
		for (int j = 0; j < ilosc_wierzcholkow; j++) {		//tworzymy nowa tablice przechowujaca graf i wczytujemy do niego wartosci
			plik >> tab[i][j];
		}
	}
	plik.close();											//zamykamy plik
	return true;
}