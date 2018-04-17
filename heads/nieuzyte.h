#pragma once
/*
student.h:

friend void Rekrutacja::Przepisz_dostanych(Student *s);




rekrutacja.h:

bool Czy_kandydat_sie_dostal()
{
if (dostal_sie)
{
return 1;
}
else
{
return 0;
}
}


void Przepisz_dostanych(Student *s)
{
ostringstream os;
for (int i = 0; i < 6; ++i)
{
int digit = rand() % 10;
os << digit;
}
string nr_albumu_s = os.str();

int nr_albumu = stoi(nr_albumu_s);

if (dostal_sie)
{
s->setName(imie);
s->setSurname(nazwisko);
s->setNr(nr_albumu);
}
}




main:

for (int i = 0; i < kandydaci.size(); i++)				//zapisanie studentow, którzy siê dostali do listy studentow
{
Rekrutacja *k = kandydaci[i];
if (k->Czy_kandydat_sie_dostal())
{
/*students.push_back(new Student());
ilosc_studentow++;

Student *ptr = students[ilosc_studentow - 1];

k->Przepisz_dostanych(ptr);
					}

*/