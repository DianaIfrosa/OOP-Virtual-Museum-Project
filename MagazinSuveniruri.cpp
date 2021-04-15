#include "MagazinSuveniruri.h"
#include <fstream>
#include <iostream>
using namespace std;

MagazinSuveniruri::MagazinSuveniruri(): sala() {

	ifstream fin("souvenirs.in.txt");
	string nume;
	double pret;
	while(fin>>nume>>pret)
		obiecte.emplace_back(make_pair(nume,pret)); //emplace_back ~ push_back


}
void MagazinSuveniruri::Viziteaza() {

	 // TO DO joc sfml-------------------------------------------------------------

}
void MagazinSuveniruri::Renoveaza() {

	cout<<"The renovation of this room takes 7 days\n";
	stare=0;

}
