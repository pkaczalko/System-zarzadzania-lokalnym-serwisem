#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include "Los.hpp"
#include "Finanse.hpp"
#include "HR.hpp"
#include "Magazyn.hpp"
#include "Obsluga.hpp"
#include "Klienci.hpp"

using namespace std;


#ifndef Interfejs_hpp
#define Interfejs_hpp

class interfejs{
	Magazyn* magazyn_o;
	Pracownicy* pracownicy;
	Sprzedaze* sprzedaz;
	Wizyty* wizyty;
	Zlecenia* zlecenia;
	Klienci* klienci;

public:
	interfejs() ;
	void start();
	void magazyn();
	void hr();
	void serwis();
	void statystyki();
	void wybor(); 
	void obsluga();
	void wyswietl_zlecenia();
	void wykonaj_zlecenie();
	void aktualizuj_zlecenie();
	void stat_sprzedazy();
	void stat_pracownikow();
	unsigned int znajdz(char,int);
	int wal();


	~interfejs();
};










#endif