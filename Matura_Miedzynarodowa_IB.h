#pragma once
#include"Rekrutacja.h"

using namespace std;
void Licz_pkt_dla(double &ocena);


class MaturaMiedzynarodowaIB : public Rekrutacja
{
protected:
	int *ocena_z_matury;
	string nazwa;

public:
	MaturaMiedzynarodowaIB();

	MaturaMiedzynarodowaIB(string Imie, string Nazwisko, int IloscPrzedmiotow, float IloscPktRekrutacyjnych, float ProgKierunku);

	~MaturaMiedzynarodowaIB();

	///////////////////////////////////////////

	void Wczytaj(fstream& plik);
	void Wypisz(int i);
	void Licz_ilosc_pkt_rekrutacyjnych();
};


