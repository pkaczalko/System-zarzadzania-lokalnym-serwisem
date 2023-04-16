#include <iostream>
#include <string>
#include <ctime>
#include "HR.hpp"
#include "Magazyn.hpp"
using namespace std;
#ifndef Obsluga_hpp
#define Obsluga_hpp

class Obsluga {
public:
	virtual void dodaj(int,int) = 0;
	virtual void usun(int) = 0;
};

class Sprzedaz  {
private:
	unsigned int idPracownika;
	unsigned int idKlienta;
	unsigned int idSprzedazy;
	unsigned int idProduktu;
	string dataSprzedazy;
public:
	void set_id_klienta(unsigned int);
	void set_id_pracownika(unsigned int);
	void set_id_sprzedazy(unsigned int);
	void set_id_produktu(unsigned int);
	void set_data_sprzedazy(string);
	unsigned int get_id_klienta();
	unsigned int get_id_pracownika();
	unsigned int get_id_sprzedazy();
	unsigned int get_id_produktu();
	string get_data_sprzedazy();
};

class Sprzedaze :public Obsluga {
private:
	vector<Sprzedaz*> sprzedaz;
	unsigned int liczba_sprzedazy = 0;
public:
	friend class interfejs;
	Sprzedaze() = default;
	Sprzedaze(int);
	void sprzedaj(int,int);
	virtual void dodaj(int,int);
	virtual void usun(int);

	~Sprzedaze();
};




class Zlecenie {
private:
	unsigned int idPracownika;
	unsigned int idKlienta;
	unsigned int idZlecenia;
	unsigned int idProduktu;
	string dataPrzyjecia;
	string godzinaPrzyjecia;
	unsigned int nrUslugi;
public:
	void set_id_zlecenia(unsigned int);
	void set_id_produktu(unsigned int);
	void set_data(string);
	void set_godzina(string);
	void set_nr_uslugi(unsigned int);
	unsigned int get_id_zlecenia();
	unsigned int get_id_produktu();
	string get_data();
	string get_godzina();
	unsigned int get_nr_uslugi();
	void set_id_klienta(unsigned int);
	void set_id_pracownika(unsigned int);
	unsigned int get_id_klienta();
	unsigned int get_id_pracownika();
};

class Zlecenia :public Obsluga {
private:
	class Uslugi {
	private:
		string nazwaUslugi;
		float cenaUslugi;
	public:	
		friend class Zlecenia;
	};
	Uslugi* uslugi;
	vector<Zlecenie*> zlecenia;
	unsigned int liczba_zlecen = 0;
public:
	friend class interfejs;
	Zlecenia() = default;
	Zlecenia(int);
	void set_cena_uslugi(int, float);
	string get_nazwa_uslugi(int);
	float get_cena_uslugi(int);
	void zlec(int,int);
	virtual void dodaj(int,int);
	virtual void usun(int);
	~Zlecenia();
};



class Wizyta  {
private:
	unsigned int idKlienta;
	unsigned int idWizyty;
	string dataWizyty;
	string celWizyty;
	string godzinaWizyty;
public:
	unsigned int get_id_klienta();
	unsigned int get_id_wizyty();
	void set_data(string);
	void set_cel(string);
	string get_data();
	string get_cel();
	void set_id_klienta(unsigned int);
	void set_id_wizyty(unsigned int);
	void set_godzina_wizyty(string);
	string get_godzina_wizyty();
};


class Wizyty :public Obsluga {
private:
	vector<Wizyta*> wizyty;
	unsigned int ostatnie_id = 0;
	unsigned int liczba_wizyt = 0;
public:
	friend class interfejs;
	Wizyty()= default;
	Wizyty(int);
	bool czy_wolne(string,string);
	void zaplanuj(int,int);
	virtual void dodaj(int,int);
	virtual void usun(int);
	~Wizyty();
};

#endif
