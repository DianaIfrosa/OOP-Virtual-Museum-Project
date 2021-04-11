#include <string>
#include <iostream>

#include "sala.h"
using namespace std;

void sala::AdaugaExponat(string nume_exponate, string data_aducerii, int pret){

    exponate[nr_exponate]=nume_exponate;
    date_exponate[nr_exponate]=data_aducerii;
    preturi_exponate[nr_exponate]=pret;
    nr_exponate++;

}
void sala::DeschideSala() {
    this->stare=1;
}
void sala::InchideSala() {
    this->stare=0;
}
bool sala::Stare() {
    return this->stare;
}

//operatorul =
sala& sala::operator=(const sala &s){
	if (this == &s)
		return *this; //daca am acelasi obiect

	//dezaloc ce avea alocat deja

	delete []exponate;
	delete []date_exponate;
	delete []preturi_exponate;

    nume_sala=s.nume_sala;
    nr_exponate=s.nr_exponate;
	stare = s.stare;
    etaj=s.etaj;

    exponate=s.exponate;
    date_exponate=s.date_exponate;
    preturi_exponate=s.preturi_exponate;

    return *this;
}

//constructor
sala ::sala(string nume, int etaj){
    nr_exponate=0;
    this->etaj=etaj;
    exponate=new string[7];
    date_exponate=new string[7];
    preturi_exponate= new int[7];
    this->nume_sala=nume;
    this->stare=1; //implicit sala deschisa
    //cout<<"constructor ";

}

//destructor
sala ::~sala(){
    delete []exponate;
    delete []date_exponate;
    delete []preturi_exponate;
    //cout<<"destructor ";
}

//constructor de copiere
sala ::sala (const sala &s) {
    nume_sala = s.nume_sala;
    nr_exponate = s.nr_exponate;
    stare = s.stare;
    etaj = s.etaj;
    exponate = new string[7];
    date_exponate = new string[7];
    preturi_exponate = new int[7];
    for (int i = 0; i < s.nr_exponate; i++) {
        exponate[i] = s.exponate[i];
        date_exponate[i] = s.date_exponate[i];
        preturi_exponate[i] = s.preturi_exponate[i];
    }
}
ostream &operator << (ostream &out,const sala &S){
    out<<"The room named " <<S.nume_sala<<" has "<<S.nr_exponate<<" exhibit(s) and is on floor "<<S.etaj<<".\n";
    return out;
}
istream &operator >> (istream &in, sala &S){

    in>>S.nume_sala>>S.etaj;
    return in;
}

