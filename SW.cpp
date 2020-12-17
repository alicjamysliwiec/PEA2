#include "SW.h"

//konstruktor
SW::SW(double czas, Graf graf, double ochlodzenie) {
	tab = graf.getTab();				//ustawienie macierzy reprezentuj�cej graf
	ilosc_wierzcholkow = graf.getW();	//ustawienie liczby wierzcho�k�w
	temperatura = obliczTemperature();	//wyznaczenie pocz�tkowej temperatury
	czas_stopu = czas;					//ustawienie kryterium stopu
	stopien_ochlodzenia = ochlodzenie;	//ustawienie wsp�czynnika zmiany temperatury
	epoka = liczEpoke();				//wyznaczenie epoki
}

//funckja rozpoczynaj�ca algorytm
void SW::start()
{
	vector<int> najlepsza;														//zainicjowanie najlepszej �cie�ki
	vector<int> aktualna = algorytmZachlanny();									//wyznaczenie aktualnej sciezki za pomoc� algorytmu zachlannego
	vector<int> nowa(aktualna);													//utworzenie nowej sciezki														
	int pierwszy_do_zamiany;													//indeks pierwszego zamienianego wierzcholka
	int drugi_do_zamiany;														//indeks drugiego zamienianego wierzcho�ka
	int wynik = INT_MAX;														//ustawienie jakiej� du�ej liczby do wyniku
	int aktualna_sciezka = liczSciezke(aktualna);								//obliczenie wartosci aktualnej sciezki		
	double czas = 0;															//ustawienie czasu wykonania algorytmu
	double znajdz_czas = 0;														//ustawienie czasu, w kt�rym znajdziemy najlepsze rozwi�zanie
	clock_t start = clock();													//wystartowanie zegara

	while (czas <= czas_stopu) {												//dopoki czas wykonania nie przekorczyl kryterium stopu

		for (int i = epoka; i > 0; i--) {										//wykonujemy schladzanie dla ka�dej epoki

			do {
				pierwszy_do_zamiany = rand() % ilosc_wierzcholkow;				//losujemy indeks dla pierwszego wierzcholka
				drugi_do_zamiany = rand() % ilosc_wierzcholkow;					//losujemy indeks dla drugiego wierzcholka
			} while (pierwszy_do_zamiany == drugi_do_zamiany);					//sprawdzamy czy nie s� identyczne

			nowa = aktualna;													//tworzymy now� �ciezke i zamieniamy wierzcholki miejscami
			nowa[pierwszy_do_zamiany] = aktualna[drugi_do_zamiany];
			nowa[drugi_do_zamiany] = aktualna[pierwszy_do_zamiany];

			int nowa_sciezka = liczSciezke(nowa);								//liczymy wartosc nowej sciezki

			if (wynik > nowa_sciezka) {											//jezeli nowa sciezka jest lepsza niz obecna
				wynik = nowa_sciezka;											//nadpisujemy obecny wynik
				najlepsza = nowa;												//do obecnie najlepszej sciezki przypisujemy now�
				znajdz_czas = (clock() - start) / (double)CLOCKS_PER_SEC;		//czas znalezienia rozwi�zania
			}

			int roznica = aktualna_sciezka - nowa_sciezka;						//liczymy r�nic� mi�dzy wartosciami obu sciezek

			if (roznica > 0) {													//jesli znalezlismy lepsza sciezkie (mniejsza wartosc)
				aktualna = nowa;												//nadpisujemy aktualna sciezke
				aktualna_sciezka = nowa_sciezka;								//nadpisujemy wartosc aktualnej sciezki
			}
			
			else if (liczPrawdopodobienstwo(roznica, temperatura) >((double)rand() / RAND_MAX))
			{ //z pewnym prawdopodobie�stwiem akceptujemy gorsze rozwi�zanie
				aktualna = nowa;
				aktualna_sciezka = nowa_sciezka;
			}
		}
		temperatura *= stopien_ochlodzenia;					//och�adzamy
		czas = (clock() - start) / (double)CLOCKS_PER_SEC;	//czas wykonania algorytmu
	}
	wypisz(najlepsza, znajdz_czas, wynik);					//wypisujemy wyniki
}


