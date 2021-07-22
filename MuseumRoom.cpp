#include <string>
#include <iostream>

#include "MuseumRoom.h"

using namespace std;

MuseumRoom::MuseumRoom() : room(){

	number_exhibits = 0;
}

ostream &operator<<(ostream &out, const MuseumRoom &S) {
	out << "The room named " << S.name_room << " has " << S.number_exhibits << " exhibit(s) and is on floor number " << S.floor << ".\n";
	return out;
}

istream &operator>>(istream &in, MuseumRoom &S) {

	in >> S.name_room >> S.floor;
	return in;
}
void MuseumRoom::Close() {

	cout<<"This museum room has been closed!\n";
	state=false;

}

