#pragma once
#include "Student.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <vector>

using namespace std;
class Student;

class Deficyt
{
protected:

	string *przedmioty_lista;
	int *pkt_ects;
	int n;					//iloœæ przedmiotów
	
public:
	Deficyt();

	Deficyt(int newN);

	~Deficyt();
	
	///////////////////////////////////////////////////

	void Wczytaj_deficyt(fstream& plik, int n);
	void Wyswietl_deficyt(int n);

	friend void Student::Licz_deficyt(Deficyt& d, int n, int nr_studenta);
};



