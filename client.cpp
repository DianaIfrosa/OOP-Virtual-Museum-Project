#include "client.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int client::Tip() const {
	if (tip == "adult")
		return 1;
	else if (tip == "student")
		return 2;
	else return 3; //child
}

client::client(string nume, string prenume, string tip) {
	//constructor
	this->nume = nume;
	this->prenume = prenume;
	this->tip = tip;

}

ostream &operator<<(ostream &out, const client &C) {
	out << "Name of client: " << C.nume << " " << C.prenume << ". Category: " << C.tip << "\n";
	return out;
}

istream &operator>>(istream &in, client &C) {
	string category;
	cout << "Please enter your name: ";
	in >> C.nume >> C.prenume;
	cout << "Please enter your category (adult, student, child):";
	while (true) {
		in >> category;
		try {
			if (category != "adult" && category != "student" && category != "child")
				throw invalid_argument("Invalid input! Please enter adult, student or child.\n");
			break;
		}
		catch (const invalid_argument &err) { cout << err.what(); }

	}
	C.tip = category;
	return in;

}

void client::Feedback() {

	double nota;
	ofstream fout("feedback.txt", ios::app); //pentru a putea scrie la sfarsitul fisierului
	cout << "Please give us feedback. On a scale of 1 to 5, how much did you enjoy this tour?\n";
	while (true) {
		cin >> nota;
		try {
			if (int(nota) != nota || nota > 5 || nota < 1)
				throw invalid_argument("Invalid feedback! Please enter 1,2,3,4 or 5.\n");
			break;
		}
		catch (const invalid_argument &err) { cout << err.what(); }

	}
	cout << "Thank you!\n";
	fout << nume + " " + prenume << " " << nota << "\n";

}

