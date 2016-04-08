#include "Slav.h"
#include <fstream>

using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size()); 
	/* Dochodzi tu do tzw. leniwej inicjalizacji (leniwa inicjalizacja jest to wzorzec 
	projektowy polegający na opóźnianiu tworzenia obiektu, obliczania wartości lub przeprowadzania 
	innych kosztownych operacji, aż do momentu pierwszego zapotrzebowania na nie)

	Ze względu na wystąpienie słowa static linijka ta wykona się tylko jeden raz
	init() wczytuje imiona z pliku tekstowego do wektora, zaś zmiennej amountOfNames 
	przypisywana jest wartość names.size(), czyli ilość wczytanych imion */
	_name = names[rand() % amountOfNames];
	_id = _counter++;
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}