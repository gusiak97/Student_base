#include "Student.h"
#include "Deficyt.h"

using namespace std;

Student::Student()
{
	imie = "";
	nazwisko = "";
	nr_albumu = 0;
	srednia = 0.0;
	przedmioty = nullptr;
	oceny = nullptr;
	n = 0;
	ilosc_deficytu = 0;
}

Student::Student(string newImie, string newNazwisko, int newNr, int newN)				// konstruktor z parametrami
{
	imie = newImie;
	nazwisko = newNazwisko;
	nr_albumu = newNr;
	n = newN;

	przedmioty = new string[n];
	oceny = new float[n];
}


Student::Student(const Student &s)		//konstruktor kopiuj¹cy
{
	imie = s.imie;
	nazwisko = s.nazwisko;
	nr_albumu = s.nr_albumu;
	n = s.n;

	if (n == 0)
	{
		przedmioty = NULL;
		oceny = NULL;
	}
	else
	{
		przedmioty = new string[n];

		for (int i = 0; i < n; i++)
			przedmioty[i] = s.przedmioty[i];

		oceny = new float[n];

		for (int i = 0; i < n; i++)
			oceny[i] = s.oceny[i];
	}
}


Student::~Student()							//destruktor
{			
	if (przedmioty)
	{
		delete[] przedmioty;
		przedmioty = NULL;
	}

	if (oceny)
	{
		delete[] oceny;
		oceny = NULL;
	}
}

////////////////////////////////////////////////////////////////////////
																				// METODY WCZYTUJ¥CE DANE
void Student::Wczytaj(fstream& dane)			//wczytanie studenta z pliku
{

	if (dane.is_open())
	{
		getline(dane, imie);
		getline(dane, nazwisko);
		dane >> nr_albumu;
		dane >> n;

		przedmioty = new string[n];
		oceny = new float[n];

		for (int i = 0; i < n; i++)
		{
			getline(dane, przedmioty[i], ':');
			dane >> oceny[i];
		}
		dane >> ilosc_deficytu;
	}
}

// WCZYTYWANIE RÊCZNE
void Student::setName(string newName) {
	imie = newName;

	for (int i = 0; i < newName.length(); i++)					//zabezpieczenie
	{
		if ((newName[i] < 65) || (newName[i] > 123))
		{
			if ((newName[i] > 90) || (newName[i] < 97))
			{
				cout << "ZLE DANE: Imie powinno skaldac sie tylko z liter!!!\n Podaj poprawne imie:  ";
				cin >> newName;
				imie = newName;
			}
		}
		else
		{
			continue;
		}
	}
}

void Student::setSurname(string newSurname) {
	nazwisko = newSurname;

	for (int i = 0; i < newSurname.length(); i++)				//zabezpieczenie
	{
		if ((newSurname[i] < 65) || (newSurname[i] > 123))
		{
			if ((newSurname[i] > 90) || (newSurname[i] < 97))
			{
				cout << "ZLE DANE: Nazwisko powinno skaldac sie tylko z liter!!!\n Podaj poprawne nazwisko:  ";
				cin >> newSurname;
				nazwisko = newSurname;
			}
		}
		else
		{
			continue;
		}
	}
}

void Student::setNr(int newNr) {
	nr_albumu = newNr;
}

void Student::setGrade(float newGrade) {
	srednia = newGrade;
}

void Student::setN(int newN) {
	n = newN;
	przedmioty = new string[newN];
	oceny = new float[newN];
}

void Student::addSubject(int newN, string addSubject){
	przedmioty[newN] = addSubject;
}

void Student::addGrade(int newN, float addGrade){
	
	oceny[newN] = addGrade;
}

//////////////////////////////////////////////////////////////////////////
																				// METODY WYŒWIETLAJ¥CE / ZAPISUJ¥CE DANE
