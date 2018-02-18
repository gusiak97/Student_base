#include "Matura_OKE.h"

using namespace std;

MaturaOKE::MaturaOKE() :Rekrutacja()
{
	procent_z_matury = nullptr;
	nazwa = "";
}

MaturaOKE::MaturaOKE(string Imie, string Nazwisko, int IloscPrzedmiotow, float IloscPktRekrutacyjnych, float ProgKierunku)
	:Rekrutacja(Imie, Nazwisko, IloscPrzedmiotow, IloscPktRekrutacyjnych, ProgKierunku)
{
	przedmioty = new string[IloscPrzedmiotow];
	procent_z_matury = new float[IloscPrzedmiotow];
}

MaturaOKE::~MaturaOKE()
{
	if (procent_z_matury)
	{
		delete[] procent_z_matury;
		procent_z_matury = NULL;
	}
}

/////////////////////////////////////////////////////////////////////	
																				// METODA WCZYTUJ¥CA
void MaturaOKE::Wczytaj(fstream& plik)
{
	getline(plik, imie);
	getline(plik, nazwisko);
	getline(plik, nazwa);
	plik >> ilosc_przedmiotow;

	przedmioty = new string[ilosc_przedmiotow];
	procent_z_matury = new float[ilosc_przedmiotow];

	for (int i = 0; i < ilosc_przedmiotow; i++)
	{
		getline(plik, przedmioty[i], ':');
		plik >> procent_z_matury[i];
	}
}

/////////////////////////////////////////////////////////////////////	
																				// METODA WYPISUJ¥CA
void MaturaOKE::Wypisz(int i)
{
	cout << "------------------------------------------------\n";
	cout << "KANDYDAT NR [" << i + 1 << "]:\n";
	cout << "\nImie: " << imie;
	cout << "\nNazwisko: " << nazwisko;
	cout << "\nRodzaj matury: " << nazwa;

	for (int i = 0; i < ilosc_przedmiotow; i++)
	{
		cout << przedmioty[i] << ": " << procent_z_matury[i];
	}
	cout << "\n\n";
}

/////////////////////////////////////////////////////////////////////	
																				// METODA LICZ¥CA ILOŒÆ PKT REKRUTACYJNYCH
void MaturaOKE::Licz_ilosc_pkt_rekrutacyjnych()
{
	double matematyka_P = 0;
	double matematyka_R = 0;
	double fizyka = 0;
	double informatyka = 0;
	double jObcy_P = 0;
	double jObcy_R = 0;
	double polski_P = 0;
	double polski_R = 0;
	double studium_talent = 0;

	for (int i = 0; i < ilosc_przedmiotow; i++)
	{
		if (przedmioty[i] == "\nmatematyka P")
			matematyka_P = procent_z_matury[i];
		if (przedmioty[i] == "\nmatematyka R")
			matematyka_R = procent_z_matury[i];
		if (przedmioty[i] == "\nfizyka")
			fizyka = procent_z_matury[i];
		if (przedmioty[i] == "\ninformatyka")
			informatyka = procent_z_matury[i];
		if (przedmioty[i] == "\nangielski P")
			jObcy_P = procent_z_matury[i];
		if (przedmioty[i] == "\nangielski R")
			jObcy_R = procent_z_matury[i];
		if (przedmioty[i] == "\nniemiecki P")
			jObcy_P = procent_z_matury[i];
		if (przedmioty[i] == "\nniemiecki R")
			jObcy_R = procent_z_matury[i];
		if (przedmioty[i] == "\npolski P")
			polski_P = procent_z_matury[i];
		if (przedmioty[i] == "\npolski R")
			polski_R = procent_z_matury[i];
		if (przedmioty[i] == "\nstudium talent")
			studium_talent = procent_z_matury[i];
	}

	double M1 = max(matematyka_P, matematyka_P + 1.5*matematyka_R);
	double M2 = max(matematyka_P + 1.5*matematyka_R, 2.5*matematyka_R);
	double M = max(M1, M2);

	double F = max(2.5*fizyka, 2.5*informatyka);

	double A1 = max(jObcy_P, jObcy_P + 1.5*jObcy_R);
	double A2 = max(jObcy_P + 1.5*jObcy_R, 2.5*jObcy_R);
	double A = max(A1, A2);

	double P = max(polski_P, polski_R);

	double ST = 0;
	if ((studium_talent == 5) || (studium_talent == 6))
		ST = 50;
	if (studium_talent == 4)
		ST = 40;
	if (studium_talent == 3)
		ST = 30;

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
