#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Obsluga.hpp"
#include "HR.hpp"
#include "Magazyn.hpp"
#include "Los.hpp"
using namespace std;


void Sprzedaz::set_id_klienta(unsigned int id) { idKlienta = id; }
void Sprzedaz::set_id_pracownika(unsigned int id) { idPracownika = id; }
void Sprzedaz::set_id_sprzedazy(unsigned int id) { idSprzedazy = id; }
void Sprzedaz::set_id_produktu(unsigned int id) { idProduktu = id; }
void Sprzedaz::set_data_sprzedazy(string data) { dataSprzedazy = data; }
unsigned int Sprzedaz::get_id_klienta() { return idKlienta; }
unsigned int Sprzedaz::get_id_pracownika() { return idPracownika; }
unsigned int Sprzedaz::get_id_sprzedazy() { return idSprzedazy; }
unsigned int Sprzedaz::get_id_produktu() { return idProduktu; }
string Sprzedaz::get_data_sprzedazy() { return dataSprzedazy; }


void Zlecenie::set_id_zlecenia(unsigned int id) { idZlecenia = id; }
void Zlecenie::set_id_produktu(unsigned int id) { idPracownika = id; }
void Zlecenie::set_id_klienta(unsigned int id) { idKlienta = id; }
void Zlecenie::set_id_pracownika(unsigned int id) { idPracownika = id; }
void Zlecenie::set_data(string data) { dataPrzyjecia = data; }
void Zlecenie::set_godzina(string h) { godzinaPrzyjecia = h; }
void Zlecenie::set_nr_uslugi(unsigned int n) { nrUslugi = n; }
unsigned int Zlecenie::get_id_zlecenia() { return idZlecenia; }
unsigned int Zlecenie::get_id_produktu() { return idProduktu; }
string Zlecenie::get_data() { return dataPrzyjecia; }
string Zlecenie::get_godzina() { return godzinaPrzyjecia; }
unsigned int Zlecenie::get_nr_uslugi() { return nrUslugi; }
unsigned int Zlecenie::get_id_klienta() { return idKlienta; }
unsigned int Zlecenie::get_id_pracownika() { return idPracownika; }
string Zlecenia::get_nazwa_uslugi(int i) { return uslugi[i].nazwaUslugi; }
float Zlecenia::get_cena_uslugi(int i) { return uslugi[i].cenaUslugi; }
unsigned int Wizyta::get_id_klienta() { return idKlienta; }
unsigned int Wizyta::get_id_wizyty() { return idWizyty; }
void Wizyta::set_data(string d) { dataWizyty = d; }
void Wizyta::set_cel(string c) { celWizyty = c; }
string Wizyta::get_data() { return dataWizyty; }
string Wizyta::get_cel() { return celWizyty; }
void Wizyta::set_id_klienta(unsigned int id) { idKlienta = id; }
void Wizyta::set_id_wizyty(unsigned int id) { idWizyty = id; }
void Wizyta::set_godzina_wizyty(string c) { godzinaWizyty = c; }
string Wizyta::get_godzina_wizyty() { return godzinaWizyty; }





Sprzedaze::Sprzedaze(int liczba) {
	liczba_sprzedazy = liczba;
	for (size_t i = 0; i < liczba_sprzedazy; i++)
		sprzedaz.push_back(new Sprzedaz);
	
}
Sprzedaze::~Sprzedaze() {
	for (auto x : sprzedaz)
		delete x;
	liczba_sprzedazy = 0;
}




Wizyty::Wizyty(int liczba) {
	liczba_wizyt = liczba;
	for (size_t i = 0; i < liczba_wizyt; i++)
		wizyty.push_back(new Wizyta);
}

