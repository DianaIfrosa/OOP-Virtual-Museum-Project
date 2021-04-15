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

int Price(muzeu M, client C, int nr_zi_saptamana) {
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
string CurrentDate()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);
	ostringstream oss;
	oss << put_time(&tm, "%d-%m-%Y");
	auto str = oss.str();
	return str;

}
int CurrentDay() {
	//https://stackoverflow.com/questions/41523301/how-to-get-the-day-of-the-week-from-a-tm-object-in-c
	time_t current_time;
	tm *timeinfo;
	time(&current_time);
	timeinfo = localtime(&current_time);
	return timeinfo->tm_wday;

}

int main() {
	client C;
	client_VIP cv;
	//creeaza muzeul stiind datele despre primarie
	ifstream fin("townhall_data.in.txt");
	string nume_p, oras;
	int fonduri_m, fonduri_t;

	fin >> oras >> nume_p;
	fin >> fonduri_t >> fonduri_m;

	muzeu M(oras, nume_p, fonduri_m, fonduri_t);
	primarie *ptr=&M;

	//exit code negativ??-------------------------------------------------------------
	//unique_ptr <primarie> ptr; //pointer de tip baza(primarie) catre derivata(muzeu)
	//ptr.reset(&M);

	//citiri din fisiere
	ReadMuseumData(M);

	//afiseaza date relevante despre muzeu
	ptr->Despre(); //apeleaza functia din clasa derivata(muzeu) deoarece e override/virtual
	M.ReadRoomsData();
	ReadStaffData(M);
	M.RenoveazaSala(1);

	//Donatii
	cv.DoneazaArta(2, "Donation-SmithB", CurrentDate(), M); //trebuie adaugata imagine in photos pentru fiecare donatie
	cv.DoneazaBani(M,500);

	//incepe tur sau nu
	bool command = ButtonTour();
	destroyAllWindows();
	if (command) {
		cin >> C; //citeste nume si prenume client, cat si daca e adult, student sau copil
		cout << "Your custom price is: " << Price(M, C, CurrentDay()) << "$\n";
		cout << "Are you sure you want to continue with the tour? Type yes or no.\n";
		string ans;
		cin >> ans;
		while (ans != "yes" && ans != "no") {
			cout << "Please type yes or no.\n";
			cin >> ans;
		}
		if (ans == "yes") {
			M.StartTour();
			C.Feedback();
		}

	}

	cout << "Our feedback score is:\n";
	M.FeedbackScore();

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


   // mai trebuie delete ptr; ??-------------------------------------------------------------

	return 0;

}
