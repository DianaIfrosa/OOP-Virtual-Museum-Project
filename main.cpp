#include <iostream>
#include <fstream>
//#include <memory>
#include <cmath>
#include <string>
#include <sstream>
#include <ctime> //current date
#include <iomanip>
#include "museum.h"
#include "client.h"
#include "client_VIP.h"

#define CVUI_IMPLEMENTATION

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "cvui.h"

const int v0 = 89;
const int v1 = 45;
const int v2 = 49;

using namespace std;
using namespace cv;

void ReadMuseumData(museum &M) {
	ifstream fin("museum_data.in.txt");
	fin >> M; //citeste date despre muzeu - overloaded operator
}

void ReadStaffData(museum &M) {

	ifstream fin("staff_data.in.txt");
	string department, name;
	int number_dep, number_staff;
	fin >> number_dep;
	//fiecare departament
	for (int i = 0; i < number_dep; i++) {
		fin >> department;
		M.AddDepartment(department);
	}

	fin >> number_staff;
	//fiecare persoana din staff
	for (int i = 0; i < number_staff; i++) {
		fin >> department;
		getline(fin, name);
		M.AddStaff(department, name);
	}

	//M.AfiseazaPersonal();

}

int Price(museum& M, const client_VIP &C, int day_week) {
	//calculeaza pretul/zi in functie de tipul de client si ce zi este; 0->duminica, 1->luni etc.
	//tip: 1->0% reducere, 2->20% reducere, 3->50% reducere
	int price = M.PricePerDay(day_week);
	int type_client;
	type_client = C.Type();
	if (type_client == 1)
		return price;
	else if (type_client == 2)
		return ceil(price- price * 0.2);
	else  //tip 3
		return ceil(price - price * 0.5);

}

bool ButtonTour() {
	//prima fereastra
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

void CloseRoom(int number)
{
	auto M=museum::get_museum();
	cout<<"Room number "<<number<<": ";
	M->CloseCertainRoom(number);

}

void OpenRoom(int number)
{
	auto M=museum::get_museum();
	M->OpenCertainRoom(number);

}
int main() {
	client_VIP cv;
	auto M=museum::get_museum();

	//citiri din fisiere
	ReadMuseumData(*M);
	M->ReadRoomsData();

	ReadStaffData(*M);
	M->Info();

	CloseRoom(1);
	OpenRoom(1);

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
		string lastname, firstname, ans;
		int value;
		cin >> firstname >> lastname;
		cout << "\nWould you like to donate money? (yes or no)\n";
		cin >> ans;
		if (ans == "yes") {
			cout << "Please type the value: ";
			cin >> value;
			client_VIP::DonateMoney(*M, value);
			cout << "\nThank you!\n";
		}
		cout << "\nWould you like to donate art? (yes or no)\n";
		cin >> ans;
		if (ans == "yes") {
			cout << "Please type the room number you would like to donate to (a number from 1 to "+to_string(M->NoRooms())+")\n";
			int room_no;
			while (true) {
				cin >> room_no;
				try {
					if (room_no<=0 || room_no>M->NoRooms())
						throw invalid_argument("Invalid museum room number! Please type a number from 1 to "+to_string(M->NoRooms())+"\n");
					break;
				}
				catch (const invalid_argument &err) { cout << err.what(); }

			}
			client_VIP::DonateArt(room_no-1, "Donation-" + lastname + "-"+ firstname, CurrentDate(),
			               *M); //trebuie adaugata imagine in photos pentru fiecare donatie; room_no-1 ptc clientul foloseste indexare de la 1
			cout << "\nThe next step is to send the piece of art to our museum address.\nThank you!\n";
		}

	}

	return 0;

}
