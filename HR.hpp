#include <iostream>
#include "Finanse.hpp"
#include <vector>
using namespace std;
#ifndef HR_hpp
#define HR_hpp

class Pracownik {
	int idPracownika;
	string rolaPracownika;
	string imiePracownika;
	string nazwiskoPracownika;
	class Numery {
		string numer_telefonu;
		string typ;
	public:
		friend class Pracownik;
	};
	Numery* numer;
	int ilosc_numerow;
	

public:
	Pracownik();
	void set_id(int id);
	void set_rola(string rola);
	void set_imie(string imie);
	void set_nazwisko(string nazwisko);
	int get_ilosc_nr();
	string get_numer(int i);
	string get_typ(int i);
	int get_id();
	string get_rola();
	string get_imie();
	string get_nazwisko();
	void ustaw_numery();
	~Pracownik();
};



class Pracownicy {
	vector<Pracownik*> pracownicy;
	vector<Pensje*> pensja;
	int ilosc_pracownikow;
	unsigned int ostatnie_id = 0;

	
public:
	friend class interfejs;
	friend ostream& operator<<(ostream&, const Pracownicy&);
	void operator()(string);
	Pracownik* operator[](int);
	Pracownicy& operator=(Pracownicy &a);
	Pracownicy() = default;
	Pracownicy(int);
	void zatrudnij_Pracownikow();
	void zmien_role();
	void wyswietl_Pracownikow();
	void wyswietl_Pracownika(int);
	void dodaj_Pracownika();
	void usun_Pracownika(int);
	void wyswietl_pensje();
	void zmien_Premie();
	void zmien_Pensje();
	Pracownicy(const Pracownicy& a);
	~Pracownicy();
};
#endif