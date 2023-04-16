#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <ctime>
#include <iomanip>
#include "Magazyn.hpp"
#include "Los.hpp"
using namespace std;

	

	Adres* Magazyn::adres= new Adres;
	Adres::Adres() { miejsce = "Lipowa 43"; }
	string Adres::get_adres() { return miejsce; };
	string Magazyn::pokaz_adres() { return adres->get_adres(); }
	void Magazyn::usun_adres() { delete adres; }
	unsigned int Magazyn::rozmiar() { return produkty.size() - 1; }
	unsigned int Magazyn::get_ilosc_produktow() { return ilosc_produktow; };


	void Produkty::set_id(int id) { idProduktu = id; }
	void Produkty::set_nazwa(string nazwa) { nazwaProduktu = nazwa; }
	void Produkty::set_cena(float cena) { cenaProduktu = cena; }
	void Produkty::set_ilosc(int _ilosc) {ilosc_na_stanie = _ilosc; }
	unsigned int Produkty::get_id() { return idProduktu; }
	string Produkty::get_nazwa() { return nazwaProduktu; }
	float Produkty::get_cena() { return cenaProduktu; }
	unsigned int Produkty::get_ilosc() { return ilosc_na_stanie; }

	void Magazyn::zapelnij_magazyn() {

		  for(size_t i = 0; i < ilosc_produktow; i++) {
			produkty[i]->set_id(i);
			produkty[i]->set_nazwa(losuj_nazwe());
			produkty[i]->set_cena(losuj_float());
			produkty[i]->set_ilosc(losuj_int(25));
		}
	}

	void Magazyn::wyswietl_stan() {
		cout << Magazyn::pokaz_adres() << endl;;
		 for(size_t i = 0; i < ilosc_produktow; i++) {
			cout << "id: " << produkty[i]->get_id() << endl;
			cout << "nazwa: " << produkty[i]->get_nazwa() << endl;
			cout << "cena: " << produkty[i]->get_cena() << " zl" << endl;
			cout << "dostepna ilosc: " << produkty[i]->get_ilosc()<<" szt." << endl;

		}
		cout << "Procent zapelnienia: " << (ilosc_produktow / pojemnosc)*100<<" %" << endl;
	}

	void Magazyn::dodaj_produkt() {
		if (ilosc_produktow >= pojemnosc) {
			cout << "Nie mozesz dodac wiecej produktow, poniewaz magazyn jest pelny " << endl;
			}
		else {
			produkty.push_back(new Produkty);
			ilosc_produktow++;
			unsigned int id = produkty.size()-1;
			produkty[id]->set_id(id);
			produkty[id]->set_nazwa(losuj_nazwe());
			produkty[id]->set_cena(losuj_float());
			produkty[id]->set_ilosc(losuj_int(25));
			cout << "dodano produkt: " << endl;
			cout<<*produkty[id];
		}
	}
	void Magazyn::usun_produkt(int i) {
		cout << "wybrany produkt: " << endl;
		cout<<*produkty[i];
		string p; cout << "czy na pewno chcesz kontynuowac ? (Y): "; cin >> p;
		if (p == "Y" || p == "y") {
			auto it = produkty.begin() + i; //poczatek wektora + docelowy indeks do usuniecia
			ilosc_produktow--;
			produkty.erase(it);
			cout << "usunieto produkt" << endl;
		}
		else
		{
			cout << "nie usunieto produktu" << endl;
		}
	}

	

	void Magazyn::zapisz(string sciezka) {
			fstream plik;
			if (sciezka.find(".txt") == string::npos) { sciezka += "magazyn.txt"; }
			plik.open("magazyn.txt", ios::out);
			if (plik.good() == true)
			{
				 for(size_t i = 0; i < ilosc_produktow; i++) {
					plik << "id: " << produkty[i]->get_id() << ",";
					plik << "nazwa: " << produkty[i]->get_nazwa() << ",";
					plik << "cena: " << produkty[i]->get_cena() << " zl" << ",";
					plik << "dostepna ilosc: " << produkty[i]->get_ilosc()<<" szt." << endl;
				}
				cout << "Zakonczono zapis do pliku " + sciezka << endl;
			}
			else cout << "Wystapil problem z plikiem" << endl;
	
			plik.close();
		}
	

	void Magazyn::set_ile_magazynow(int ilosc = 1)const {
		ile_magazynow = ilosc;
	}
	unsigned int Magazyn::get_ile_magazynow()const { return ile_magazynow; }

	Magazyn::Magazyn(int ilosc,int _pojemnosc) {
		if (ilosc < 0) { ilosc *= -1; }
		if (_pojemnosc < 0) { _pojemnosc *= -1; }
		if (ilosc > _pojemnosc) { _pojemnosc = ilosc + 10; }
		ilosc_produktow = ilosc;
		pojemnosc = _pojemnosc;
		 for(size_t i = 0; i < ilosc_produktow; i++) {
			produkty.push_back(new Produkty);
		}
		zapelnij_magazyn();

	}
	Magazyn::~Magazyn() {
		for (auto y : produkty)
			delete y;
		ilosc_produktow = 0;
	}





	ostream& operator<<(ostream& output, const Magazyn& mag) {
		if (mag.produkty.size() > 0) {
			size_t j = mag.produkty.size();
			 for(size_t i = 0; i < j; i++) {
				output << "id: " << mag.produkty[i]->get_id() << endl;
				output << "nazwa: " << mag.produkty[i]->get_nazwa() << endl;
				output << "cena: " << mag.produkty[i]->get_cena() << " zl" << endl;
				output << "dostepna ilosc: " << mag.produkty[i]->get_ilosc()<<" szt." << endl;
			}
		} output<< "Procent zapelnienia: " << setprecision(2) << (float(mag.ilosc_produktow) / float(mag.pojemnosc)) * 100 << " %" << endl;
			return output;
		}

	Produkty* Magazyn::operator[](int i) {
		int ile = 1, pozostalo=6;
		while (true)
		{
			if (ile > 5) return produkty[0];
			else if (i > produkty.size() - 1 || i < 0) {
				ile++;
				pozostalo -= 1;
				cout << "zly indeks,pozostalo "<<pozostalo<<" prob, sproboj ponownie: ";
				cin >> i; continue;
			}
			else break;
		}
		cout << "id: " << produkty[i]->get_id() << endl;
		cout << "nazwa: " << produkty[i]->get_nazwa() << endl;
		cout << "cena: " << produkty[i]->get_cena() << " zl" << endl;
		cout << "dostepna ilosc: " << produkty[i]->get_ilosc() << " szt." << endl;
		
		return produkty[i];
	}

	ostream& operator<<(ostream& output, const Produkty& prod) {
		
				output << "id: " << prod.idProduktu << endl;
				output << "nazwa: " << prod.nazwaProduktu << endl;
				output << "cena: " << prod.cenaProduktu << " zl" << endl;
				output << "dostepna ilosc: " << prod.ilosc_na_stanie<<" szt." << endl;
	
		return output;
	}