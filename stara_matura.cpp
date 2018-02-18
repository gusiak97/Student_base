#include "Stara_Matura.h"

using namespace std;

StaraMatura::StaraMatura() :Rekrutacja()
{
	ocena_z_matury = nullptr;
	nazwa = "";
}

StaraMatura::StaraMatura(string Imie, string Nazwisko, int IloscPrzedmiotow, float IloscPktRekrutacyjnych, float ProgKierunku)
	:Rekrutacja(Imie, Nazwisko, IloscPrzedmiotow, IloscPktRekrutacyjnych, ProgKierunku)
{
	przedmioty = new string[IloscPrzedmiotow];
	ocena_z_matury = new int[IloscPrzedmiotow];
}

StaraMatura::~StaraMatura()
{
	if (ocena_z_matury)
	{
		delete[] ocena_z_matury;
		ocena_z_matury = NULL;
	}
}

/////////////////////////////////////////////////////////////////////	
																				// METODA WCZYTUJ¥CA
void StaraMatura::Wczytaj(fstream& plik)
{
	getline(plik, imie);
	getline(plik, nazwisko);
	getline(plik, nazwa);
	plik >> ilosc_przedmiotow;

	przedmioty = new string[ilosc_przedmiotow];
	ocena_z_matury = new int[ilosc_przedmiotow];

	for (int i = 0; i < ilosc_przedmiotow; i++)
	{
		getline(plik, przedmioty[i], ':');
		plik >> ocena_z_matury[i];
	}
}

/////////////////////////////////////////////////////////////////////	
																				// METODA WYPISUJ¥CA
void StaraMatura::Wypisz(int i)
{
	cout << "------------------------------------------------\n";
	cout << "KANDYDAT NR [" << i + 1 << "]:\n";
	cout << "\nImie: " << imie;
	cout << "\nNazwisko: " << nazwisko;
	cout << "\nRodzaj matury: " << nazwa;

	for (int i = 0; i < ilosc_przedmiotow; i++)
	{
		cout << przedmioty[i] << ": " << ocena_z_matury[i];
	}
	cout << "\n\n";
}

/////////////////////////////////////////////////////////////////////	
																				// METODA LICZ¥CA ILOŒÆ PKT REKRUTACYJNYCH
void StaraMatura::Licz_ilosc_pkt_rekrutacyjnych()
{
	double matematyka_P = 0;
	double matematyka_R = 0;
	double fizyka_P = 0;
	double fizyka_R = 0;
	double informatyka_P = 0;
	double informatyka_R = 0;
	double jObcy_P = 0;
	double jObcy_U = 0;
	double polski = 0;
	double studium_talent = 0;

	for (int i = 0; i < ilosc_przedmiotow; i++)
	{
		if (przedmioty[i] == "\nmatematyka P")
			matematyka_P = ocena_z_matury[i];
		if (przedmioty[i] == "\nmatematyka R")
			matematyka_R = ocena_z_matury[i];
		if (przedmioty[i] == "\nfizyka P")
			fizyka_P = ocena_z_matury[i];
		if (przedmioty[i] == "\nfizyka R")
			fizyka_R = ocena_z_matury[i];
		if (przedmioty[i] == "\ninformatyka P")
			informatyka_P = ocena_z_matury[i];
		if (przedmioty[i] == "\ninformatyka R")
			informatyka_R = ocena_z_matury[i];
		if (przedmioty[i] == "\nangielski PISEMNY")
			jObcy_P = ocena_z_matury[i];
		if (przedmioty[i] == "\nangielski USTNY")
			jObcy_U = ocena_z_matury[i];
		if (przedmioty[i] == "\nniemiecki PISEMNY")
			jObcy_P = ocena_z_matury[i];
		if (przedmioty[i] == "\nniemiecki USTNY")
			jObcy_U = ocena_z_matury[i];
		if (przedmioty[i] == "\npolski")
			polski = ocena_z_matury[i];
		if (przedmioty[i] == "\nstudium talent")
			studium_talent = ocena_z_matury[i];
	}

	Licz_pkt_dla_scislych(matematyka_P);
	Licz_pkt_dla_scislych(matematyka_R);
	Licz_pkt_dla_scislych(fizyka_P);
	Licz_pkt_dla_scislych(fizyka_R);
	Licz_pkt_dla_scislych(informatyka_P);
	Licz_pkt_dla_scislych(informatyka_R);
	Licz_pkt_dla_scislych(jObcy_P);
	Licz_pkt_dla_scislych(jObcy_U);
	Licz_pkt_dla_humanistycznych(polski);

	double ST = 0;
	if ((studium_talent == 5) || (studium_talent == 6))
		ST = 50;
	if (studium_talent == 4)
		ST = 40;
	if (studium_talent == 3)
		ST = 30;


	double M1 = max(matematyka_P, matematyka_P + 1.5*matematyka_R);
	double M2 = max(matematyka_P + 1.5*matematyka_R, 2.5*matematyka_R);
	double M = max(M1, M2);

	double F1 = max(fizyka_P, fizyka_P + 1.5*fizyka_R);
	double F2 = max(fizyka_P + 1.5*fizyka_R, 2.5*fizyka_R);
	double F3 = max(F1, F2);

	double I1 = max(informatyka_P, informatyka_P + 1.5*informatyka_R);
	double I2 = max(informatyka_P + 1.5*informatyka_R, 2.5*informatyka_R);
	double I = max(I1, I2);

	double F = max(F3, I);

	double A = jObcy_P + jObcy_U;

	double P = polski;


	ilosc_pkt_rekrutacyjnych = M + F + 0.1*A + 0.1*P + ST;

	cout << "ILOSC PKT REKRUTACYJNYCH: " << ilosc_pkt_rekrutacyjnych;
	cout << "\nProg kierunku Teleinformatyka: " << prog_kierunku;

	if (ilosc_pkt_rekrutacyjnych >= prog_kierunku)
	{
		cout << "\n\n|| DOSTAL SIE ||\n\n\n";
		dostal_sie = 1;
	}
	else
	{
		cout << "\n\n|| NIE DOSTAL SIE ||\n\n\n";
		dostal_sie = 0;
	}
}
/////////////////////////////////////////////////////////////////////////

void Licz_pkt_dla_scislych(double &ocena)
{
	if (ocena == 6)
		ocena = 125;
	if (ocena == 5)
		ocena = 90;
	if (ocena == 4)
		ocena = 70;
	if (ocena == 3)
		ocena = 50;
	if (ocena == 2)
		ocena = 30;
}

void Licz_pkt_dla_humanistycznych(double &ocena)
{
	if (ocena == 6)
		ocena = 100;
	if (ocena == 5)
		ocena = 90;
	if (ocena == 4)
		ocena = 70;
	if (ocena == 3)
		ocena = 50;
	if (ocena == 2)
		ocena = 30;
}

