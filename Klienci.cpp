#include <iostream>
#include <string>
#include <vector>
#include "Obsluga.hpp"
#include "HR.hpp"
#include "Klienci.hpp"
#include "Los.hpp"
using namespace std;



void Klient::set_id_kl(unsigned int i) { id_klienta = i; }
void Klient::set_imie_kl(string i) { imie_klienta = i; }
void Klient::set_nazwisko_kl(string i) { nazwisko_klienta = i; }
void Klient::set_nr_tel_kl(string i) { nr_tel_klienta = i; }
unsigned int Klient::get_id_kl() { return id_klienta; }
string Klient::get_imie_kl() { return imie_klienta; }
string Klient::get_nazwisko_kl() { return nazwisko_klienta; }
string Klient::get_nr_tel_kl() { return nr_tel_klienta; }



Klienci::Klienci(int liczba) {
	if (liczba < 0) { liczba *= -1; }
	
	liczba_klientow = liczba;
	for (size_t i = 0; i < liczba_klientow; i++) {
		klienci.push_back(new Klient());
	}
	pozyskaj_klientow();
}


void Klienci::pozyskaj_klientow() {
	if (liczba_klientow > 0) {
		for (size_t i = 0; i < liczba_klientow; i++)
		{
			klienci[i]->set_id_kl(i+1);
			klienci[i]->set_imie_kl(losuj_imie());
			klienci[i]->set_nazwisko_kl(losuj_nazwisko());
			klienci[i]->set_nr_tel_kl(losuj_nr_tel());
		}
	}
}

unsigned int Klienci::ile_klientow() { return liczba_klientow; }

void Klienci::nowy_klient() {

	klienci.push_back(new Klient());
	liczba_klientow++;
	size_t i = klienci.size() - 1;
	klienci[i]->set_id_kl(i + 1);
	klienci[i]->set_imie_kl(losuj_imie());
	klienci[i]->set_nazwisko_kl(losuj_nazwisko());
	klienci[i]->set_nr_tel_kl(losuj_nr_tel());
	cout << "dodano klienta" << endl;

}
void Klienci::wyswietl_klienta(int i){
	cout <<"Imie Klienta: " <<klienci[i]->get_imie_kl() << endl;
	cout << "Nazwisko Klienta "<<klienci[i]->get_nazwisko_kl() << endl;
	cout << "Numer telefonu: "<<klienci[i]->get_nr_tel_kl() << endl;
}



Klienci::~Klienci() {
	for (auto x : klienci)
		delete x;
	liczba_klientow = 0;
}



ostream& operator<<(ostream& output, const Klienci& kl) {
	size_t j = kl.klienci.size();
		if (j > 0) {
			for (size_t i = 0; i < j; i++) {
				output << "id klienta: " << kl.klienci[i]->get_id_kl() << endl;
				output << "imie klienta: " << kl.klienci[i]->get_imie_kl() << endl;
				output << "nazwisko klienta: " << kl.klienci[i]->get_nazwisko_kl() << endl;
				output << "nr telefonu klienta: " << kl.klienci[i]->get_nr_tel_kl() << endl;
				output << endl;
			}
	} 
	return output;
}