//liczenie pocz�tkowej temperatury
double SW::obliczTemperature() {

	vector<int> oryginalna;												//tworzymy wektor

	int pierwszy_do_zamiany;											//indeks pierwszego wierzcholka
	int drugi_do_zamiany;												//indeks drugiego wierzcholka
	int delta = 0;														//srednia roznica

	for (int i = 0; i < 10000; i++) {									//wykonujemy 10 000 razy

		do {
			pierwszy_do_zamiany = rand() % ilosc_wierzcholkow;			//losujemy pierwszy indeks
			drugi_do_zamiany = rand() % ilosc_wierzcholkow;				//losujemy drugi indeks
		} while (pierwszy_do_zamiany == drugi_do_zamiany);				//sprawdzamy, czy nie sa takie same

		oryginalna = losowaPermutacja(ilosc_wierzcholkow);				//wyznaczamy losow� �cie�k�
		vector<int> sasiedztwo(oryginalna);								//tworzymy s�siednie rozwi�zanie

		int tmp = sasiedztwo[pierwszy_do_zamiany];						//zamieniamy miejscami wierzcholki o wylosowanych indeksach
		sasiedztwo[pierwszy_do_zamiany] = sasiedztwo[drugi_do_zamiany];
		sasiedztwo[drugi_do_zamiany] = tmp;

		delta += fabs(double(liczSciezke(oryginalna) - liczSciezke(sasiedztwo)));	//liczymy srednia wartosc roznicy miedzy wartosciami obu sciezek
	}

	delta /= 10000;						//wyznaczamy srednia wartosc jednej roznicy
	return (-1 * delta) / log(0.99);	//zwracamy pocz�tkow� temperatur�
}


//funkcja licz�ca prawdopodobie�stwo
double SW::liczPrawdopodobienstwo(int roznica, double temperatura) {
	return exp(roznica / temperatura);									//ze wzoru
}


//funckja wykonuj�ca losow� permutacj� rozwi�zania problemu
vector<int> SW::losowaPermutacja(int rozmiar) {
	vector<int> temp;							//tworzymy wektor
	temp.reserve(rozmiar);						//rezerwujemy miejsce

	for (int i = 0; i < rozmiar; i++) {
		temp.push_back(i);						//dodajemy kolejne wierzcholki do wektora
	}

	random_shuffle(temp.begin(), temp.end());	//mieszamy kolejno�� wierzcho�k�w

	return temp;								//zwracamy stworzony wektor
}

//obliczenie d�ugo�ci �cie�ki
int SW::liczSciezke(vector<int> sciezka) {
	int droga = 0;												//tworzymy zmienn� przechowuj�c� warto�� drogi

	for (int i = 0; i < sciezka.size() - 1; ++i) {				//przechodzimy po kolejnych wierzcho�kach wektora
		droga += tab[sciezka[i]][sciezka[i + 1]];				//dodajemy odleg�o�ci pomi�dzy kolejnymi wierzcho�kami
	}
	droga += tab[sciezka[ilosc_wierzcholkow - 1]][sciezka[0]];	//dodajemy odleg�o�� mi�dzy wierzcho�kiem ko�cowym i pocz�tkowym

	return droga;												//zwracamy obliczon� wartos�
}

//funckja wyswietlajaca wyniki
void SW::wypisz(vector<int> droga, double czas_znalezienia, int wynik) {
	cout << "Droga: ";													//wypisanie kolejnych wierzcho�k�w
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		cout << droga[i];
		if (i < ilosc_wierzcholkow-1) {
			cout << " - ";
		}
	}
		
	cout << "\nKoszt: " << wynik << endl;								//wypisanie wartosci sciezki
	cout << "Znaleziono po: " << czas_znalezienia << " s " << endl;		//wypisanie czasu znalezienia rozwi�zania
	cout << "Temperatura koncowa: " << temperatura << endl;				//wypisanie temperatury ko�cowej
	cout << endl;
}

