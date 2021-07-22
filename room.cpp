#include "room.h"
#include <iostream>
using namespace std;

room::room(int fl, bool st)
{
	floor=fl;
	this->state=st; //implicit sala deschisa
}
void room::Close() {

	cout<<"This random room has been closed\n";
}

bool room::State() const {
	return this->state;
}
void room::Open() {

	state=true;
}

