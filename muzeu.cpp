#include "muzeu.h"
#include "cvui.h"
#include <vector>
//#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <fstream>
#include <string>


using namespace std;
using namespace cv;

const int v0 = 49;
const int v1 = 52;
const int v2 = 49;
const int waiting_time = 300;
const string generalpath = "./photos/photo";
const string closedroom_path = "./photos/photoclosed.jpg";


muzeu* muzeu::m=nullptr;

//constructorul clasei derivate(muzeu) apeleaza explicit constructorul clasei de baza (primarie) cu parametri
muzeu::muzeu() {
	nume = "-";
	fonduri_muzeu = 0;
	nr_sali = 0;
	for (int i = 0; i < 7; i++)
		pret_zile[i] = 0;
	feedback_score = 0;

}
muzeu::~muzeu()
{
	//sterg pointerii alocati dinamic
	for(int i=0;i<nr_sali;++i) {
		delete S[i];
		S[i] = nullptr;
	}

	S.clear();

}
void muzeu::ReadRoomsData() {

	string room_name, data_aducere;
	int pret, room_no;
	ifstream fin("rooms_data.in.txt");
	for (int i = 0; i < nr_sali-1; i++) {
		auto *s = new SalaMuzeu;
		fin >> *s;
		S.push_back(s);
	}

	while (fin >> room_no >> room_name >> data_aducere
	           >> pret) //fisierul de intrare e de forma: nr_sala nume_exponat data_aducere_exp pret_exp
		this->AdaugaExponat(room_no, room_name, data_aducere, pret);

	///pun magazinul la finalul vectorului de sali din muzeu

	S.push_back(MagazinSuveniruri::get_shop());

}

void muzeu::AdaugaDepartament(const string &departament) {
	nume_personal[departament];
}

void muzeu::AdaugaPersonal(const string &departament, const string &nume_angajat) {
	if (nume_personal.count(departament) == 0)
		cout << "This department doesn't exist!\n";
	else
		nume_personal[departament].push_back(nume_angajat);
}

void muzeu::AfiseazaPersonal() {
	unordered_map<string, vector<string> >::iterator iter;
	for (iter = nume_personal.begin(); iter != nume_personal.end(); ++iter) {
		int dimensiune = iter->second.size();
		//formatare
		cout << "The department " << iter->first << " has ";
		if (dimensiune == 0)
			cout << "0 members\n";
		else if (dimensiune == 1) {
			cout << "1 member:";
			cout << iter->second[0];
			cout << "\n";
		} else if (dimensiune > 1) {
			cout << dimensiune << " members:";
			cout << iter->second[0];
			for (int i = 1; i < dimensiune; i++)
				cout << "," << iter->second[i];
			cout << "\n";
		}

	}
}

int muzeu::PretZi(int nr_zi_saptamana) {

	//returneaza pretul din ziua specificata
	return pret_zile[nr_zi_saptamana];
}

istream &operator>>(istream &in, muzeu &M) {

	in >> M.nume;
	getline(in, M.adresa);
	in >> M.fonduri_muzeu;
	for (int i = 0; i < 7; i++)
		in >> M.ore_vizitare[i];
	in >> M.nr_sali;
	for (int i = 0; i < 7; i++)
		in >> M.pret_zile[i];

	return in;
}

