#include "Rekrutacja.h"

using namespace std;

Rekrutacja::Rekrutacja()
{
	imie = "";
	nazwisko = "";
	ilosc_pkt_rekrutacyjnych = 0;
	prog_kierunku = 0;
	przedmioty = nullptr;
	prog_kierunku = 242;
}

Rekrutacja::Rekrutacja(string Imie, string Nazwisko, int IloscPrzedmiotow, float IloscPktRekrutacyjnych, float ProgKierunku)
{
	imie = Imie;
	nazwisko = Nazwisko;
	ilosc_przedmiotow = IloscPrzedmiotow;
	ilosc_pkt_rekrutacyjnych = IloscPktRekrutacyjnych;
	prog_kierunku = ProgKierunku;
}

Rekrutacja::Rekrutacja(Rekrutacja& r)
{
	imie = r.imie;
	nazwisko = r.nazwisko;
	ilosc_pkt_rekrutacyjnych = r.ilosc_pkt_rekrutacyjnych;
	prog_kierunku = r.prog_kierunku;

	if (ilosc_przedmiotow == 0)
	{
		przedmioty = nullptr;
	}
	else
	{
		przedmioty = new string[ilosc_przedmiotow];

		for (int i = 0; i < ilosc_przedmiotow; i++)
		{
			przedmioty[i] = r.przedmioty[i];
		}
	}
}

Rekrutacja::~Rekrutacja()
{
	if (ilosc_przedmiotow > 0)
	{
		if (przedmioty)
		{
			delete[] przedmioty;
			przedmioty = nullptr;

			ilosc_przedmiotow = 0;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

bool Rekrutacja::Czy_kandydat_sie_dostal()
{
	if (dostal_sie)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Rekrutacja::Przepisz_dostanych(Student *s)
{
	ostringstream os;
	for (int i = 0; i < 6; ++i)
	{
		int digit = rand() % 10;
		os << digit;
	}
	string nr_albumu_s = os.str();

	int nr_albumu = stoi(nr_albumu_s);

	if (dostal_sie)
	{
		s->setName(imie);
		s->setSurname(nazwisko);
		s->setNr(nr_albumu);
	}
}