Wizyty::~Wizyty() {
	for (auto x : wizyty)
		delete x;
	liczba_wizyt = 0;
}


	Zlecenia::Zlecenia(int liczba) {
		liczba_zlecen = liczba;
		for (size_t i = 0; i < liczba_zlecen; i++)
			zlecenia.push_back(new Zlecenie);
		uslugi = new Uslugi[48];
		fstream plik;
		plik.open("pliki/Uslugi.txt", ios::in);
		if (plik.good() == true)
		{
			string wiersz;
			for (int i = 0; i < 48; i++) {
				getline(plik, wiersz,':');
				uslugi[i].nazwaUslugi = wiersz;
				getline(plik, wiersz, ':');
				uslugi[i].cenaUslugi = stoi(wiersz);
			}
			plik.close();
		}
	
	}

	Zlecenia::~Zlecenia() {
		for (auto x : zlecenia)
			delete x;
		delete [] uslugi;
		uslugi = nullptr;
		liczba_zlecen = 0;
	}
	

	void Sprzedaze::sprzedaj(int ile_klientow = 5,int ile_produktow = 5){
		if (liczba_sprzedazy > 0) {
			for (int i = 0; i < liczba_sprzedazy; i++) {
				sprzedaz[i]->set_data_sprzedazy(losuj_date());
				sprzedaz[i]->set_id_klienta(losuj_int(ile_klientow)+1);
				sprzedaz[i]->set_id_pracownika(losuj_int(15)+11);
				sprzedaz[i]->set_id_produktu(losuj_int(ile_produktow));
				sprzedaz[i]->set_id_sprzedazy(i);
			}

		}
	}
	
	void Zlecenia::set_cena_uslugi(int a, float r) { uslugi[a].cenaUslugi = r; }



	bool Wizyty::czy_wolne(string data,string godzina){
	for(auto j:wizyty)
		if (j->get_data() == data && j->get_godzina_wizyty() == godzina) { return false; }
	return true;
	}


	void Wizyty::zaplanuj(int ile_klientow = 5, int ile_produktow = 5) {
		string data,godzina;
		if (liczba_wizyt > 0) {
		wizyty[0]->set_data(losuj_date("wizyta"));
		wizyty[0]->set_godzina_wizyty(losuj_godzine());
			for (int i = 0; i < liczba_wizyt; i++) {
				ostatnie_id++;
				wizyty[i]->set_id_klienta(losuj_int(ile_klientow+1));
				wizyty[i]->set_id_wizyty(ostatnie_id);
				wizyty[i]->set_cel(losuj_cel());
				if (i > 0) {
					data = losuj_date("wizyta");
					godzina = losuj_godzine();
					while (!czy_wolne(data, godzina)) {
						data = losuj_date("wizyta");
						godzina = losuj_godzine();
					}
					wizyty[i]->set_data(data);
					wizyty[i]->set_godzina_wizyty(godzina);

				}
			}
		}
	}

	void Wizyty::usun(int i) {
		if (i > wizyty.size() - 1 || i < 0) { cout << "blad" << endl; }
		else {
			auto it = wizyty.begin() + i; 
			wizyty.erase(it);
			liczba_wizyt--;
			cout << "usunieto wizyte" << endl;
		}
	}


	void Zlecenia::zlec(int ile_klientow = 5, int ile_produktow = 5) {
		if (liczba_zlecen > 0)
		{
			for (size_t i = 0; i < liczba_zlecen; i++) {
				zlecenia[i]->set_id_zlecenia(i);
				zlecenia[i]->set_id_produktu(losuj_int(ile_produktow));
				zlecenia[i]->set_data(losuj_date());
				zlecenia[i]->set_godzina(losuj_godzine());
				zlecenia[i]->set_nr_uslugi(losuj_int(48));
				zlecenia[i]->set_id_klienta(losuj_int(ile_klientow) + 1);
				zlecenia[i]->set_id_pracownika(losuj_int(5) + 6);
			}
		}
	}

	void Zlecenia::usun(int i) {
		i += 1;
		if (i > zlecenia.size() - 1 || i < 0) { cout << "blad" << endl; }
		else {
			auto it = zlecenia.begin() + i; //poczatek wektora + docelowy indeks do usuniecia - korekta id
			zlecenia.erase(it);
			liczba_zlecen--;
			cout << "usunieto zlecenie" << endl;
		}
	}




	void Sprzedaze::dodaj(int ile_klientow=5 ,int ile_produktow = 5) {
		size_t j = sprzedaz.size();
		sprzedaz.push_back(new Sprzedaz);
		liczba_sprzedazy++;
		sprzedaz[j]->set_data_sprzedazy(losuj_date());
		sprzedaz[j]->set_id_klienta(losuj_int(ile_klientow) + 1);
		sprzedaz[j]->set_id_pracownika(losuj_int(15) + 11);
		sprzedaz[j]->set_id_produktu(losuj_int(ile_produktow));
		sprzedaz[j]->set_id_sprzedazy(j);
		cout << "dodano sprzedaz" << endl;


	}

	void Sprzedaze::usun(int i) {
		if (i > sprzedaz.size() - 1 || i < 0) { cout << "blad" << endl; }
		else {
			auto it = sprzedaz.begin() + i; //poczatek wektora + docelowy indeks do usuniecia - korekta id
			sprzedaz.erase(it);
			liczba_sprzedazy--;
			cout << "usunieto sprzedaz" << endl;
		}
	}


	void Wizyty::dodaj(int ile_klientow = 5, int ile_produktow = 5) {
		size_t i = wizyty.size();
		string data, godzina;
		wizyty.push_back(new Wizyta);
		liczba_wizyt++;
		ostatnie_id++;
		wizyty[i]->set_id_wizyty(ostatnie_id);
		wizyty[i]->set_id_klienta(losuj_int(ile_klientow + 1));
		wizyty[i]->set_cel(losuj_cel());
		if (i > 0) {
			data = losuj_date("wizyta");
			godzina = losuj_godzine();
			while (!czy_wolne(data, godzina))
				data = losuj_date("wizyta");
			wizyty[i]->set_data(losuj_date("wizyta"));
		}
		cout << "dodano wizyte" << endl;
	}


		void Zlecenia::dodaj(int ile_klientow = 5, int ile_produktow = 5) {
			size_t i = zlecenia.size();
			zlecenia.push_back(new Zlecenie);
			liczba_zlecen++;
			zlecenia[i]->set_id_zlecenia(i);
			zlecenia[i]->set_id_produktu(losuj_int(ile_produktow));
			zlecenia[i]->set_data(losuj_date());
			zlecenia[i]->set_godzina(losuj_godzine());
			zlecenia[i]->set_nr_uslugi(losuj_int(48));
			zlecenia[i]->set_id_klienta(losuj_int(ile_klientow) + 1);
			zlecenia[i]->set_id_pracownika(losuj_int(5) + 6);
			cout << "dodano zlecenie" << endl;
		
		}






