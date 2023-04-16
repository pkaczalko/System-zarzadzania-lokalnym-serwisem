#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include "Los.hpp"
using namespace std;


#ifndef Magazyn_hpp
#define Magazyn_hpp



class Produkty {
private:
	unsigned int idProduktu;
	string nazwaProduktu;
	float cenaProduktu;
	unsigned int ilosc_na_stanie;
public:
	friend ostream& operator<<(ostream&, const Produkty&);
	void set_id(int);
	void set_nazwa(string);
	void set_cena(float);
	void set_ilosc(int);
	unsigned int get_id();
	string get_nazwa();
	float get_cena();
	unsigned int get_ilosc();
};




class Adres {
	string miejsce;
public:
	Adres();
	string get_adres();
};




class Magazyn {
	vector<Produkty*> produkty;
	static Adres* adres;
	unsigned int ilosc_produktow = 0;
	mutable int ile_magazynow{ 1 };
	unsigned int pojemnosc;
	void zapelnij_magazyn();
public:
	friend class interfejs;
	friend ostream& operator<<(ostream&, const Magazyn&);
	Produkty* operator[](int);
	void set_ile_magazynow(int)const;
	unsigned int rozmiar();
	unsigned int get_ilosc_produktow();
	unsigned int get_ile_magazynow()const;
	static string pokaz_adres();
	static void usun_adres();
	void wyswietl_stan();
	void zapisz(string);
	void dodaj_produkt();
	void usun_produkt(int);
	Magazyn(int, int);
	~Magazyn();
};

#endif