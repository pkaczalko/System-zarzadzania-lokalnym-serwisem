#include <iostream>
#include "Finanse.hpp"
using namespace std;

Pensje::Pensje() :idPracownika(0) ,premia(0), pensja(2061.67) {}
void Pensje::set_id(int id) { idPracownika = id; }
void Pensje::set_pensja(float pen) { pensja = pen; }
void Pensje::set_premia(float prem) { premia = prem; }
int	Pensje::get_id() { return idPracownika; }
float Pensje::get_pensja() { return pensja; }
float Pensje::get_premia() { return premia; }