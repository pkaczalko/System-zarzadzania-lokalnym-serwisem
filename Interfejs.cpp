#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include "Interfejs.hpp"
#include "Los.hpp"
#include "Finanse.hpp"
#include "HR.hpp"
#include "Magazyn.hpp"
#include "Obsluga.hpp"
#include "Klienci.hpp"
using namespace std;

namespace print {
	string print(string ciag) {
		string doc;
		cout << ciag << endl;
		cin >> doc;
		return doc;
	}
}


interfejs::interfejs() {
	magazyn_o = new Magazyn(100,150);
	pracownicy = new Pracownicy(25);//zmienic na wczytanie z pliku
	sprzedaz = new Sprzedaze(losuj_int("3")+500);
	wizyty = new Wizyty(losuj_int("2"));
	zlecenia = new Zlecenia(losuj_int("2"));
	klienci = new Klienci(losuj_int("4"));
	sprzedaz->sprzedaj(klienci->ile_klientow(),magazyn_o->get_ilosc_produktow());
	wizyty->zaplanuj(klienci->ile_klientow(), magazyn_o->get_ilosc_produktow());
	zlecenia->zlec(klienci->ile_klientow(), magazyn_o->get_ilosc_produktow());
}





void interfejs::start() {

	bool koniec = false;
	int wybor;
	cout << "Witaj!" << endl;
	while (!koniec) {
		cout << "1. Zarzadzanie magazynem" << endl;
		cout << "2. Zarzadzanie zasobami ludzkimi" << endl;
		cout << "3. Zarzadzanie obsluga" << endl;
		cout << "4. Zarzadzanie serwisem" << endl;
		cout << "5. Finanse i Statystyki" << endl;
		cout << "0. Wyjscie" << endl;
		cout << "Co zrobic?: ";
		cin >> wybor;
		switch (wybor)
		{
		case 1:
			magazyn(); break;
		case 2:
			hr(); break;
		case 3: 
			obsluga(); break;
		case 4:
			serwis(); break;
		case 5:
			statystyki(); break;
		case 0: {
			koniec = true;
			system("cls");
			continue; }break;
		default:
			cout << "zly wybor, sproboj ponownie" << endl;
			break;
		}	cout << endl;
	}

}



void interfejs::stat_sprzedazy(){
	int id,indeks=0;
	cout << "podaj id produktu: ";
	cin >> id;
	for (size_t i = 0; i < magazyn_o->get_ilosc_produktow(); i++) {
		if (magazyn_o->produkty[i]->get_id() == id) { indeks = i; break;}
	}
	int ile=0;
	for (size_t i = 0; i < sprzedaz->liczba_sprzedazy; i++) {
		if (sprzedaz->sprzedaz[i]->get_id_produktu() == magazyn_o->produkty[indeks]->get_id()) { ile++; }
	}
	cout << "Nazwa towaru: " << magazyn_o->produkty[indeks]->get_nazwa() << endl;
	cout << "laczna sprzedaz: " << ile << " szt." << endl;
	cout << "Przychod: " << ile * magazyn_o->produkty[indeks]->get_cena() << " zl" << endl;

}



void interfejs::stat_pracownikow() {
	int ile,max=0,kto,suma,sumam;
	for (size_t i = 0; i < pracownicy->ilosc_pracownikow; i++) {
		ile = 0; suma = 0;
		for (size_t j = 0; j < sprzedaz->liczba_sprzedazy; j++) {
			if (sprzedaz->sprzedaz[j]->get_id_pracownika() == pracownicy->pracownicy[i]->get_id()) {
				suma += magazyn_o->produkty[sprzedaz->sprzedaz[j]->get_id_produktu()]->get_cena();
				ile++;
			}
		}
		if (ile > max) { kto = i; max = ile; sumam = suma; }
	}
	cout << "Najwiecej przedmiotow zostalo sprzedanych przez: " << pracownicy->pracownicy[kto]->get_imie() + " " + pracownicy->pracownicy[kto]->get_nazwisko() << " sprzedajac " << max << " przedmiotow o wartosci " << sumam << " zl" << endl;;
	max = 0; kto = NULL; suma = sumam = 0;
	for (size_t i = 0; i < pracownicy->ilosc_pracownikow; i++) {
		ile = 0;
		for (size_t j = 0; j < zlecenia->liczba_zlecen; j++) {
			if (zlecenia->zlecenia[j]->get_id_pracownika() == pracownicy->pracownicy[i]->get_id()) {
				suma += zlecenia->get_cena_uslugi(zlecenia->zlecenia[j]->get_nr_uslugi());
				ile++;
			}
		}
		if (ile > max) { kto = i; max = ile; sumam = suma; }
	}
	cout << "Najwiecej zlecen: " << pracownicy->pracownicy[kto]->get_imie() + " " + pracownicy->pracownicy[kto]->get_nazwisko() << " z " << max << " zlecen za uslugi warte " <<sumam<<" zl\n"<<endl;

}

