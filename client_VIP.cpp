#include "client_VIP.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

 void client_VIP::DonateArt(int no_room, const string& name, const string& date, museum &Mus) {

	ofstream fout("rooms_data.in.txt", ios::app);
	fout<<no_room<<" "<<name<<" "<<date<<" "<<0<<"\n";
	Mus.AddExhibit(no_room,name,date,0);
	cout<<"Thank you for your donation!\n";

}
void client_VIP::DonateMoney(museum &Mus, int val) {

	Mus.ReceiveDonations(val);

}