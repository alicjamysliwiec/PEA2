#include "Menu.h"

Menu::Menu() {
	string nazwa_pliku;													//zmienna przechowujaca nazwe pliku
	char option;														//zmienna odpowiedzialna za dokonany wybor w menu
	char numer;															//zmienna do wyboru wspolczynnika
	double kryterium_stopu = 0;											//zmienna przechowujaca kryterium stopu
	double wspolczynnik = 0;											//zmienna przechowuj¹ca wspó³czynnik zmiany temperatury
	do {
		cout << endl;
		cout << "1. Wczytaj z pliku" << endl;							
		cout << "2. Wprowadz kryterium stopu" << endl;
		cout << "3. Algorytm Tabu Search" << endl;
		cout << "4. Ustaw wspolczynnik zmiany temperatury" << endl;		//menu programu
		cout << "5. Algorytm Symulowanego Wyzarzania" << endl;
		cout << "0. Wyjscie" << endl;
		cout << "Podaj opcje: ";
		option = _getche();												//pobranie znaku z klawiatury
		cout << endl;

		switch (option) {
		case '1':														
			do {
				cout << "Podaj nazwe pliku: ";							
				cin >> nazwa_pliku;										//wczytanie nazwy pliku
			} while (!graf.wczytajPlik(nazwa_pliku));					//powtorzenie jesli nie uda sie wczytac
			NacisnijKlawiszByKontynuwoac();
			break;
		case '2':
			cout << "Wprowadz kryterium stopu: ";
			cin >> kryterium_stopu;										//wczytanie kryterium stopu
			cout << "Twoje kryterium stopu to: " << kryterium_stopu;	//wyswietlenie ustawionego kryterium
			NacisnijKlawiszByKontynuwoac();
			break;
		case '3':
			if (!graf.wczytajPlik(nazwa_pliku)) {						//sprawdzenie czy udalo sie wczytac graf
				cout << "Nie wczytano grafu" << endl;
			}
			if (kryterium_stopu == NULL) {								//sprawdzenie czy zostalo ustawione kryterium stopu
				cout << "Nie zostalo wprowadzone kryterium stopu";
			}
			else {
				algorytmTS = new TS(kryterium_stopu, graf);				//utworzenie algorytmu tabu search
				algorytmTS->start();									//wystartowanie algorytmu tabu search
			}
			break;
		case '4':
			cout << "Ustaw wspolczynnik zmiany temperatury: " << endl;
			cout << "1) 0.99" << endl;
			cout << "2) 0.95" << endl;
			cout << "3) 0.90" << endl;
			numer = _getche();											//wczytanie wartosci z klawiatury
			cout << endl;
			switch (numer) {
			case '1': wspolczynnik = 0.99;								//ustawienie wartosci wspolczynnika na 0.99
				break;
			case '2': wspolczynnik = 0.95;								//ustawienie wartosci wspolczynnika na 0.95
				break;
			case '3': wspolczynnik = 0.90;								//ustawienie wartosci wspolczynnika na 0.90
				break;
			default:
				cout << "Wcisnieto niepoprawny klawisz";
				break;
			}
			cout << "Twoj wspolczynnik zmiany temperatury to: " << wspolczynnik;
			NacisnijKlawiszByKontynuwoac();
			break;
		case '5':
			if (!graf.wczytajPlik(nazwa_pliku)) {							//sprawdzenie czy graf zostal wczytany
				cout << "Nie wczytano grafu" << endl;
			}
			if (kryterium_stopu == NULL || wspolczynnik == NULL) {
				cout << "Nie zostaly ustawione wszystkie wartosci.";		//sprawdenie czy zostaly ustawione odpowiednie parametry
			}
			else {
				algorytmSW = new SW(kryterium_stopu, graf, wspolczynnik);	//utworzenie algorytmu
				algorytmSW->start();										//wystartowanie algorytmu
			}
			NacisnijKlawiszByKontynuwoac();
			break;
		case '0':
			break;
		default:
			cout << "Cos poszlo nie tak, sprobuj ponownie :)" << endl;
		};
	} while (option != '0');
}


void Menu::NacisnijKlawiszByKontynuwoac() {
	cout << "\nNacisnij dowolny klawisz by kontynuowac" << endl;
	_getche();
}


Menu::~Menu() {

}