void interfejs::statystyki() {
	system("cls");
	int wybor;
	bool koniec = false;
	while (!koniec) {
		cout << "1. Statystyki sprzedazy" << endl;
		cout << "2. Statystyki pracownikow" << endl;
		cout << "0. Powrot" << endl;
		cout << "Co chcesz zrobic?: ";
		cin >> wybor;

		switch (wybor)
		{
		case 1: {system("cls"); stat_sprzedazy(); }break;

		case 2: {system("cls"); stat_pracownikow(); }break;

		case 0: {system("cls"); koniec = true; }break;
		default: cout << "zly wybor, sproboj ponownie" << endl;
			break;
		}
	}
}


void interfejs::magazyn() {
	system("cls");
	int wybor;
	bool koniec = false;
	while (!koniec) {

		cout << "1. Wyswietl produkty w magazynie" << endl;
		cout << "2. Wyswietl ilosc produktow " << endl;
		cout << "3. Dodaj produkt " << endl;
		cout << "4. Usun produkt" << endl;
		cout << "5. Zapisz stan magazynu do pliku tekstowego" << endl;
		cout << "6. Adres magazynu" << endl;
		cout << "0. Powrot" << endl;
		cout << "Co zrobic?: ";
		cin >> wybor;
		switch (wybor)
		{
		case 1: {
			system("cls");
			cout << *magazyn_o;
		}break;

		case 2: {
			system("cls");
			cout << "ilosc produktow w magazynie: " << magazyn_o->get_ilosc_produktow();
		}break;

		case 3: {
			system("cls");
			magazyn_o->dodaj_produkt();
		}break;

		case 4: {
			system("cls");
			while (1) {
				cout << "Podaj indeks produktu: ";
				int c; cin >> c;
				if (c > magazyn_o->rozmiar() || c < 0) { cout << "zly indeks" << endl; continue; }
				else { magazyn_o->usun_produkt(c); break; }
			}
		} break;

		case 5:
			system("cls");
			magazyn_o->zapisz(print::print("Wpisz sciezke do zapisu")); break;

		case 6:
			system("cls");
			cout << Magazyn::pokaz_adres() << endl; break;

		case 0: {
			koniec = true;
			system("cls");
			continue;
		}break;

		default:
			cout << "zly wybor, sproboj ponownie" << endl;
			break;
		}//switch

		cout << '\n' << endl;
	}//while
}



void interfejs::wykonaj_zlecenie() {
	int id;
	cout << "wpisz id zlecenia: " << endl;
	cin >> id;
	zlecenia->usun(id);
	system("cls");
	cout << "zlecenie wykonane" << endl;

}


void interfejs::aktualizuj_zlecenie() {
	int w,id,f;
	cout << "1. Aktualizuj numer uslugi\n 2. Aktualizuj cene uslugi\n Wybor: ";
	cin >> w;
	cout << "Podaj id zlecenia: "; cin >> id;
	switch (w)
	{
	case 1: cout << "podaj numer uslugi: "; cin >> f; zlecenia->zlecenia[id]->set_nr_uslugi(losuj_int(35) + 1); cout << "zmieniono numer" << endl; break;

	case 2:float cena; cout << "Podaj nowa cene: "; cin >> cena;  zlecenia->set_cena_uslugi(id, cena); cout << "zmieniono cene"<<endl; break;
	default: cout << "zly wybor" << endl;
		break;
	}


}

