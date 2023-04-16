#include <iostream>
using namespace std;

#ifndef Finanse_hpp
#define Finanse_hpp
class Pensje{
private:
	int idPracownika;
	float pensja;
	float premia;

public:
	Pensje();
	void set_id(int id);
	void set_pensja(float pen);
	void set_premia(float prem);
	int get_id();
	float get_pensja();
	float get_premia();
};
#endif