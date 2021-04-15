#include "sala.h"
#include <iostream>
using namespace std;

sala::sala(int et, bool stare)
{
	etaj=et;
	this->stare=stare; //implicit sala deschisa
}
void sala::Renoveaza() {

	cout<<"The renovation of this room will take a few  days\n";
}

bool sala::Stare() const {
	return this->stare;
}