void Student::Przedstaw_sie(int i)														
{
	cout << "\nImie Studenta [" << i + 1 << "]: " << imie;
	cout << "\nNazwisko Studenta [" << i + 1 << "]: " << nazwisko;
	cout << "\nNr albumu Studenta [" << i + 1 << "]: " << nr_albumu;
	if (przedmioty)
	{
		cout << "\nPrzedmioty Studenta [" << i + 1 << "]: \n";

		for (int j = 0; j < n; j++)
		{
			cout << "\t\t\t" << przedmioty[j] << ": " << oceny[j];
		}
		Srednia();
		cout << "\n\nSrednia Studenta[" << i + 1 << "]: " << fixed << setprecision(2) << srednia;
	}
}

void Student::Wyswietl_Powyzej_Sredniej(float srednia_podana, int i)
{
	Srednia();
	if (srednia > srednia_podana)
	{
		cout << "\nImie Studenta [" << i + 1 << "]: " << imie;
		cout << "\nNazwisko Studenta [" << i + 1 << "]: " << nazwisko;
		cout << "\nNr albumu Studenta [" << i + 1 << "]: " << nr_albumu;
		cout << "\n\nSrednia Studenta[" << i + 1 << "]: " << fixed << setprecision(2) << srednia;
	}
}

void Student::zapisz_do_pliku()											
{
	ofstream plik("student_out.txt", ios::out | ios::app);
	if (plik.is_open())
	{
		plik << imie << endl;
		plik << nazwisko << endl;
		plik << nr_albumu << endl;
		plik << n;

		for (int j = 0; j < n; j++)
		{
			plik << przedmioty[j] << ": " << oceny[j];
		}
		Srednia();
		if (srednia>=0)
		{
			plik << endl << fixed << setprecision(2) << srednia;
		}

		plik << endl << endl;
	}
	plik.close();
}

////////////////////////////////////////////////////////	
																// INNE FUNKCJE
void Student::Srednia()
{
	float srednia1 = 0;
	float suma_ocen = 0;

	for (int i = 0; i < n; i++)
	{
		suma_ocen += oceny[i];
	}

	srednia1 = suma_ocen / n;
	srednia = srednia1;
}
/////////////////////////////////////////////////////////////////////////
																					//	DEFICYT
void Student::Licz_deficyt(Deficyt& d, int n, int nr_studenta)
{
	if (oceny)
	{
		string *tab_niezaliczonych;							//tablica pomocnicza przpisuj¹ca niezaliczone przedmioty
		tab_niezaliczonych = new string[n];

		int k = 0;

		for (int i = 0; i < n; i++)							//przepisywanie niezaliczonych przedmiotów
		{
			if (oceny[i] < 3)
			{
				tab_niezaliczonych[k] = przedmioty[i];
				k++;
			}
		}

		cout << "\n\nNiezaliczone przedmioty studenta nr [" << nr_studenta + 1 << "]:";
		if (k == 0)					//jesli brak niezaliczonych
		{
			cout << "-";
		}

		for (int i = 0; i < k; i++)					//wypisanie niezaliczonych
		{
			cout << tab_niezaliczonych[i];
		}


		cout << "\n\nIlosc deficytu po I semestrze: " << ilosc_deficytu << endl;;
		int ilosc_deficytu_2 = 0;

		for (int i = 0; i < k; i++)										//policzenie deficytu
		{
			for (int j = 0; j < n; j++)
			{
				if (tab_niezaliczonych[i] == d.przedmioty_lista[j])
				{
					ilosc_deficytu_2 += d.pkt_ects[j];
				}
			}
		}
		cout << "Ilosc deficytu po II semestrze: " << ilosc_deficytu_2 << endl;;
		ilosc_deficytu += ilosc_deficytu_2;

		if (ilosc_deficytu != 0)
		{
			cout << "Ilosc CALKOWITEGO deficytu studenta nr [" << nr_studenta + 1 << "]: " << ilosc_deficytu << endl;

			if (ilosc_deficytu > 15)
				cout << "\n|| STUDENT ZAGROZONY ||\n";
		}
	}	
}





