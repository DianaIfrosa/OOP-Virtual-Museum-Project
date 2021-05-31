#include "MagazinSuveniruri.h"
#include <fstream>
#include <iostream>
using namespace std;

MagazinSuveniruri* MagazinSuveniruri::mag=nullptr;

MagazinSuveniruri::MagazinSuveniruri(): sala() {

	ifstream fin("souvenirs.in.txt");
	string nume;
	double pret;
	while(fin>>nume>>pret)
		obiecte.emplace_back(make_pair(nume,pret)); //emplace_back ~ push_back

}
void MagazinSuveniruri::Viziteaza() {

	 // TO DO

}
void MagazinSuveniruri::Inchide() {

	cout<<"The museum shop has been closed!\n";
	stare=false;

}

