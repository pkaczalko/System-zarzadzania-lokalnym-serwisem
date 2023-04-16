#include <iostream>
#include <vector>
using namespace std;
#ifndef Klienci_hpp
#define Klienci_hpp

class Klient {
private:
	unsigned int id_klienta;
	string imie_klienta;
	string nazwisko_klienta;
	string nr_tel_klienta;
public:
	void set_id_kl(unsigned int);
	void set_imie_kl(string);
	void set_nazwisko_kl(string);
	void set_nr_tel_kl(string);
	unsigned int get_id_kl();
	string get_imie_kl();
	string get_nazwisko_kl();
	string get_nr_tel_kl();
};




class Klienci {
private:	
	vector<Klient*> klienci;
	unsigned int liczba_klientow = 0;

public:
	friend class interfejs;
	friend ostream& operator<<(ostream&, const Klienci&);
	Klienci(int);
	unsigned int ile_klientow();
	void wyswietl_klienta(int);
	void pozyskaj_klientow();
	void nowy_klient();


	~Klienci();


};

#endif
