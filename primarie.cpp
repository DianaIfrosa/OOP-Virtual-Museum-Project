#include "primarie.h"
#include <iostream>
#include <string>

using namespace std;

void primarie::Despre() {
	cout << oras << " Town Hall is responsible for the maintenance of the museum under the supervision of mayor "
	     << nume_primar << "\n";

}

primarie::primarie(const int& fonduri_t, const int& fonduri_m, const string& nume_oras, const string& primar) {
	this->fonduri_totale = fonduri_t;
	this->fonduri_muzeu = fonduri_m;

	this->oras = make_shared<string>(nume_oras);
	this->nume_primar = make_shared<string>(primar);

}
