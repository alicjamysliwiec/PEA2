#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<string>
#include <iostream>
#include <fstream>
#include "Menu.h"

using namespace std;


int main()
{
	srand(time(NULL));			//rozpoczęcie odliczania
	Menu* menu = new Menu();	//stworzenie menu
	return 0;
}
