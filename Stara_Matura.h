#pragma once
#include"Rekrutacja.h"

using namespace std;
void Licz_pkt_dla_scislych(double &ocena);
void Licz_pkt_dla_humanistycznych(double &ocena);



class StaraMatura : public Rekrutacja
{
protected:
	int *ocena_z_matury;
	string nazwa;

public:
	StaraMatura();

	StaraMatura(string Imie, string Nazwisko, int IloscPrzedmiotow, float IloscPktRekrutacyjnych, float ProgKierunku);

	~StaraMatura();

	/////////////////////////////////////////////////////

	void Wczytaj(fstream& plik);
	void Wypisz(int i);
	void Licz_ilosc_pkt_rekrutacyjnych();
};

