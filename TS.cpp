#include "TS.h"

//konstruktor algorytmu
TS::TS(double czas, Graf graf) {
	ilosc_wierzcholkow = graf.getW();	//ustawienie liczby wierzcholkow
	tab = graf.getTab();				//ustawienie macierzy reprezentującej graf
	czas_stopu = czas;					//ustawienie kryterium stopu
}

//destruktor algorytmu
TS::~TS() {

}

//wystartowanie algorytmu
void TS::start()
{
	vector<int> najlepsza_sciezka = algorytmZachlanny();						//wyznaczenie sciezki za pomocą algorytmu zachlannego i ustawienie jako obecnie najlepszej
	vector<int> aktualna_sciezka(najlepsza_sciezka);							//ustawienie aktualnej sciezki 
	double czas = 0;															//ustawienie czasu wykonania algorytmu
	double znajdz_czas = 0;														//ustawienie czasu najlepszego rozwiązania
	kadencja = ilosc_wierzcholkow;												//ustawienie kadencji
	int dywersyfikacja = 0;														//utworzenie zmiennej dywersyfikacji
	clock_t start = clock();													//wystartowanie zegara

	while (czas <= czas_stopu) {																				//dopoki nie czas wykonania algorytmu nie przekroczył kryterium stopu
		aktualna_sciezka = znajdzNajlepszyRuch(aktualna_sciezka, liczSciezke(najlepsza_sciezka));				//modyfikacja aktualnej sciezki o najlepszy dozwolony ruch
		if (liczSciezke(aktualna_sciezka) < liczSciezke(najlepsza_sciezka)) {									//sprawdzamy czy dlugosc drogi jest lepsza
			dywersyfikacja = 0;																					//zerujemy dywersyfikację, bo mozemy znalezc lepsze rozwiazanie
			najlepsza_sciezka = aktualna_sciezka;																//jesli tak, przypisujemy do najlepszej sciezki aktualna
			znajdz_czas = (clock() - start) / (double)CLOCKS_PER_SEC;											//czas znalezienia najlepszej sciezki
		}
		else {
			dywersyfikacja++;																					//nie znalezlismy rozwiazania i zwiekszamy wspolczynnik prowadzacy do resetu
		}

		if (koniec < poczatek) ruchy_zakazane.push_back(Ruch(koniec, poczatek, kadencja + rand() % kadencja));	//dodajemy ruch do listy ruchów zakazanych - mniejsza liczba jest pierwsza
		else ruchy_zakazane.push_back(Ruch(poczatek, koniec, kadencja + rand() % kadencja));						

		for (int i = 0;i < ruchy_zakazane.size();i++) {				//przechodzimy po wszystkich ruchach zakazanych
			if (ruchy_zakazane[i].zmniejszenieKadencji()) {			//zmniejszamy kadencję i sprawdzamy czy ruch dalej powinien być zakazany
				ruchy_zakazane.erase(ruchy_zakazane.begin() + i);	//jeśli nie powinien być zakazany to usuwamy go z listy
			}
		}
		if (dywersyfikacja > 3 * ilosc_wierzcholkow) {
			dywersyfikacja = 0;														//resetujemy dywersyfikacje
			aktualna_sciezka = algorytmZachlanny();									//losujemy nowa sciezke
			if (liczSciezke(aktualna_sciezka) < liczSciezke(najlepsza_sciezka)) {	//sprawdzamy czy dlugosc drogi jest lepsza
				najlepsza_sciezka = aktualna_sciezka;								//jesli tak, przypisujemy do najlepszej sciezki aktualna
				znajdz_czas = (clock() - start) / (double)CLOCKS_PER_SEC;			//czas znalezienia najlepszej sciezki
			}
		}
		czas = (clock() - start) / (double)CLOCKS_PER_SEC;			//pobranie czasu wykonania algorytmu
	}
	wypisz(najlepsza_sciezka, znajdz_czas, liczSciezke(najlepsza_sciezka)); //wypisanie rezultatu
}

//funkcja wypisująca wyniki
void TS::wypisz(vector<int> droga, double czas_znalezienia, int wynik) {
	cout << "Droga: ";													//wypisanie kolejnych wierzchołków najlepszej znalezionej ścieżki
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		cout << droga[i];
		if (i < ilosc_wierzcholkow - 1) {
			cout << " - ";
		}
	}

	cout << "\nKoszt: " << wynik << endl;								//wypisanie długości ścieżki
	cout << "Znaleziono po: " << czas_znalezienia << " s " << endl;		//wypisanie czasu znalezienia najlepszego rozwiązania
	cout << endl;
}

