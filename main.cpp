#include "Funkcje.h"
#include "Deficyt.h"
#include "Student.h"
#include "Rekrutacja.h"
#include "Matura_OKE.h"
#include "Stara_Matura.h"
#include "Matura_Miedzynarodowa_IB.h"

using namespace std;


int main()
{
	srand(time(NULL));

	string zakoncz;					//zmienna pomocnicza do konczenia programu
	int x;							//zmienna pomocnicza do wyboru z menu (switch(x))
	int ilosc_studentow;
	
///////////////////////////////////////////////////////////////////////////////////
																						// OBLICZENIE ILOSCI STUDENTOW
	fstream plik;
	plik.open("studenci.txt", ios::in);

	string linia;
	int ilosc_pustych_lini = 0;

	if (!plik.is_open())
	{
		cout << "Nie mozna otworzyc pliku!!!" << endl;
		exit(-1);
	}
	else
	{
		while (!plik.eof())
		{
			getline(plik, linia);
			if (linia == "\0")
			{
				ilosc_pustych_lini++;					//zliczamy ilosc pustych lini
			}
		}
	}

	ilosc_studentow = ilosc_pustych_lini + 1;		//studentow jest o jeden wiecej niz pustych lini
	linia.clear();


	fstream deficyt;										//obliczenie ilosci przedmiotow z przypisanymi pkt ects
	deficyt.open("deficyt.txt", ios::in);
	
	int ilosc_przedmiotow=0;

	if (!plik.is_open())
	{
		cout << "Nie mozna otworzyc pliku!!!" << endl;
		exit(-1);
	}
	else
	{
		while (!deficyt.eof())
		{
			getline(deficyt, linia);
			ilosc_przedmiotow++;
		}
	}

///////////////////////////////////////////////////////////////////////////////////////
																							// WCZYTANIE LISTY STUDENTOW
	plik.seekg(0, ios::beg);							//ustawienie pozycji iteratora w pliku na pocz¹tku
	deficyt.seekg(0, ios::beg);

	vector<Student*> students;

	for (int i = 0; i < ilosc_studentow; i++)
	{
		students.push_back(new Student());
	}

	for (int i = 0; i < students.size(); i++)
	{
		Student *ptr = students[i];

		ptr->Wczytaj(plik);		
		plik.ignore(2, '\0');

	}

	Deficyt lista_pkt_ects;														//wczytanie deficytu

	lista_pkt_ects.Wczytaj_deficyt(deficyt, ilosc_przedmiotow);
	
														
//////////////////////////////////////////////////////////////////////////////////////

																							// MENU

	do {
		system("cls");		
		cout << "\n////   LISTA DOSTEPNYCH OPERACJI   ////" << endl;				

		cout << "\n0 - wyswietlenie listy studentow\n"
			"1 - dodanie nowego studenta\n"
			"2 - usuwanie konkretnego studenta\n"
			"3 - wyswietlanie studentow powyzej podanej sredniej\n"
			"4 - liczenie deficytu\n"
			"5 - proces rekrutacji\n"
			"6 - zapisanie zawartosci bazy do pliku\n" 
			"\n7 - skasowanie calej zawartosci i zakonczenie programu\n"<< endl;

		cin >> x;

		if (cin.good())
		{
			switch (x)
			{
				//////////////////////////////////////////////////////////////////////
			case 0: {	system("cls");
				cout << "|||		WYSWIETLANIE LISTY STUDENTOW		|||" << endl;				//WYSWIETLANIE LISTY


				for (int i = 0; i < ilosc_studentow; i++)
				{
					Student *ptr = students[i];

					ptr->Przedstaw_sie(i);
					cout << "\n\n\n";
				}
				
			}break;

				//////////////////////////////////////////////////////////////////////////
			case 1: {	system("cls");
				cout << "|||		DODAWANIE NOWEGO STUDENTA		|||" << endl;						//DODAWANIE STUDENTA

				string newName;					//zmienne pomocnicze do wczytywania danych		
				string newSurname;
				int newNr;
				int newN;
				string subject;
				float grade;



				students.push_back(new Student());
				ilosc_studentow++;

				Student *ptr = students[ilosc_studentow - 1];

				cout << endl << "Podaj imie studenta nr " << (ilosc_studentow) << endl;
				cin >> newName;
				ptr->setName(newName);

				cout << "Podaj nazwisko studenta nr " << (ilosc_studentow) << endl;
				cin >> newSurname;
				ptr->setSurname(newSurname);

				cout << "Podaj numer albumu studenta nr " << (ilosc_studentow) << endl;
				cin >> newNr;
				ptr->setNr(newNr);

				cout << "Ile przedmiotow chcesz dodac studentowi nr " << (ilosc_studentow) << endl;
				cin >> newN;
				ptr->setN(newN);

				cout << "Jakie przedmioty i oceny chcesz dodac studentowi nr " << (ilosc_studentow) << endl;
				for (int m = 0; m < newN; m++)
				{
					cout << "Podaj nazwe przedmiotu: ";
					cin >> subject;
					ptr->addSubject(m, subject);

					cout << "Podaj ocene: ";
					cin >> grade;
					ptr->addGrade(m, grade);
				}
			} break;
				///////////////////////////////////////////////////////////////////////
			case 2: {	system("cls");
				cout << "|||		USUWANIE KONKRETNEGO STUDENTA		|||\n" << endl;							//USUWANIE STUDENTA

				int numer;

				cout << "Podaj numer studenta do usuniecia: ";
				cin >> numer;

				if ((numer < 1) || (numer > ilosc_studentow))
				{
					do
					{
						cout << "Podaj poprawny numer od 1 od " << ilosc_studentow <<": ";
						cin >> numer;
					} while ((numer <= 0) || (numer > ilosc_studentow));
				}
				
				if((numer>=1)&&(numer<=ilosc_studentow))
				{
					students.erase(students.begin() + numer - 1);
					cout << "\nStudent zostal usuniety!\n";
				}

				ilosc_studentow--;

			}break;
				///////////////////////////////////////////////////////////////////////
			case 3: {	system("cls");
				cout << "|||		WYSWIETLANIE STUDENTOW POWYZEJ PODANEJ SREDNIEJ		|||\n" << endl;		//POWYZEJ SREDNIEJ

				float srednia;
				cout << "podaj srednia: ";
				cin >> srednia;

				if (srednia < 0)
				{
					do
					{
						cout << "Podaj srednia wieksza od 0!: ";
						cin >> srednia;

					} while (srednia < 0);
				}
				
				if (srednia >= 0)
				{
					cout << "\nStudenci powyzej sredniej [ " << fixed << setprecision(2) << srednia << " ]:\n\n";
					for (int i = 0; i < ilosc_studentow; i++)
					{
						Student *ptr = students[i];

						ptr->Wyswietl_Powyzej_Sredniej(srednia, i);
						cout << "\n";
					}
				}
				
			}break;
				///////////////////////////////////////////////////////////////////////
			case 4: {	system("cls");
				cout << "|||		LICZENIE DEFICYTU		|||" << endl;									//LICZENIE DEFICYTU
				cout << "Lista przedmiotow i pkt ects:" << endl;

				lista_pkt_ects.Wyswietl_deficyt(ilosc_przedmiotow);

				cout << "\nDopuszczalna ilosc deficytu po II semestrze: [ 15 ]\n";

				for (int i = 0; i < ilosc_studentow; i++)
				{
					Student *ptr = students[i];

					ptr->Licz_deficyt(lista_pkt_ects, ilosc_przedmiotow, i);
				}

			}break;
				///////////////////////////////////////////////////////////////////////	
			case 5: {	system("cls");
				cout << "|||		PROCES REKRUTACJI		|||" << endl;							//PROCES REKRUTACJI

				fstream rekrutacja;
				rekrutacja.open("rekrutacja.txt", ios::in);

				int ilosc_kandydatow = 0;

				Oblicz_ile_kandydatow(rekrutacja, ilosc_kandydatow);	


				vector<Rekrutacja*> kandydaci;

				for (int i = 0; i <= ilosc_kandydatow; i++)
				{
					string matura = Sprawdz_jaka_matura(rekrutacja, i);

					if (matura == "matura OKE")
					{
						kandydaci.push_back(new MaturaOKE());

						Rekrutacja *ptr = kandydaci[i];

						ptr->Wczytaj(rekrutacja);
						ptr->Wypisz(i);
						ptr->Licz_ilosc_pkt_rekrutacyjnych();

					}

					if (matura == "stara matura")
					{
						kandydaci.push_back(new StaraMatura());

						Rekrutacja *ptr = kandydaci[i];

						ptr->Wczytaj(rekrutacja);
						ptr->Wypisz(i);
						ptr->Licz_ilosc_pkt_rekrutacyjnych();
					}

					if (matura == "matura miedzynarodowa IB")
					{
						kandydaci.push_back(new MaturaMiedzynarodowaIB());

						Rekrutacja *ptr = kandydaci[i];

						ptr->Wczytaj(rekrutacja);
						ptr->Wypisz(i);
						ptr->Licz_ilosc_pkt_rekrutacyjnych();
					}

				}

				for (int i = 0; i < kandydaci.size(); i++)				//zapisanie studentow, którzy siê dostali do listy studentow
				{
					Rekrutacja *k = kandydaci[i];
					if (k->Czy_kandydat_sie_dostal())
					{
						students.push_back(new Student());
						ilosc_studentow++;

						Student *ptr = students[ilosc_studentow - 1];

						k->Przepisz_dostanych(ptr);
					}
				}

				rekrutacja.close();

				for (int i = 0; i < kandydaci.size(); i++)				//zwalnianie pamieci
				{
					delete kandydaci[i];
				}

				plik.close();


			}break;
				///////////////////////////////////////////////////////////////////////
			case 6: {	system("cls");
				cout << "|||		ZAPIS LISTY DO PLIKU student_out.txt		||| " << endl;				//ZAPIS LISTY DO PLIKU

				wyczysc_plik();				//czyszczenie pliku

				for (int i = 0; i < ilosc_studentow; i++)
				{
					Student *ptr = students[i];

					ptr->zapisz_do_pliku();					//wywo³anie funkcji zapisz_do_pliku
				}
			}break;

				//////////////////////////////////////////////////////////////////////
			case 7: {	system("cls");
				cout << "|||		SKASOWANIE ZAWARTOSCI I ZAKONCZENIE		|||" << endl;			//SKASOWANIE I ZAKONCZENIE

				for (int i = 0; i < students.size(); i++)				//zwalnianie pamieci
				{
					delete students[i];
				}
				system("pause");
				return 0;
			}break;



				///////////////////////////////////////////////////////////////////////////////////////
			default: {
				cout << "Nie wybrano zadnej wartosci w wymienionych!!!";

			}break;
			}
		}
		
		else
		{
			cout << "PODAJ CYFRE !!!" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

				cout << "\nCzy chcesz zakonczyc program (T/N)?" << endl;
				cin >> zakoncz;

				if ((zakoncz == "T") || (zakoncz == "t"))
				{
					cout << endl << "////   PROGRAM ZAKONCZONY   ////" << endl;			//jesli "T" lub "t" - zakonczenie programu

					for (int i = 0; i < students.size(); i++)				//zwalnianie pamieci
					{
						delete students[i];
					}
					system("pause");
					return 0;
					break;

				}
				else if ((zakoncz != "T") && (zakoncz != "t") && (zakoncz != "N") && (zakoncz != "n"))
				{
					cout << "Wpisz poprawna litere (T/N)\n";				//zabezpieczenie przed blednym wpisywaniem zakonczenia
					cin >> zakoncz;
				}

			} while (zakoncz != "T");

			

//////////////////////////////////////////////////////////////////////////////////////////////////
																											// KONIEC

			for (int i = 0; i < students.size(); i++)				//zwalnianie pamieci
			{
				delete students[i];
			}
			plik.close();
	
			system("Pause");
			return 0;
}
	