ostream &operator<<(ostream &out, const muzeu &M) {

	//detalii despre muzeu
	out << "Welcome to " << M.nume << ". Our adress is " << M.adresa << "\n";
	out << "Visiting hours and prices:\n";
	string zile_sapt[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	for (int i = 0; i < 7; i++) {
		out << zile_sapt[i] << ": " << M.ore_vizitare[i];
		if (M.ore_vizitare[i] != "-")
			out << ", " << M.pret_zile[i] << "$";

		out << "\n";

	}
	return out;
}

void DisplayImage(const string &path, const string &name_window) {

	///exception handling
	try {
		Mat image = imread(path, IMREAD_UNCHANGED);
		namedWindow(name_window, WINDOW_AUTOSIZE);
		imshow(name_window, image);
		setWindowProperty(name_window, WND_PROP_TOPMOST, 1); //aduce imaginea in fata ide-ului
		waitKey(waiting_time);
	}
	catch (...) {
		cout << "This exhibit was not found!\n";
	}

}

void muzeu::Despre() const {
	cout << *this;
}

void muzeu::ShowRoom(const int nrsala) {
	//afiseaza exponatele din camera data
	int i;
	if ((*S[nrsala]).stare == 0) {//daca sala e inchisa
		DisplayImage(closedroom_path, "Sorry for the inconvenience!");
		return;
	}
	string src = generalpath;

	auto*dp = dynamic_cast<SalaMuzeu *>(S[nrsala]); //acum pointeaza la partea derivata (salamuzeu) si nu numai la baza (sala)


	for (i = 1; i <= dp->nr_exponate; i++) //iau fiecare exponat
	{
		string path;
		//compun path ul pozanrexp_nrsala !!

		path = src + to_string(i) + "_";
		path += to_string(nrsala) + ".jpg";
		//afisez exponatul
		DisplayImage(path, "Museum Tour-Room " + to_string(nrsala + 1));

	}
//
}

int Button(int nr_sala, int nr_total_sali, const string& nume_muzeu) {
	//codificare: 1- continua tur, 2- camera precendenta, 3-rewatch, 4-exit
	Mat frame = Mat(Size(650, 150), CV_8UC3);
	cvui::init("Menu", 10);
	while (true) {
		frame = Scalar(v0, v1, v2); //colour
		cvui::text(frame, 100, 40, nume_muzeu);
		if (nr_sala != nr_total_sali - 2 && cvui::button(frame, 320, 80, "Continue tour")) {
			//doar pe la mijloc/inceput
			return 1;
		}
		if (nr_sala == nr_total_sali - 2 && cvui::button(frame, 500, 40, "Finish tour")) { //ultima sala- finish tour
			return 4;
		}
		if (nr_sala > 0 && cvui::button(frame, 100, 80, "Go to previous room")) {  // sa nu fie prima
			return 2;
		}
		if (nr_sala > 0 && nr_sala != nr_total_sali - 1 &&
		    cvui::button(frame, 320, 40, "See again this room")) { //sa nu fie nici ultima nici prima
			return 3;
		}
		if (nr_sala > 0 && nr_sala != nr_total_sali - 2 &&
		    cvui::button(frame, 500, 80, "Exit")) { //sa nu fie ultima, acolo exista "Finish tour" si sa nu fie prima
			return 4;
		}
		cvui::update(); //face automat waitkey
		imshow("Menu", frame);
		setWindowProperty("Menu", WND_PROP_TOPMOST, 1); //aduce butonul in fata ide-ului


	}


}

void muzeu::StartTour() {

	//de la 0 la nrsali
	for (int i = 0; i < nr_sali; i++) {
		ShowRoom(i);
		destroyAllWindows();
		if (i != nr_sali - 1) {
			int command = Button(i, nr_sali, this->nume);
			destroyAllWindows();
			if (command == 1) //continua tur
				continue;
			else if (command == 2)
				i -= 2;
			else if (command == 3) //rewatch
				i--;
			else //exit=4
			{
				cout << "See you next time!\n";
				break;
			}
		}
	}

}

void muzeu::FeedbackScore() {

	ifstream fin("feedback.txt");
	string nume_client, prenume_client;
	int nota, ct = 0;
	int suma = 0;
	while (fin >> nume_client >> prenume_client >> nota) {
		ct++;
		suma += nota;
	}
	feedback_score = (double) suma / ct;
	cout << feedback_score << " ";
}

void muzeu::PrimesteDonatii(int valoare) {

	fonduri_muzeu += valoare;
}

void muzeu::AdaugaExponat(int nr_sala, const std::string& nume_exponat, const std::string& data_aducerii, int pret) {

	auto *dp = dynamic_cast<SalaMuzeu *>(S[nr_sala]); //acum pointeaza la partea derivata (salamuzeu) si nu numai la baza (sala)
	dp->exponate.emplace_back(std::make_tuple(nume_exponat, data_aducerii, pret));
	dp->nr_exponate++;

}

void muzeu::InchideSala(int nrsala) {

    //metoda virtuala apelata prin pointer la clasa de baza
	S[nrsala]->Inchide();
}

void muzeu::DeschideSala(int nrsala) {

	if (nrsala < nr_sali) {
		cout << "The room no. " << nrsala << " is now open!\n";
	}
	else { //am magazinul
		cout << "The museum shop is now open!\n";
	}
	S[nrsala]->Deschide();
}
int muzeu::NrSali() const{
	return nr_sali;
}



