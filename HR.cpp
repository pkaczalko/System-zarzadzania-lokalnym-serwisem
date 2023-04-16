#include <iostream>
#include <string>
#include <vector>
#include "Finanse.hpp"
#include "HR.hpp"
#include "Los.hpp"
using namespace std;


	Pracownik::Pracownik() :ilosc_numerow((rand() % 5) + 1) {
		numer = new Numery[ilosc_numerow];
		ustaw_numery();
	}

		void Pracownik::set_id(int id) { idPracownika = id; }
		void Pracownik::set_rola(string rola) { rolaPracownika = rola; }
		void Pracownik::set_imie(string imie) { imiePracownika = imie; }
		void Pracownik::set_nazwisko(string nazwisko) { nazwiskoPracownika = nazwisko; }
		int Pracownik::get_ilosc_nr() { return ilosc_numerow; }
		string Pracownik::get_numer(int i) { return numer[i].numer_telefonu; }
		string Pracownik::get_typ(int i) { return numer[i].typ; }
		int Pracownik::get_id() { return idPracownika; }
		string Pracownik::get_rola() { return rolaPracownika; }
		string Pracownik::get_imie() { return imiePracownika; }
		string Pracownik::get_nazwisko() { return nazwiskoPracownika; }

		void Pracownik::ustaw_numery() {
		string tp;
		for (int i = 0; i < ilosc_numerow; i++) {
			string nr = losuj_nr_tel();
			if ((rand() % 10) % 2 == 0) { tp = "komorka"; }
			else { tp = "stacjonarny"; }
			numer[i].numer_telefonu = nr; numer[i].typ = tp;
		}
	}
		Pracownik::~Pracownik() {
		delete[] numer;
		numer = nullptr;
		ilosc_numerow = 0;
	}
		//-------------------------Pracownicy-------------------------------------------



