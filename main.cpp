#include <iostream>
#include <fstream>
//#include <memory>
#include <cmath>
#include <string>
#include <sstream>
#include <ctime> //current date
#include <iomanip>
#include "muzeu.h"
#include "client.h"
#include "client_VIP.h"

#define CVUI_IMPLEMENTATION

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "cvui.h"

const int v0 = 49;
const int v1 = 52;
const int v2 = 49;

using namespace std;
using namespace cv;

void ReadMuseumData(muzeu &M) {
	ifstream fin("museum_data.in.txt");
	fin >> M; //citeste date despre muzeu - overloaded operator
}

void ReadStaffData(muzeu &M) {

	ifstream fin("staff_data.in.txt");
	string departament, nume;
	int nr_dep, nr_pers;
	fin >> nr_dep;
	for (int i = 0; i < nr_dep; i++) {
		fin >> departament;
		M.AdaugaDepartament(departament);
	}

	fin >> nr_pers;
	for (int i = 0; i < nr_pers; i++) {
		fin >> departament;
		getline(fin, nume);
		M.AdaugaPersonal(departament, nume);
	}

	//M.AfiseazaPersonal();

}

int Price(muzeu& M, const client_VIP &C, int nr_zi_saptamana) {
	//calculeaza pretul/zi in functie de tipul de client si ce zi este; 0->duminica, 1->luni etc.
	//tip: 1->0%, 2->20%, 3->50% reduceri
	int pret = M.PretZi(nr_zi_saptamana);
	int tip_client;
	tip_client = C.Tip();
	if (tip_client == 1)
		return pret;
	else if (tip_client == 2)
		return ceil(pret - pret * 0.2);
	else  //tip 3
		return ceil(pret - pret * 0.5);

}

bool ButtonTour() {
	Mat frame = Mat(Size(650, 150), CV_8UC3);
	cvui::init("Welcome!", 10);
	while (true) {
		frame = Scalar(v0, v1, v2); //colour
		cvui::text(frame, 40, 40, "Would you like to start the museum tour?");
		if (cvui::button(frame, 100, 80, "Yes")) {
			return true;
		}
		if (cvui::button(frame, 300, 80, "No")) {
			return false;
		}
		cvui::update();
		imshow("Welcome!", frame);
		setWindowProperty("Welcome!", WND_PROP_TOPMOST, 1); //aduce butonul in fata ide-ului

	}

}

bool ButtonDonation() {
	Mat frame = Mat(Size(650, 150), CV_8UC3);
	cvui::init("Donations", 10);
	while (true) {
		frame = Scalar(v0, v1, v2); //colour
		cvui::text(frame, 40, 40, "Would you like to donate art or money?");
		if (cvui::button(frame, 100, 80, "Yes")) {
			return true;
		}
		if (cvui::button(frame, 300, 80, "No")) {
			return false;
		}
		cvui::update();
		imshow("Donations", frame);
		setWindowProperty("Donations", WND_PROP_TOPMOST, 1); //aduce butonul in fata ide-ului

	}
}

string CurrentDate() {
	auto t = time(nullptr);
	auto tm = *localtime(&t);
	ostringstream oss;
	oss << put_time(&tm, "%d-%m-%Y");
	auto str = oss.str();
	return str;

}

int CurrentDay() {
	time_t current_time;
	tm *timeinfo;
	time(&current_time);
	timeinfo = localtime(&current_time);
	return timeinfo->tm_wday;

}

int main() {
	client_VIP cv;
	auto M=muzeu::get_museum();

	//citiri din fisiere
	ReadMuseumData(*M);
	M->ReadRoomsData();
	ReadStaffData(*M);
	M->Despre();
	M->InchideSala(1);
	M->DeschideSala(1);

	//incepe tur sau nu
	bool command = ButtonTour();
	destroyAllWindows();
	if (command) {
		cin >> cv; //citeste nume si prenume client, cat si daca e adult, student sau copil
		cout << "Your custom price is: " << Price(*M, cv, CurrentDay()) << "$\n";
		cout << "Are you sure you want to continue with the tour? Type yes or no.\n";
		string ans;
		while (true) {
			cin >> ans;
			try {
				if (ans != "yes" && ans != "no")
					throw invalid_argument("Please type yes or no.\n");
				break;
			}
			catch (const invalid_argument &err) { cout << err.what(); } //afiseaza mesajul de mai sus

		}
		if (ans == "yes") {
			M->StartTour();
			cv.Feedback();
		}

	}

	cout << "Our feedback score is:\n";
	M->FeedbackScore();

	//Donatii
	command = ButtonDonation();
	destroyAllWindows();
	if (command) {
		cout << "\nPlease enter your first and last name: ";
		string nume, prenume, ans;
		int value;
		cin >> nume >> prenume;
		cout << "\nWould you like to donate money? (yes or no)\n";
		cin >> ans;
		if (ans == "yes") {
			cout << "Please type the value: ";
			cin >> value;
			client_VIP::DoneazaBani(*M, value);
			cout << "\nThank you!\n";
		}
		cout << "\nWould you like to donate art? (yes or no)\n";
		cin >> ans;
		if (ans == "yes") {
			cout << "Please type the room number you would like to donate to (a number from 1 to "+to_string(M->NrSali())+")\n";
			int room_no;
			while (true) {
				cin >> room_no;
				try {
					if (room_no<=0 || room_no>M->NrSali())
						throw invalid_argument("Invalid museum room number! Please type a number from 1 to "+to_string(M->NrSali())+"\n");
					break;
				}
				catch (const invalid_argument &err) { cout << err.what(); }

			}
			client_VIP::DoneazaArta(room_no-1, "Donation-" + nume + "-"+ prenume, CurrentDate(),
			               *M); //trebuie adaugata imagine in photos pentru fiecare donatie; room_no-1 ptc clientul foloseste indexare de la 1
			cout << "\nThe next step is to send the piece of art to our museum address.\nThank you!\n";
		}


	}

//-------------------de actualizat
	///Metode disponibile si relevante pentru obiectul din clasa muzeu (celelalte se apeleaza in cadrul turului):
//    void AdaugaPersonal(string departament,string nume);
//    void AfiseazaPersonal();
//    void AdaugaDepartament(string departament);
//    void StartTour(SalaMuzeu S[]);
//    void FeedbackScore(); //afiseaza feedback score bazat pe fisierul in care se retin
//    notele (si numele/prenumele) date de utilizator (client)

	///Metode disponibile si relevante pentru obiectul din clasa SalaMuzeu
//    void AdaugaExponat(string nume_exponate, string data_aducerii, int pret);
//    void DeschideSala();
//    void InchideSala(); //are consecinte la "rularea" turului-> va afisa o atentionare cu camera-inchisa
//    bool Stare(); //afla disponibilitatea unei camere

	///Adaugarea unui exponat se poate face manual cu metoda de mai sus (si scriind ulterior datele tot manual in rooms_data.in.txt), fie
	///adaugand direct datele (nr_sala nume_exponat data_aducerii pret_cumparare) in fisierul rooms_data.in.txt
	///iar mai apoi prin apelarea  M.ReadRoomsData(); O alta metoda este prin donatii.

	///Metode disponibile si relevante pentru obiectul din clasa client
//  void Feedback(); //ofera feedback la finalul turului, care va fi luat in calcul la feedback score al muzeului
//  int Tip(); //se poate afla din ce categorie face parte (student, adult, child)


	return 0;

}
