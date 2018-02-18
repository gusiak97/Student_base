#include "Matura_Miedzynarodowa_IB.h"

using namespace std;

MaturaMiedzynarodowaIB::MaturaMiedzynarodowaIB() :Rekrutacja()
{
	ocena_z_matury = nullptr;
	nazwa = "";
}

MaturaMiedzynarodowaIB::MaturaMiedzynarodowaIB(string Imie, string Nazwisko, int IloscPrzedmiotow, float IloscPktRekrutacyjnych, float ProgKierunku)
	:Rekrutacja(Imie, Nazwisko, IloscPrzedmiotow, IloscPktRekrutacyjnych, ProgKierunku)
{
	przedmioty = new string[IloscPrzedmiotow];
	ocena_z_matury = new int[IloscPrzedmiotow];
}

MaturaMiedzynarodowaIB::~MaturaMiedzynarodowaIB()
{
	if (ocena_z_matury)
	{
		delete[] ocena_z_matury;
		ocena_z_matury = NULL;
	}
}

/////////////////////////////////////////////////////////////////////	
																					// METODA WCZYTUJ¥CA
void MaturaMiedzynarodowaIB::Wczytaj(fstream& plik)
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
void MaturaMiedzynarodowaIB::Wypisz(int i)
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
void MaturaMiedzynarodowaIB::Licz_ilosc_pkt_rekrutacyjnych()
{
	double matematyka_SL = 0;
	double matematyka_HL = 0;
	double fizyka_SL = 0;
	double fizyka_HL = 0;
	double informatyka_SL = 0;
	double informatyka_HL = 0;
	double jObcy_SL = 0;
	double jObcy_HL = 0;
	double polski_SL = 0;
	double polski_HL = 0;
	double studium_talent = 0;

	for (int i = 0; i < ilosc_przedmiotow; i++)
	{
		if (przedmioty[i] == "\nmatematyka SL")
			matematyka_SL = ocena_z_matury[i];
		if (przedmioty[i] == "\nmatematyka HL")
			matematyka_HL = ocena_z_matury[i];
		if (przedmioty[i] == "\nfizyka SL")
			fizyka_SL = ocena_z_matury[i];
		if (przedmioty[i] == "\nfizyka HL")
			fizyka_HL = ocena_z_matury[i];
		if (przedmioty[i] == "\ninformatyka SL")
			informatyka_SL = ocena_z_matury[i];
		if (przedmioty[i] == "\ninformatyka HL")
			informatyka_HL = ocena_z_matury[i];
		if (przedmioty[i] == "\nangielski SL")
			jObcy_SL = ocena_z_matury[i];
		if (przedmioty[i] == "\nangielski HL")
			jObcy_HL = ocena_z_matury[i];
		if (przedmioty[i] == "\nniemiecki SL")
			jObcy_SL = ocena_z_matury[i];
		if (przedmioty[i] == "\nniemiecki HL")
			jObcy_HL = ocena_z_matury[i];
		if (przedmioty[i] == "\npolski SL")
			polski_SL = ocena_z_matury[i];
		if (przedmioty[i] == "\npolski HL")
			polski_HL = ocena_z_matury[i];
		if (przedmioty[i] == "\nstudium talent")
			studium_talent = ocena_z_matury[i];
	}

	Licz_pkt_dla(matematyka_SL);
	Licz_pkt_dla(matematyka_HL);
	Licz_pkt_dla(fizyka_SL);
	Licz_pkt_dla(fizyka_HL);
	Licz_pkt_dla(informatyka_SL);
	Licz_pkt_dla(informatyka_HL);
	Licz_pkt_dla(jObcy_SL);
	Licz_pkt_dla(jObcy_HL);
	Licz_pkt_dla(polski_SL);
	Licz_pkt_dla(polski_HL);

	double ST = 0;
	if ((studium_talent == 5) || (studium_talent == 6))
		ST = 50;
	if (studium_talent == 4)
		ST = 40;
	if (studium_talent == 3)
		ST = 30;

	double M = max(matematyka_SL, 2.5*matematyka_HL);

	double F = max(fizyka_SL, 2.5*fizyka_HL);

	double I = max(informatyka_SL, 2.5*informatyka_HL);

	double F_C = max(F, I);

	double A = max(jObcy_SL, 2.5*jObcy_HL);

	double P = max(polski_SL, polski_HL);


	ilosc_pkt_rekrutacyjnych = M + F_C + 0.1*A + 0.1*P + ST;

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

///////////////////////////////////////////////////////////////////////////////
void Licz_pkt_dla(double &ocena)
{
	if (ocena == 7)
		ocena = 100;
	if (ocena == 6)
		ocena = 86;
	if (ocena == 5)
		ocena = 72;
	if (ocena == 4)
		ocena = 58;
	if (ocena == 3)
		ocena = 44;
	if (ocena == 2)
		ocena = 30;
}