//-----------------------------Operatory------------------------------------------------------------------------------
	
	Pracownik* Pracownicy::operator[](int i) {
		int ile = 1, pozostalo = 6;
		while (true)
		{
			if (ile > 5) return pracownicy[0];
			else if (i > pracownicy.size() - 1 || i < 0) {
				ile++;
				pozostalo -= 1;
				cout << "zly indeks,pozostalo " << pozostalo << " prob, sproboj ponownie: ";
				cin >> i; continue;
			}
			else break;
		}
		cout << "id: " << pracownicy[i]->get_id() << endl;
		cout << "imie: " << pracownicy[i]->get_imie() << endl;
		cout << "nazwisko: " << pracownicy[i]->get_nazwisko() << endl;
		cout << "rola: " << pracownicy[i]->get_rola() << endl;
		for (int j = 0; j < pracownicy[i]->get_ilosc_nr(); j++)
			cout << "numer telefonu: " << pracownicy[i]->get_numer(j) + " " + pracownicy[i]->get_typ(j) << endl;
			for(int j=0;j< pracownicy.size() - 1;j++){
				if (pracownicy[i]->get_id() == pensja[j]->get_id()) {
					cout << "pensja: " << pensja[j]->get_pensja() << " zl"
						<< " premia: " << pensja[j]->get_premia() << " zl\n" << endl;
				}
		}
	return pracownicy[i];
	}


	ostream& operator<<(ostream& output, const Pracownicy& praca) {
		if (praca.pracownicy.size() > 0) {
			for (int i = 0; i < praca.pracownicy.size(); i++) {
				output << "id: " << praca.pracownicy[i]->get_id() << endl;
				output << "imie: " << praca.pracownicy[i]->get_imie() << endl;
				output << "nazwisko: " << praca.pracownicy[i]->get_nazwisko() << endl;
				output << "rola: " << praca.pracownicy[i]->get_rola() << endl;
				for (int j = 0; j < praca.pracownicy[i]->get_ilosc_nr(); j++)
					output << "numer telefonu: " << praca.pracownicy[i]->get_numer(j) + " " + praca.pracownicy[i]->get_typ(j) << endl;

				if (praca.pracownicy[i]->get_id() == praca.pensja[i]->get_id()) {
					output << "pensja: " << praca.pensja[i]->get_pensja() << " zl"
						<< " premia: " << praca.pensja[i]->get_premia() << " zl\n" << endl;


				}
			}
	
			return output;
		}
	}

	void Pracownicy::operator()(string nazwisko) {
		int ile = 0;
		for (int i = 0; i < ilosc_pracownikow; i++) {
			if (pracownicy[i]->get_nazwisko() == nazwisko) {
				ile++;
			}
		}
			cout << "Nazwisko " << nazwisko << " wystepuje " << ile << " raz(y)" << endl;
	}

	Pracownicy& Pracownicy::operator=(Pracownicy& a) {
		Pracownicy o;
		for (auto x : o.pracownicy)
			delete x;
		ilosc_pracownikow = a.ilosc_pracownikow;
		for (size_t i = 0; i < ilosc_pracownikow; i++) {
			o.pracownicy[i]=a.pracownicy[i];
		
		}
		return o;
	}


	Pracownicy::Pracownicy(int ilosc) :ilosc_pracownikow(ilosc) {
		for (int i = 0; i < ilosc_pracownikow; i++) {
			pracownicy.push_back(new Pracownik());
			pensja.push_back(new Pensje());
		}
		zatrudnij_Pracownikow();

	}


	Pracownicy::Pracownicy(const Pracownicy& a) :ilosc_pracownikow{5} {
			for (auto x : pracownicy)
				delete x;
			vector<Pracownik*> pracownicy;
			for (int i = 0; i < a.pracownicy.size(); i++)
				pracownicy.push_back(a.pracownicy[i]);
		}


	string jaka_rola(int id) {
		if (id > 25) { id = (id*6) % 3; }
		if (id >= 1 && id < 6) return "Administracja"; //administracja
		if (id >= 6 && id < 11) return "Technik"; //technik
		if (id >= 11) return "Obsluga"; //obsluga
	}


	void  Pracownicy::zatrudnij_Pracownikow() {
			int id;
			string imie,rola, nazwisko;
			for (int i = 0; i < ilosc_pracownikow; i++) {
				ostatnie_id++;
				id = ostatnie_id;
				rola = jaka_rola(id);
				imie = losuj_imie();
				nazwisko = losuj_nazwisko();
				pracownicy[i]->set_id(id);
				pracownicy[i]->set_rola(rola);
				pracownicy[i]->set_imie(imie);
				pracownicy[i]->set_nazwisko(nazwisko);
				pensja[i]->set_id(ostatnie_id);
				pensja[i]->set_pensja(losuj_float()+1000);
				pensja[i]->set_premia(losuj_int("3"));
	
			}
	}
	
	void Pracownicy::zmien_role() {
		int id,w;
		cout << "Wprowadz id pracownika, ktoremu chcesz zmienic role: ";
		cin >> id;
		if (id > pracownicy.size() - 1 || id < 0) { cout << "blad" << endl; }
		else {
			for (int i=0; i < pracownicy.size(); i++) {
				if (pracownicy[i]->get_id() == id) {
					cout << "Zmieniasz role " << pracownicy[i]->get_imie() + " " + pracownicy[i]->get_nazwisko() << " id " << pracownicy[i]->get_id()<<endl;
					cout << "Obecna rola: " << pracownicy[i]->get_rola() << endl;
					cout << "Wybierz role: \n 1. Obsluga\n 2. Technik\n 3. Administracja\n wpisz wybor: ";
					cin >> w;
					switch (w)
					{
					case 1:pracownicy[i]->set_rola("Obsluga"); cout << "Zmieniono role" << endl; break;
					case 2:pracownicy[i]->set_rola("Technik"); cout << "Zmieniono role" << endl; break;
					case 3:pracownicy[i]->set_rola("Administracja"); cout << "Zmieniono role" << endl; break;
					default: cout << "Zly wybor" << endl; break;
					}cout << endl;
					break;
				}
				
			}
		}

	}

	void Pracownicy::dodaj_Pracownika() {
		pracownicy.push_back(new Pracownik);
		pensja.push_back(new Pensje);
		ilosc_pracownikow++;
		int id = pracownicy.size()-1;
		ostatnie_id++;
		pracownicy[id]->set_id(ostatnie_id);
		pracownicy[id]->set_rola(jaka_rola(id));
		pracownicy[id]->set_imie(losuj_imie());
		pracownicy[id]->set_nazwisko(losuj_nazwisko()); 
		pensja[id]->set_id(ostatnie_id);
		pensja[id]->set_pensja(losuj_float());
		cout << "dodano pracownika" << endl;
	}
	
	void Pracownicy::usun_Pracownika(int id) {
		if (id-1 > pracownicy.size() - 1 || id < 0) { cout << "blad" << endl; }
		else {
			size_t i = 0;
			for (i; i < pracownicy.size(); i++) {
				if (pracownicy[i]->get_id() == id) break;
			}
			auto it = pracownicy.begin() + i ; //poczatek wektora + docelowy indeks
			pracownicy.erase(it);
			ilosc_pracownikow--;
			cout << "usunieto pracownika" << endl;
		}
	}
	
	
	void Pracownicy::zmien_Premie() {
		int id;
		float premia;
		bool znaleziono = false;
		cout << "Podaj id pracownika, ktoremu chcesz zmienic premie: ";
		cin >> id;
		if (id - 1 > pracownicy.size() - 1 || id < 0) { cout << "blad" << endl; }
		else {
			size_t i = 0;
			for (i; i < pracownicy.size(); i++) {
				if (pracownicy[i]->get_id() == id) { znaleziono = true; break; }
			}
			if (znaleziono) {
				cout << "Wpisz kwote nowej premii: ";
				cin >> premia;
				pensja[i]->set_premia(premia);
				cout << "Pracownik " << pracownicy[i]->get_imie() + " " + pracownicy[i]->get_nazwisko() << " ma przyznana premie w wysokosci: " << premia << " zl\n" << endl;

			}
			else {
				cout << "nie znaleziono pracownika\n" << endl;
			}
		}
	}


	void Pracownicy::zmien_Pensje() {
		int id;
		float zarobki;
		bool znaleziono = false;
		cout << "Podaj id pracownika, ktoremu chcesz zmienic pensje: ";
		cin >> id;
		if (id - 1 > pracownicy.size() - 1 || id < 0) { cout << "blad" << endl; }
		else {
			size_t i = 0;
			for (i; i < pracownicy.size(); i++) {
				if (pracownicy[i]->get_id() == id) { znaleziono = true; break; }
			}
			if (znaleziono) {
				cout << "Wpisz kwote nowej pensji: ";
				cin >> zarobki;
				pensja[i]->set_pensja(zarobki);
				cout << "Pracownik " << pracownicy[i]->get_imie() + " " + pracownicy[i]->get_nazwisko() << " ma przyznana wyplate w wysokosci: " << zarobki << " zl\n" << endl;

			}
			else {
				cout << "nie znaleziono pracownika\n" << endl;
			}
		}
	}


	

	void Pracownicy::wyswietl_Pracownika(int i) {
		cout <<"Imie pracownika: "<< pracownicy[i]->get_imie() << endl;
		cout << "Nazwisko pracownika:" << pracownicy[i]->get_nazwisko()<<endl;
		cout << "Rola pracownika: " << pracownicy[i]->get_rola()<<endl;
	}





	Pracownicy::~Pracownicy() {
		for (auto x : pracownicy)
			delete x;
		for (auto y : pensja)
			delete y;
		ilosc_pracownikow = 0;
	}


	