void interfejs::serwis() {
	system("cls");
	int wybor;
	bool koniec = false;
	while (!koniec) {

		cout << "1. Wykonaj zlecenie" << endl;
		cout << "2. Aktualizuj zlecenie" << endl;
		cout << "0. Powrot" << endl;
		cout << "Co chcesz zrobic?: ";
		cin >> wybor;

		switch (wybor)
		{
		case 1: {system("cls"); wykonaj_zlecenie(); }break;

		case 2: {system("cls"); aktualizuj_zlecenie(); }break;

		case 0: {system("cls"); koniec = true; }break;
		default: cout << "zly wybor, sproboj ponownie" << endl;
			break;
		}
	}
}


void interfejs::hr() {
	system("cls");
	int wybor;
	bool koniec = false;
	while (!koniec) {

		cout << "1. Wyswietl pracownikow" << endl;
		cout << "2. Zatrudnij pracownika" << endl;
		cout << "3. Zwolnij pracownika" << endl;
		cout << "4. Zmien stanowisko pracownika" << endl;
		cout << "5. Zmien premie pracownika" << endl;
		cout << "6. Zmien pensje pracownika" << endl;
		cout << "0. Powrot" << endl;
		cout << "Co chcesz zrobic?: ";
		cin >> wybor;

		switch (wybor)
		{
		case 1: {system("cls"); cout << *pracownicy; }break;

		case 2: {system("cls"); pracownicy->dodaj_Pracownika(); }break;

		case 3: {system("cls"); pracownicy->usun_Pracownika(wal()); }break;

		case 4: {system("cls"); pracownicy->zmien_role(); }break;

		case 5: {system("cls"); pracownicy->zmien_Premie(); }break;

		case 6: {system("cls"); pracownicy->zmien_Pensje(); }break;

		case 0: {system("cls"); koniec = true;}break;
		default: cout << "zly wybor, sproboj ponownie" << endl;
			break;
		}
	}
}

int interfejs::wal() {
	int d;
	return d = stoi(print::print("podaj id: "));
	
}


void interfejs::obsluga() {
	system("cls");
	int wybor;
	bool koniec = false;
	Obsluga* o;
	while (!koniec) {
		o = nullptr;
		cout << "1. Zaplanowane wizyty" << endl;
		cout << "2. Dodaj wizyte" << endl;
		cout << "3. Usun wizyte " << endl;
		cout << "4. Wyswietl zlecenia" << endl;
		cout << "5. Dodaj zlecenie" << endl;
		cout << "6. Usun zlecenie" << endl;
		cout << "0. Powrot" << endl;
		cout << "Co zrobic?: ";
		cin >> wybor;
		switch (wybor)
		{

		case 1: {
			unsigned int idKlienta,indeksKlienta;
			int ile_wizyt = wizyty->liczba_wizyt, ile_klientow = klienci->ile_klientow();
			for (int i = 0; i < ile_wizyt; i++) {
				idKlienta = wizyty->wizyty[i]->get_id_klienta();
				indeksKlienta = znajdz('k',idKlienta);
				cout << wizyty->wizyty[i]->get_id_wizyty() << endl;
				cout << "Imie: " << klienci->klienci[indeksKlienta]->get_imie_kl() << endl;;
				cout << "Nazwisko: " << klienci->klienci[indeksKlienta]->get_nazwisko_kl() << endl;;
				cout << "Numer telefonu: " << klienci->klienci[indeksKlienta]->get_nr_tel_kl() << endl;;
				cout << "Data i godzina Wizyty: " << wizyty->wizyty[i]->get_data() + " " + wizyty->wizyty[i]->get_godzina_wizyty() << endl;
				cout << "Cel wizyty: " << wizyty->wizyty[i]->get_cel() << "\n" << endl;
			
			}
		}break;

		case 2: {system("cls"); o = wizyty; o->dodaj(klienci->ile_klientow(), magazyn_o->get_ilosc_produktow());}break;
		
		case 3: {system("cls"); int c = wal(); if (c >= 0) { o = wizyty; o->usun(c-1); } }break;

		case 4: {system("cls"); wyswietl_zlecenia(); } break;

		case 5: {system("cls"); o = zlecenia; o->dodaj(klienci->ile_klientow(), magazyn_o->get_ilosc_produktow()); }break;

		case 6: {system("cls"); int c = wal(); if (c >= 0) { o = zlecenia; o->usun(c-1); } }break;

		case 0: {system("cls"); koniec = true; }break;
		default: {
			cout << "zly wybor, sproboj ponownie" << endl;
		}break;
		}//switch

		cout << '\n' << endl;
	}//while

}







