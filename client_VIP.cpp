#include "client_VIP.h"
#include <string>
#include <iostream>
using namespace std;

void client_VIP::DoneazaArta(int nrsala, string nume, string data, muzeu &Muz) {

	Muz.AdaugaExponat(nrsala,nume,data,0);
	cout<<"Thank you for your donation!\n";

}
void client_VIP::DoneazaBani(muzeu &Muz, int val) {

	Muz.PrimesteDonatii(val);

}