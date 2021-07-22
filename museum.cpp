#include "museum.h"
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

const int v0 = 89;
const int v1 = 45;
const int v2 = 49;
const int waiting_time = 3000;
const string generalpath = "./photos/photo";
const string closedroom_path = "./photos/photoclosed.jpg";


museum* museum::m=nullptr;

museum::museum() {
	name = "-";
	museum_funds = 0;
	number_of_rooms = 0;
	for (int i = 0; i < 7; i++)
		prices[i] = 0;
	feedback_score = 0;

}
museum::~museum()
{
	//sterg pointerii alocati dinamic
	for(int i=0;i<number_of_rooms;++i) {
		delete S[i];
		S[i] = nullptr;
	}

	S.clear();

}
void museum::ReadRoomsData() {

	string room_name, date_receipt; //numele camerei si data primirii exponatului
	int pret, room_no;
	ifstream fin("rooms_data.in.txt");
	for (int i = 0; i < number_of_rooms-1; i++) {
		auto *s = new MuseumRoom;
		fin >> *s;
		S.push_back(s);
	}

	while (fin >> room_no >> room_name >> date_receipt
	           >> pret) //fisierul de intrare e de forma: nr_sala nume_exponat data_aducere_exp pret_exp
		this->AddExhibit(room_no, room_name, date_receipt, pret);

	///pun magazinul la finalul vectorului de sali din muzeu

	S.push_back(SouvenirShop::get_shop());

}

void museum::AddDepartment(const string &department) {
	name_staff[department];
}

void museum::AddStaff(const string &department, const string &name_employee) {
	if (name_staff.count(department) == 0)
		cout << "This department doesn't exist!\n";
	else
		name_staff[department].push_back(name_employee);
}

void museum::DisplayStaff() {
	unordered_map<string, vector<string> >::iterator iter;
	for (iter = name_staff.begin(); iter != name_staff.end(); ++iter) {
		int size = iter->second.size();
		//formatare
		cout << "The department " << iter->first << " has ";
		if (size == 0)
			cout << "0 members\n";
		else if (size == 1) {
			cout << "1 member:";
			cout << iter->second[0];
			cout << "\n";
		} else if (size > 1) {
			cout << size << " members:";
			cout << iter->second[0];
			for (int i = 1; i < size; i++)
				cout << "," << iter->second[i];
			cout << "\n";
		}

	}
}

int museum::PricePerDay(int day_of_week) {

	//returneaza pretul din ziua specificata
	return prices[day_of_week];
}

istream &operator>>(istream &in, museum &M) {

	in >> M.name;
	getline(in, M.adress);
	in >> M.museum_funds;
	for (int i = 0; i < 7; i++)
		in >> M.visiting_hours[i];
	in >> M.number_of_rooms;
	for (int i = 0; i < 7; i++)
		in >> M.prices[i];

	return in;
}

ostream &operator<<(ostream &out, const museum &M) {

	//detalii despre muzeu
	out << "Welcome to " << M.name << ". Our adress is " << M.adress << ".\n";
	out << "Visiting hours and prices:\n";
	string days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	for (int i = 0; i < 7; i++) {
		out << days[i] << ": " << M.visiting_hours[i];
		if (M.visiting_hours[i] != "-")
			out << ", " << M.prices[i] << "$";

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

void museum::Info() const {
	cout << *this;
}

void museum::ShowRoom(const int no_room) {
	//afiseaza exponatele din camera data
	int i;
	if ((*S[no_room]).state == 0) {//daca sala e inchisa afiseaza o imagine speciala
		DisplayImage(closedroom_path, "Sorry for the inconvenience!");
		return;
	}
	string src = generalpath;

	auto*dp = dynamic_cast<MuseumRoom *>(S[no_room]); //acum pointeaza la partea derivata (museumroom) si nu numai la baza (room)


	for (i = 1; i <= dp->number_exhibits; i++) //iau fiecare exponat
	{
		string path;
		//compun path-ul de forma pozanrexp_nrsala !!

		path = src + to_string(i) + "_";
		path += to_string(no_room) + ".jpg";

		//afisez exponatul
		DisplayImage(path, "Museum Tour-Room " + to_string(no_room + 1));

	}
//
}

int Button(int no_room, int no_total_rooms, const string& name_mus) {

	///codificare: 1- continua tur, 2- camera precendenta, 3-rewatch, 4-exit

	Mat frame = Mat(Size(650, 150), CV_8UC3);
	cvui::init("Menu", 10);
	while (true) {
		frame = Scalar(v0, v1, v2); //colour
		cvui::text(frame, 100, 40, name_mus);
		if (no_room != no_total_rooms - 1 && cvui::button(frame, 320, 80, "Continue tour")) {
			//doar pe la mijloc/inceput
			return 1;
		}
		if (no_room == no_total_rooms - 1 && cvui::button(frame, 500, 40, "Finish tour")) { //ultima sala- finish tour
			return 4;
		}
		if (no_room > 0 && cvui::button(frame, 100, 80, "Go to previous room")) {  // sa nu fie prima
			return 2;
		}
		if (no_room > 0 && no_room != no_total_rooms - 1 &&
		    cvui::button(frame, 320, 40, "See again this room")) { //sa nu fie nici ultima nici prima
			return 3;
		}
		if (no_room > 0 && no_room != no_total_rooms - 1 &&
		    cvui::button(frame, 500, 80, "Exit")) { //sa nu fie ultima, acolo exista "Finish tour" si sa nu fie prima
			return 4;
		}
		cvui::update(); //face automat waitkey
		imshow("Menu", frame);
		setWindowProperty("Menu", WND_PROP_TOPMOST, 1); //aduce butonul in fata ide-ului


	}

}

void museum::StartTour() {

	for (int i = 0; i < number_of_rooms-1; i++) {
		ShowRoom(i);
		destroyAllWindows();
		if (i != number_of_rooms - 1) {
			int command = Button(i, number_of_rooms-1, this->name);
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

	//vizitez magazinul de suveniruri dupa terminarea turului

	//trec de la partea de baza la partea derivata
	SouvenirShop* ptrShop=dynamic_cast<SouvenirShop*>(S[number_of_rooms-1]);
	ptrShop->Visit();

}

void museum::FeedbackScore() {

	ifstream fin("feedback.txt");
	string lastname_client, firstname_client;
	int grade, ct = 0;
	int sum = 0;
	while (fin >> lastname_client >> firstname_client >> grade) {
		ct++;
		sum += grade;
	}
	feedback_score = (double) sum / ct;
	cout << feedback_score << " ";
}

void museum::ReceiveDonations(int value) {

	museum_funds += value;
}

void museum::AddExhibit(int no_room, const std::string& name_exhibit, const std::string& date_receipt, int price) {

	auto *dp = dynamic_cast<MuseumRoom *>(S[no_room]); //acum pointeaza la partea derivata (museumroom) si nu numai la baza (room)
	dp->exhibits.emplace_back(std::make_tuple(name_exhibit, date_receipt, price));
	dp->number_exhibits++;

}

void museum::CloseCertainRoom(int number) {

    //metoda virtuala apelata prin pointer la clasa de baza
	S[number]->Close();
}

void museum::OpenCertainRoom(int number) {

	if (number < number_of_rooms) {
		cout << "The room no. " << number << " is now open!\n";
	}
	else { //e magazinul de suveniruri
		cout << "The museum shop is now open!\n";
	}
	S[number]->Open();
}
int museum::NoRooms() const{
	return number_of_rooms;
}



