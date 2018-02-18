#pragma once

#include "Student.h"

#include <limits>
#include <algorithm>
#include <sstream>
#include <cstdlib>		//generator liczb losowych
#include <ctime>


using namespace std;

class Rekrutacja
{
protected:
	string imie;
	string nazwisko;
	int ilosc_przedmiotow;

	string *przedmioty;
	float ilosc_pkt_rekrutacyjnych;
	float prog_kierunku;
	bool dostal_sie;

public:

	virtual void Licz_ilosc_pkt_rekrutacyjnych() = 0;
	virtual void Wczytaj(fstream& plik) = 0;
	virtual void Wypisz(int i) = 0;

	Rekrutacja();

	Rekrutacja(string Imie, string Nazwisko, int IloscPrzedmiotow, float IloscPktRekrutacyjnych, float ProgKierunku);	

	Rekrutacja(Rekrutacja& r);
	
	virtual ~Rekrutacja();

	///////////////////////////////////////////////

	bool Czy_kandydat_sie_dostal();	
	void Przepisz_dostanych(Student *s);

	friend string Sprawdz_jaka_matura(fstream& plik, int i);
};
	
