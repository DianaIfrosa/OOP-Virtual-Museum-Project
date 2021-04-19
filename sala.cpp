#include "sala.h"
#include <iostream>
using namespace std;

sala::sala(int et, bool stare)
{
	etaj=et;
	this->stare=stare; //implicit sala deschisa
}
void sala::Inchide() {

	cout<<"This random room has been closed\n";
}

bool sala::Stare() const {
	return this->stare;
}
void sala::Deschide() {

	stare=true;
}

