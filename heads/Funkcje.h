#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void wyczysc_plik();
void Oblicz_ile_kandydatow(fstream& plik, int &ilosc_kandydatow);
void skip_lines(std::fstream& pStream, size_t pLines);
string Sprawdz_jaka_matura(fstream& plik, int i);
