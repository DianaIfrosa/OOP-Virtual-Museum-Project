#include "client_VIP.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

void client_VIP::DoneazaArta(int nrsala, string nume, string data, muzeu &Muz) {

	ofstream fout("rooms_data.in.txt", ios::app);
	fout<<nrsala<<" "<<nume<<" "<<data<<" "<<0<<"\n";
	Muz.AdaugaExponat(nrsala,nume,data,0);
	cout<<"Thank you for your donation!\n";

}
void client_VIP::DoneazaBani(muzeu &Muz, int val) {

	Muz.PrimesteDonatii(val);

}