void interfejs::wyswietl_zlecenia() {

	cout << "1. Wszystkie zlecenia" << endl;
	int c = stoi(print::print("2. Pojedyncze zlecenie\n"));
	system("cls");
	switch (c)
	{
	case 1: {
		int indeksKlienta, indeksPracownika, idZlecenia, nrUslugi;
		size_t liczba_zlecen = zlecenia->liczba_zlecen;
		for (size_t i = 0; i < liczba_zlecen; i++) {
			indeksKlienta = znajdz('k', zlecenia->zlecenia[i]->get_id_klienta());
			indeksPracownika = znajdz('p', zlecenia->zlecenia[i]->get_id_pracownika());
			nrUslugi = zlecenia->zlecenia[i]->get_nr_uslugi();
			cout << zlecenia->zlecenia[i]->get_id_zlecenia() << endl;
			cout << "Dane klienta: " << endl;
			klienci->wyswietl_klienta(indeksKlienta);
			cout << "Dane pracownika przypisanego do zlecenia: " << endl;;
			pracownicy->wyswietl_Pracownika(indeksPracownika);
			cout << "Dane zlecenia: " << endl;
			cout << "Nazwa uslugi: " << zlecenia->get_nazwa_uslugi(nrUslugi)<<endl;
			cout << "Cena uslugi:" << zlecenia->get_cena_uslugi(nrUslugi) << " zl\n" << endl;
		}
	}break;


	case 2: {
		int i,indeksKlienta, indeksPracownika, idZlecenia, nrUslugi;

		i = wal();
		if (i >= 0) {
			indeksKlienta = znajdz('k', zlecenia->zlecenia[i]->get_id_klienta());
			indeksPracownika = znajdz('p', zlecenia->zlecenia[i]->get_id_pracownika());
			nrUslugi = zlecenia->zlecenia[i]->get_nr_uslugi();
			cout << zlecenia->zlecenia[i]->get_id_zlecenia() << endl;
			cout << "dane klienta: " << endl;
			klienci->wyswietl_klienta(indeksKlienta);
			cout << "dane pracownika przypisanego do zlecenia: " << endl;
			pracownicy->wyswietl_Pracownika(indeksPracownika);
			cout << "dane zlecenia: " << endl;
			cout << "nazwa uslugi: " << zlecenia->get_nazwa_uslugi(nrUslugi) << endl;
			cout << "cena uslugi:" << zlecenia->get_cena_uslugi(nrUslugi) << " zl" << endl;
		}
	}break;
	default: cout << "niedozwolony wybor" << endl;
		break;
	}

	
	




}

unsigned int interfejs::znajdz(char kogo, int id) {
	{
		if (kogo == 'k') {
			int ile_klientow = klienci->ile_klientow(), i = 0;
			bool znaleziony = false;
			while (!znaleziony) {
				if (i > ile_klientow) break;

				if (id == klienci->klienci[i]->get_id_kl()) { znaleziony = true; return i; }
				i++;
			}cout << "blad! nie znalezniono klienta" << endl;
			return 0;
		}


		if (kogo == 'p') {
			int ile_pracownikow = pracownicy->ilosc_pracownikow, i = 0;
			bool znaleziony = false;
			while (!znaleziony) {
				if (i > ile_pracownikow) break;

				if (id == pracownicy->pracownicy[i]->get_id()) { znaleziony = true; return i; }
				i++;
			}cout << "blad! nie znalezniono pracownika" << endl;
			return 0;
		}




	}
}





interfejs::~interfejs(){
	delete magazyn_o;
	delete pracownicy;
	delete sprzedaz;
	delete wizyty;
	delete zlecenia;
	delete klienci;
	
}
