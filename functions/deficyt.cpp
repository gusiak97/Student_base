#include "Deficyt.h"

using namespace std;

Deficyt::Deficyt()
{
	pkt_ects = nullptr;
	przedmioty_lista = nullptr;
	n = 0;	
}

Deficyt::Deficyt(int newN)
{
	n = newN;

	przedmioty_lista = new string[n];
	pkt_ects = new int[n];
}

Deficyt::~Deficyt()
{
	if (przedmioty_lista)
	{
		delete[] przedmioty_lista;
		przedmioty_lista = NULL;
	}

	if (pkt_ects)
	{
		delete[] pkt_ects;
		pkt_ects = NULL;
	}
}

//////////////////////////////////////////////////////////////////	
																				//	METODA WCZYTUJ¥CA
void Deficyt::Wczytaj_deficyt(fstream& plik, int n)
{
	if (plik.is_open())
	{
		przedmioty_lista = new string[n];
		pkt_ects = new int[n];

		for (int i = 0; i < n; i++)
		{
			getline(plik, przedmioty_lista[i], ':');
			plik >> pkt_ects[i];
		}
	}
}

//////////////////////////////////////////////////////////////////	
																				//	METODA WYPISUJ¥CA
void Deficyt::Wyswietl_deficyt(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << przedmioty_lista[i] << ": " << pkt_ects[i];
	}
	cout << "\n\n";
}