#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <ctime>
#include "Los.hpp"

int losuj_int(int zakres) {
	return rand() % zakres;
}

string losuj_imie() {
	fstream plik;
	plik.open("pliki/Imiona.txt", ios::in);
	if (plik.good() == true)
	{
		string wiersz;
		getline(plik, wiersz);
		int ile = rand() % stoi(wiersz) + 1;
		for (int i = 0; i < ile; i++) {
			getline(plik, wiersz);
		}
		plik.close();
		return wiersz;


	}
	else return "Janusz";
}

string losuj_nazwisko() {
	fstream plik;
	plik.open("pliki/Nazwiska.txt", ios::in);
	if (plik.good() == true)
	{
		string wiersz;
		getline(plik, wiersz);
		int ile = rand() % stoi(wiersz)+1;
		for (int i = 0; i < ile; i++) {
			getline(plik, wiersz);
		}
		plik.close();
		return wiersz;
	}
	else return "Nowak";


}

string losuj_nazwe() {
	fstream plik;
	plik.open("pliki/Nazwy.txt", ios::in);
	if (plik.good() == true)
	{
		string wiersz;
		getline(plik, wiersz);
		int ile = rand() % stoi(wiersz) + 1;
		for (int i = 0; i < ile; i++) {
			getline(plik, wiersz);
		}
		plik.close();
		return wiersz;

	}
	else return "jablko";
}

float losuj_float() {
	float rand_c, rand_nc, cena;
	rand_c = rand() % 1000 + 1;
	rand_nc = rand() % 100 / 100.00;
	cena = rand_c + rand_nc;
	return cena;
}


string losuj_nr_tel() {
	string nr = "";
	for (int j = 0; j < 9; j++) {
		nr += to_string(losuj_int(10));
	}
	return nr;
}


string losuj_date(int i) {
	if (i < 2000) { i = 2012; }
	string dzien{ "" }, miesiac{ "" }, rok = to_string(i);
	dzien += to_string(losuj_int(30) + 1);
	miesiac += to_string(losuj_int(12) + 1);
	if (miesiac == "2" && stoi(dzien) > 28) { dzien = "28"; }
	return dzien + "-" + miesiac + '-' + rok;


}

string losuj_date(string w) {
	if (w == "wizyta") {
		string m, d, y;
		time_t czas;
		struct tm* aktualna;
		char data[80];
		time(&czas);
		aktualna = localtime(&czas);
		strftime(data, 80, "%d", aktualna);
		d = data;
		strftime(data, 80, "%m", aktualna);
		m = data;
		strftime(data, 80, "%Y", aktualna);
		y = data;
		int di{ stoi(d) }, mi{ stoi(m) };
		di = di + losuj_int(15);
		mi = mi + losuj_int(2);
		if (di > 30) { di = 30 - di; }
		if (mi > 12) { mi = 12 - mi; }
		if (mi == 2 && di > 28) { di = 28; }
		return to_string(di) + "-" + to_string(mi) + "-" + y;
	}else return "01-01-1971";
}


string losuj_godzine(){
	int mi = (losuj_int(4) + 1) * 15;
	string m = "";
	if (mi == 60) { m = "00"; }
	else m += to_string(mi);
	return to_string(losuj_int(8) + 10) + ":" + m;
}

string losuj_cel() {
	fstream plik;
	plik.open("pliki/Cele.txt", ios::in);
	if (plik.good() == true)
	{
		string wiersz;
		getline(plik, wiersz);
		int ile = losuj_int(stoi(wiersz)) + 1;
		for (int i = 0; i < ile; i++) {
			getline(plik, wiersz);
		}
		plik.close();
		return wiersz;

	}
	else return "Inny";
}



string losuj_zlecenie() {
	fstream plik;
	plik.open("pliki/Zlecenia.txt", ios::in);
	if (plik.good() == true)
	{
		string wiersz;
		getline(plik, wiersz);
		int ile = rand() % stoi(wiersz) + 1;
		for (int i = 0; i < ile; i++) {
			getline(plik, wiersz);
		}
		plik.close();
		return wiersz;

	}
	else return "Inne";

}


int losuj_int(string i) {
	int ile = stoi(i);
	string l = "";
	l += to_string(losuj_int(9) + 1);
	for (int j = 1; j < ile; j++) {
		l += to_string(losuj_int(9));
	}

	return stoi(l);
}