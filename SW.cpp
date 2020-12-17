#include "SW.h"

//konstruktor
SW::SW(double czas, Graf graf, double ochlodzenie) {
	tab = graf.getTab();				//ustawienie macierzy reprezentuj¹cej graf
	ilosc_wierzcholkow = graf.getW();	//ustawienie liczby wierzcho³ków
	temperatura = obliczTemperature();	//wyznaczenie pocz¹tkowej temperatury
	czas_stopu = czas;					//ustawienie kryterium stopu
	stopien_ochlodzenia = ochlodzenie;	//ustawienie wspó³czynnika zmiany temperatury
	epoka = liczEpoke();				//wyznaczenie epoki
}

//funckja rozpoczynaj¹ca algorytm
void SW::start()
{
	vector<int> najlepsza;														//zainicjowanie najlepszej œcie¿ki
	vector<int> aktualna = algorytmZachlanny();									//wyznaczenie aktualnej sciezki za pomoc¹ algorytmu zachlannego
	vector<int> nowa(aktualna);													//utworzenie nowej sciezki														
	int pierwszy_do_zamiany;													//indeks pierwszego zamienianego wierzcholka
	int drugi_do_zamiany;														//indeks drugiego zamienianego wierzcho³ka
	int wynik = INT_MAX;														//ustawienie jakiejœ du¿ej liczby do wyniku
	int aktualna_sciezka = liczSciezke(aktualna);								//obliczenie wartosci aktualnej sciezki		
	double czas = 0;															//ustawienie czasu wykonania algorytmu
	double znajdz_czas = 0;														//ustawienie czasu, w którym znajdziemy najlepsze rozwi¹zanie
	clock_t start = clock();													//wystartowanie zegara

	while (czas <= czas_stopu) {												//dopoki czas wykonania nie przekorczyl kryterium stopu

		for (int i = epoka; i > 0; i--) {										//wykonujemy schladzanie dla ka¿dej epoki

			do {
				pierwszy_do_zamiany = rand() % ilosc_wierzcholkow;				//losujemy indeks dla pierwszego wierzcholka
				drugi_do_zamiany = rand() % ilosc_wierzcholkow;					//losujemy indeks dla drugiego wierzcholka
			} while (pierwszy_do_zamiany == drugi_do_zamiany);					//sprawdzamy czy nie s¹ identyczne

			nowa = aktualna;													//tworzymy now¹ œciezke i zamieniamy wierzcholki miejscami
			nowa[pierwszy_do_zamiany] = aktualna[drugi_do_zamiany];
			nowa[drugi_do_zamiany] = aktualna[pierwszy_do_zamiany];

			int nowa_sciezka = liczSciezke(nowa);								//liczymy wartosc nowej sciezki

			if (wynik > nowa_sciezka) {											//jezeli nowa sciezka jest lepsza niz obecna
				wynik = nowa_sciezka;											//nadpisujemy obecny wynik
				najlepsza = nowa;												//do obecnie najlepszej sciezki przypisujemy now¹
				znajdz_czas = (clock() - start) / (double)CLOCKS_PER_SEC;		//czas znalezienia rozwi¹zania
			}

			int roznica = aktualna_sciezka - nowa_sciezka;						//liczymy ró¿nicê miêdzy wartosciami obu sciezek

			if (roznica > 0) {													//jesli znalezlismy lepsza sciezkie (mniejsza wartosc)
				aktualna = nowa;												//nadpisujemy aktualna sciezke
				aktualna_sciezka = nowa_sciezka;								//nadpisujemy wartosc aktualnej sciezki
			}
			
			else if (liczPrawdopodobienstwo(roznica, temperatura) >((double)rand() / RAND_MAX))
			{ //z pewnym prawdopodobieñstwiem akceptujemy gorsze rozwi¹zanie
				aktualna = nowa;
				aktualna_sciezka = nowa_sciezka;
			}
		}
		temperatura *= stopien_ochlodzenia;					//och³adzamy
		czas = (clock() - start) / (double)CLOCKS_PER_SEC;	//czas wykonania algorytmu
	}
	wypisz(najlepsza, znajdz_czas, wynik);					//wypisujemy wyniki
}


//liczenie pocz¹tkowej temperatury
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

		oryginalna = losowaPermutacja(ilosc_wierzcholkow);				//wyznaczamy losow¹ œcie¿kê
		vector<int> sasiedztwo(oryginalna);								//tworzymy s¹siednie rozwi¹zanie

		int tmp = sasiedztwo[pierwszy_do_zamiany];						//zamieniamy miejscami wierzcholki o wylosowanych indeksach
		sasiedztwo[pierwszy_do_zamiany] = sasiedztwo[drugi_do_zamiany];
		sasiedztwo[drugi_do_zamiany] = tmp;

		delta += fabs(double(liczSciezke(oryginalna) - liczSciezke(sasiedztwo)));	//liczymy srednia wartosc roznicy miedzy wartosciami obu sciezek
	}

	delta /= 10000;						//wyznaczamy srednia wartosc jednej roznicy
	return (-1 * delta) / log(0.99);	//zwracamy pocz¹tkow¹ temperaturê
}


