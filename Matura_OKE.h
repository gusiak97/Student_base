#pragma once
#include"Rekrutacja.h"

using namespace std;

class MaturaOKE : public Rekrutacja
{
protected:
	float *procent_z_matury;
	string nazwa;

public:
	MaturaOKE();
	
	MaturaOKE(string Imie, string Nazwisko, int IloscPrzedmiotow, float IloscPktRekrutacyjnych, float ProgKierunku);
	
	~MaturaOKE();
	
	////////////////////////////////////////////

	void Wczytaj(fstream& plik);
	void Wypisz(int i);
	void Licz_ilosc_pkt_rekrutacyjnych();

};