//algorytm zachłanny
vector<int> TS::algorytmZachlanny()
{
	vector <int> minSciezka = losowaPermutacja(ilosc_wierzcholkow); //wyznaczamy losową ścieżkę
	vector <int> aktualnaSciezka(minSciezka);						//tworzymy aktualną ścieżkę
	int minKoszt = liczSciezke(minSciezka);							//ustawiamy minimalną długość za pomocą funkcji liczącej długość minimalnej ścieżki
	int aktualnyKoszt = minKoszt;									//ustawiamy aktualny koszt
	do
	{
		for (int i = 0; i < ilosc_wierzcholkow; ++i)
		{
			for (int j = i; j < ilosc_wierzcholkow; ++j)		//przeszukujemy każdą parę wierzchołków
			{
				if (i != j)										//sprawdzamy czy wierzchołki są różne
				{
					int tmpKoszt;								//ustawiamy tymczasową wartość drogi
					vector <int> tmpSciezka(aktualnaSciezka);	//tworzymy tymczasową ścieżkę
					tmpSciezka[i] = aktualnaSciezka[j];			//zamieniamy miejscami wierzchołki
					tmpSciezka[j] = aktualnaSciezka[i];			
					tmpKoszt = liczSciezke(tmpSciezka);			//liczymy wartość tymczasowej ścieżki 
					if (tmpKoszt < aktualnyKoszt)				//jeśli wyliczona wartość jest mniejsza (lepsza) niż aktualna
					{
						aktualnaSciezka = tmpSciezka;			//to przypisujemy do aktualnej ścieżki nową
						aktualnyKoszt = tmpKoszt;				//i do aktualnego minimalnego rozwiązania wyliczoną wartość
					}
				}
			}
		}
		if (minKoszt > aktualnyKoszt)		//sprawdzamy czy znaleźliśmy mniejszą wartość ścieżki
		{
			minSciezka = aktualnaSciezka;	//nadpisujemy obecnie minimalną ścieżkę
			minKoszt = aktualnyKoszt;		//przypisujemy tę wartość do minimalnej długości ścieżki
			continue;						//możemy znaleźć lepsze rozwiązanie, dlatego szukamy dalej
		}
	} while (false);						//nie możemy znaleźć lepszego rozwiązania
	return minSciezka;						//zwracamy najlepszą ścieżkę
}

//szukanie najlepszego dozwolonego ruchu
vector<int> TS::znajdzNajlepszyRuch(vector<int> sciezka, int najlepsza)
{
	int najlepszeRozwiazanie = najlepsza;					//ustawiamy wartosc najlepszego rozwiazania jako to ktore mamy obecnie
	vector <int> minSciezka = sciezka;						//ustawiamy minimalną ścieżkę jako tę, którą mamy obecnie
	int minKoszt = INT_MAX;									//przypisujemy do najmniejszej wartości ścieżki jakąś dużą liczbę

	for (int i = 0; i < ilosc_wierzcholkow - 1; ++i)
	{
		for (int j = i + 1; j < ilosc_wierzcholkow; ++j)	//przeszukujemy wszystkie pary wierzchołków
		{
			bool zakazany = false;							//zmienna przechowująca informację czy ruch jest zakazany
			for (int k = 0;k < ruchy_zakazane.size();k++)	//przechodzimy po wszystkich ruchach
			{
				if (i == ruchy_zakazane[k].getPoczatek() && j == ruchy_zakazane[k].getKoniec())	//sprawdzamy czy ruch jest na liscie ruchow zakazanych
				{
					vector<int> nowa = sciezka;				//tworzymy nowa sciezke po dokonaniu ruchu
					nowa[i] = sciezka[j];
					nowa[j] = sciezka[i];
					int koszt = liczSciezke(nowa);			//liczymy dlugosc stworzonej sciezki
					if (najlepszeRozwiazanie > koszt && minKoszt > koszt)		
					{										//sprawdzamy czy zakazany ruch nie znajduje lepszego rozwiazania niz dotychczas
						minSciezka = nowa;
						minKoszt = koszt;
						najlepszeRozwiazanie = koszt;
					}
					zakazany = true;						//ustawiamy go jako zakazany
					break;									//wychodzimy z pętli
				}
			}
			if (!zakazany) {								//jeśli ruch nie jest zakazany
				vector<int> nowa = sciezka;					//tworzymy nową ścieżkę po dokonaniu ruchu
				nowa[i] = sciezka[j];						
				nowa[j] = sciezka[i];
				int koszt = liczSciezke(nowa);				//liczymy dlugosc stworzonej sciezki
				if (koszt < minKoszt)						//sprawdzamy czy obliczona wartosc jest mniejsza niz obecna minimalna
				{
					minKoszt = koszt;						//nadpisujemy wartosc minimalnej sciezki
					minSciezka = nowa;						//ustawiamy nową ścieżkę jako minimalną
					poczatek = i;							//zapisujemy indeks wierzcholka, z ktorego wykonujemy ruch
					koniec = j;								//zapisujemy indeks wierzcholka, do którego wykonujem ruch
				}
			}
		}
	}
	return minSciezka;										//zwracamy najlepszą ścieżkę
}

//funckja wykonująca losową permutację rozwiązania problemu
vector<int> TS::losowaPermutacja(int rozmiar) {
	vector<int> temp;							//tworzymy wektor
	temp.reserve(rozmiar);						//rezerwujemy miejsce

	for (int i = 0; i < rozmiar; i++) {
		temp.push_back(i);						//dodajemy kolejne wierzcholki do wektora
	}	

	random_shuffle(temp.begin(), temp.end());	//mieszamy kolejność wierzchołków

	return temp;								//zwracamy stworzony wektor
}

//obliczenie długości ścieżki
int TS::liczSciezke(vector<int> sciezka) {
	int droga = 0;												//tworzymy zmienną przechowującą wartość drogi

	for (int i = 0; i < sciezka.size() - 1; ++i) {				//przechodzimy po kolejnych wierzchołkach wektora
		droga += tab[sciezka[i]][sciezka[i + 1]];				//dodajemy odległości pomiędzy kolejnymi wierzchołkami
	}
	droga += tab[sciezka[ilosc_wierzcholkow - 1]][sciezka[0]];	//dodajemy odległość między wierzchołkiem końcowym i początkowym

	return droga;												//zwracamy obliczoną wartosć
}