//algorytm zach�anny
vector<int> SW::algorytmZachlanny()
{
	vector <int> minSciezka = losowaPermutacja(ilosc_wierzcholkow); //wyznaczamy losow� �cie�k�
	vector <int> aktualnaSciezka(minSciezka);						//tworzymy aktualn� �cie�k�
	int minKoszt = liczSciezke(minSciezka);							//ustawiamy minimaln� d�ugo�� za pomoc� funkcji licz�cej d�ugo�� minimalnej �cie�ki
	int aktualnyKoszt = minKoszt;									//ustawiamy aktualny koszt
	do
	{
		for (int i = 0; i < ilosc_wierzcholkow; ++i)
		{
			for (int j = i; j < ilosc_wierzcholkow; ++j)		//przeszukujemy ka�d� par� wierzcho�k�w
			{
				if (i != j)										//sprawdzamy czy wierzcho�ki s� r�ne
				{
					int tmpKoszt;								//ustawiamy tymczasow� warto�� drogi
					vector <int> tmpSciezka(aktualnaSciezka);	//tworzymy tymczasow� �cie�k�
					tmpSciezka[i] = aktualnaSciezka[j];			//zamieniamy miejscami wierzcho�ki
					tmpSciezka[j] = aktualnaSciezka[i];
					tmpKoszt = liczSciezke(tmpSciezka);			//liczymy warto�� tymczasowej �cie�ki 
					if (tmpKoszt < aktualnyKoszt)				//je�li wyliczona warto�� jest mniejsza (lepsza) ni� aktualna
					{
						aktualnaSciezka = tmpSciezka;			//to przypisujemy do aktualnej �cie�ki now�
						aktualnyKoszt = tmpKoszt;				//i do aktualnego minimalnego rozwi�zania wyliczon� warto��
					}
				}
			}
		}
		if (minKoszt > aktualnyKoszt)		//sprawdzamy czy znale�li�my mniejsz� warto�� �cie�ki
		{
			minSciezka = aktualnaSciezka;	//nadpisujemy obecnie minimaln� �cie�k�
			minKoszt = aktualnyKoszt;		//przypisujemy t� warto�� do minimalnej d�ugo�ci �cie�ki
			continue;						//mo�emy znale�� lepsze rozwi�zanie, dlatego szukamy dalej
		}
	} while (false);						//nie mo�emy znale�� lepszego rozwi�zania
	return minSciezka;						//zwracamy najlepsz� �cie�k�
}

//funckja pomocnicza do wyznaczenia optymalnej wartosci epoki
int SW::liczEpoke() {
	int epoka = 0;
	if (ilosc_wierzcholkow == 48) {
		if (stopien_ochlodzenia == 0.99) {
			epoka = 90 * ilosc_wierzcholkow;
		}
		else if (stopien_ochlodzenia == 0.95) {
			epoka = 900 * ilosc_wierzcholkow;
		}
		else {
			epoka = 2000 * ilosc_wierzcholkow;
		}
	}
	else if (ilosc_wierzcholkow == 170) {
		if (stopien_ochlodzenia == 0.99) {
			epoka = 180 * ilosc_wierzcholkow;
		}
		else if (stopien_ochlodzenia == 0.95) {
			epoka = 600 * ilosc_wierzcholkow;
		}
		else {
			epoka = 850 * ilosc_wierzcholkow;
		}
	}
	else {
		if (stopien_ochlodzenia == 0.99) {
			epoka = 10 * ilosc_wierzcholkow;
		}
		else if (stopien_ochlodzenia == 0.95) {
			epoka = 50 * ilosc_wierzcholkow;
		}
		else {
			epoka = 130 * ilosc_wierzcholkow;
		}
	}
	return epoka;
}