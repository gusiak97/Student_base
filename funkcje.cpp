#include "Funkcje.h"

using namespace std;

void wyczysc_plik()					//FUNKCJA CZYSZCZ¥CA PLIK
{
	remove("student_out.txt");
}

void Oblicz_ile_kandydatow(fstream& plik, int &ilosc_kandydatow)			//FUNKCJA LICZ¥CA KANDYDATÓW DO REKRUTACJI
{
	string linia_rekrutacja;
	int ilosc_pustych_lini_rekrutacja = 0;

	if (!plik.is_open())
	{
		cout << "Nie mozna otworzyc pliku!!!" << endl;
		exit(-1);
	}
	else
	{
		while (!plik.eof())
		{
			getline(plik, linia_rekrutacja);
			if (linia_rekrutacja == "\0")
			{
				ilosc_pustych_lini_rekrutacja++;					//zliczamy ilosc pustych lini
			}
		}
	}

	ilosc_kandydatow = ilosc_pustych_lini_rekrutacja + 1;		//kandydatów jest o jeden wiecej niz pustych lini
	linia_rekrutacja.clear();

	plik.seekg(0, ios::beg);
}

void skip_lines(std::fstream& pStream, size_t pLines)					// FUNKCJA OMIJAJ¥CA LINIE W PLIKU
{
	std::string s;
	for (; pLines; --pLines)
		std::getline(pStream, s);
}

string Sprawdz_jaka_matura(fstream& plik, int i)						// FUNKCJA SPRAWDZAJ¥CA JAK¥ MATURÊ PISA£ KANDYDAT
{
	int ilosc_przedmiotow;
	string matura;
	if (i > 0)
	{
		skip_lines(plik, 2);
	}
	streampos poprzednia_pozycja = plik.tellg();

	skip_lines(plik, 2);
	getline(plik, matura);
	plik >> ilosc_przedmiotow;

	plik.seekg(poprzednia_pozycja);

	return matura;
}