//funkcja licz¹ca prawdopodobieñstwo
double SW::liczPrawdopodobienstwo(int roznica, double temperatura) {
	return exp(roznica / temperatura);									//ze wzoru
}


//funckja wykonuj¹ca losow¹ permutacjê rozwi¹zania problemu
vector<int> SW::losowaPermutacja(int rozmiar) {
	vector<int> temp;							//tworzymy wektor
	temp.reserve(rozmiar);						//rezerwujemy miejsce

	for (int i = 0; i < rozmiar; i++) {
		temp.push_back(i);						//dodajemy kolejne wierzcholki do wektora
	}

	random_shuffle(temp.begin(), temp.end());	//mieszamy kolejnoœæ wierzcho³ków

	return temp;								//zwracamy stworzony wektor
}

//obliczenie d³ugoœci œcie¿ki
int SW::liczSciezke(vector<int> sciezka) {
	int droga = 0;												//tworzymy zmienn¹ przechowuj¹c¹ wartoœæ drogi

	for (int i = 0; i < sciezka.size() - 1; ++i) {				//przechodzimy po kolejnych wierzcho³kach wektora
		droga += tab[sciezka[i]][sciezka[i + 1]];				//dodajemy odleg³oœci pomiêdzy kolejnymi wierzcho³kami
	}
	droga += tab[sciezka[ilosc_wierzcholkow - 1]][sciezka[0]];	//dodajemy odleg³oœæ miêdzy wierzcho³kiem koñcowym i pocz¹tkowym

	return droga;												//zwracamy obliczon¹ wartosæ
}

//funckja wyswietlajaca wyniki
void SW::wypisz(vector<int> droga, double czas_znalezienia, int wynik) {
	cout << "Droga: ";													//wypisanie kolejnych wierzcho³ków
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		cout << droga[i];
		if (i < ilosc_wierzcholkow-1) {
			cout << " - ";
		}
	}
		
	cout << "\nKoszt: " << wynik << endl;								//wypisanie wartosci sciezki
	cout << "Znaleziono po: " << czas_znalezienia << " s " << endl;		//wypisanie czasu znalezienia rozwi¹zania
	cout << "Temperatura koncowa: " << temperatura << endl;				//wypisanie temperatury koñcowej
	cout << endl;
}

//algorytm zach³anny
vector<int> SW::algorytmZachlanny()
{
	vector <int> minSciezka = losowaPermutacja(ilosc_wierzcholkow); //wyznaczamy losow¹ œcie¿kê
	vector <int> aktualnaSciezka(minSciezka);						//tworzymy aktualn¹ œcie¿kê
	int minKoszt = liczSciezke(minSciezka);							//ustawiamy minimaln¹ d³ugoœæ za pomoc¹ funkcji licz¹cej d³ugoœæ minimalnej œcie¿ki
	int aktualnyKoszt = minKoszt;									//ustawiamy aktualny koszt
	do
	{
		for (int i = 0; i < ilosc_wierzcholkow; ++i)
		{
			for (int j = i; j < ilosc_wierzcholkow; ++j)		//przeszukujemy ka¿d¹ parê wierzcho³ków
			{
				if (i != j)										//sprawdzamy czy wierzcho³ki s¹ ró¿ne
				{
					int tmpKoszt;								//ustawiamy tymczasow¹ wartoœæ drogi
					vector <int> tmpSciezka(aktualnaSciezka);	//tworzymy tymczasow¹ œcie¿kê
					tmpSciezka[i] = aktualnaSciezka[j];			//zamieniamy miejscami wierzcho³ki
					tmpSciezka[j] = aktualnaSciezka[i];
					tmpKoszt = liczSciezke(tmpSciezka);			//liczymy wartoœæ tymczasowej œcie¿ki 
					if (tmpKoszt < aktualnyKoszt)				//jeœli wyliczona wartoœæ jest mniejsza (lepsza) ni¿ aktualna
					{
						aktualnaSciezka = tmpSciezka;			//to przypisujemy do aktualnej œcie¿ki now¹
						aktualnyKoszt = tmpKoszt;				//i do aktualnego minimalnego rozwi¹zania wyliczon¹ wartoœæ
					}
				}
			}
		}
		if (minKoszt > aktualnyKoszt)		//sprawdzamy czy znaleŸliœmy mniejsz¹ wartoœæ œcie¿ki
		{
			minSciezka = aktualnaSciezka;	//nadpisujemy obecnie minimaln¹ œcie¿kê
			minKoszt = aktualnyKoszt;		//przypisujemy tê wartoœæ do minimalnej d³ugoœci œcie¿ki
			continue;						//mo¿emy znaleŸæ lepsze rozwi¹zanie, dlatego szukamy dalej
		}
	} while (false);						//nie mo¿emy znaleŸæ lepszego rozwi¹zania
	return minSciezka;						//zwracamy najlepsz¹ œcie¿kê
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