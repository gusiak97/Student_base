#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <vector>
#include <cctype>


using namespace std;
class Deficyt;

class Student {
public:
	string imie;
	string nazwisko;
	int nr_albumu;
	float srednia;
	string *przedmioty;
	string *przedmioty_deficyt;
	float *oceny;
	float *pkt_deficytu;
	int n;						//ilosc przedmiotów
	int ilosc_deficytu;

public:
	Student();

	Student(string newImie, string newNazwisko, int newNr, int newN);				// konstruktor z parametrami

	Student(const Student &s);														//konstruktor kopiuj¹cy

	~Student(); 																	//destruktor
	
	////////////////////////////////////////////
														//METODY WCZYTUJ¥CE DANE
	void Wczytaj(fstream& dane);													//wczytanie studenta z pliku
																				
	void setName(string newName);													// wczytywanie rêcze
	void setSurname(string newSurname);
	void setNr(int newNr);
	void setGrade(float newGrade);
	void setN(int newN);
	void addSubject(int newN, string addSubject);	
	void addGrade(int newN, float addGrade);
		
	////////////////////////////////////////////
														//METODY WYŒWIETLAJ¥CE / ZAPISUJ¥CE DANE
	void Przedstaw_sie(int i);
	void Wyswietl_Powyzej_Sredniej(float srednia_podana, int i);
	
	void zapisz_do_pliku();	

	///////////////////////////////////////////	
														// INNE FUNKCJE
	void Srednia();	
	void Licz_deficyt(Deficyt& d, int n, int nr_studenta);	
	
};

