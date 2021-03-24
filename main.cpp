#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <ctime> //current date
#include "muzeu.h"
#include "client.h"
#define CVUI_IMPLEMENTATION
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "cvui.h"

const int nr_rooms=6;
const int v0=49;
const int v1=52;
const int v2=49;

using namespace std;
using namespace cv;

void ReadMuseumData(muzeu &M) {
    ifstream fin("museum_data.in.txt");
    fin >> M; //citeste date despre muzeu - overloaded operator
}
void ReadStaffData(muzeu &M){

    ifstream fin("staff_data.in.txt");
    string departament, nume;
    int nr_dep, nr_pers;
    fin>>nr_dep;
    for(int i=0;i<nr_dep;i++) {
        fin >> departament;
        M.AdaugaDepartament(departament);
    }

    fin>>nr_pers;
    for(int i=0;i<nr_pers;i++) {
        fin >> departament;
        getline(fin, nume);
        M.AdaugaPersonal(departament, nume);
    }

    //M.AfiseazaPersonal();

}

int Price(muzeu M, client C, int nr_zi_saptamana){
    //calculeaza pretul/zi in functie de tipul de client si ce zi este; 0->duminica, 1->luni etc.
    //tip: 1->0%, 2->20%, 3->50% reduceri
    int pret=M.PretZi(nr_zi_saptamana);
    int tip_client;
    tip_client=C.Tip();
    if(tip_client==1)
        return pret;
    else if (tip_client==2)
        return ceil(pret-pret*0.2);
    else  //tip 3
        return ceil(pret-pret*0.5);

}

void MuseumIntroduction(muzeu M){
    cout<<M;
}
void ReadRoomsData( sala S[]){

    string nume, data_aducere;
    int pret,room_no,nr_rooms;
    ifstream fin("rooms_data.in.txt");
    fin>>nr_rooms;
    for(int i=0;i<nr_rooms;i++)
        fin>>S[i];
    while (fin>>room_no>>nume>>data_aducere>>pret) //fisierul de intrare e de forma: nr_sala nume_exponat data_aducere_exp pret_exp
        S[room_no].AdaugaExponat(nume, data_aducere, pret);


}
bool ButtonTour()
{
    Mat frame=Mat(Size(650,150),CV_8UC3);
    cvui:: init("Welcome!",10);
    while(true)
    {
        frame=Scalar(v0,v1,v2); //colour
        cvui:: text(frame, 40,40 ,"Would you like to start the museum tour?");
        if(cvui::button(frame,100,80,"Yes"))
        {
            return 1;
        }
        if(cvui::button(frame,300,80,"No"))
        {
           return 0;
        }
        cvui:: update();
        imshow("Welcome!", frame);
        setWindowProperty("Welcome!", WND_PROP_TOPMOST, 1); //aduce butonul in fata ide-ului

    }

}
int CurrentDay()
{
    //https://stackoverflow.com/questions/41523301/how-to-get-the-day-of-the-week-from-a-tm-object-in-c
 time_t current_time;
 tm *timeinfo;
 time(&current_time);
 timeinfo=localtime(&current_time);
 return timeinfo->tm_wday;

}
int main()
{
    muzeu M;
    client C;
    sala S[nr_rooms];
    //citiri din fisiere
    ReadMuseumData(M);
    ReadRoomsData(S);
    ReadStaffData(M);

    //afiseaza date relevante despre muzeu
     MuseumIntroduction(M);

    ///Metode disponibile si relevante pentru obiectul muzeu (celelalte se apeleaza in cadrul turului):
//    void AdaugaPersonal(string departament,string nume);
//    void AfiseazaPersonal();
//    void AdaugaDepartament(string departament);
///    void StartTour(sala S[]);
//     void FeedbackScore(); //afiseaza feedback score bazat pe fisierul in care se retin
//     notele (si numele/prenumele) date de utilizator (client)

    ///Metode disponibile si relevante pentru obiectul sala
//    void AdaugaExponat(string nume_exponate, string data_aducerii, int pret);
//    void DeschideSala();
//    void InchideSala(); //are consecinte la "rularea" turului-> va afisa o atentionare cu camera-inchisa
//    bool Stare(); //afla disponibilitatea unei camere

///Adaugarea unui exponat se poate face manual cu metoda de mai sus (si scriind ulterior datele tot manual in rooms_data.in.txt), fie
///adaugand direct datele (nr_sala nume_exponat data_aducerii pret_cumparare) in fisierul rooms_data.in.txt
///iar mai apoi prin apelarea functiei ReadRoomsData(S);

    ///Metode disponibile si relevante pentru obiectul client
//  void Feedback(); //ofera feedback la finalul turului, care va fi luat in calcul la feedback score al muzeului
//  int Tip(); //se poate afla din ce categorie face parte (student, adult, child)

  //incepe tur sau nu
    bool command= ButtonTour();
    destroyAllWindows();
    if(command) {
         cin>>C; //citeste nume si prenume client, cat si daca e adult, student sau copil
         cout<<"The price is: "<<Price(M,C,CurrentDay())<<" lei\n";
         cout<<"Are you sure you want to continue with the tour? Type yes or no.\n";
         string ans;
         cin>>ans;
        while(ans!="yes" && ans!="no")
        {
            cout<<"Please type yes or no.\n";
            cin>>ans;
        }
        if(ans=="yes")
        {
             M.StartTour(S);
             C.Feedback();
         }

    }

    cout<<"Our feedback score is:\n";
    M.FeedbackScore();

   return 0;

}
