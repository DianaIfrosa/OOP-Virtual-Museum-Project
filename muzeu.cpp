#include "muzeu.h"
#include "sala.h"
#include "cvui.h"
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
const int v0=49;
const int v1=52;
const int v2=49;
const int waiting_time=3000;
const string generalpath="C:\\Users\\Diana\\Desktop\\poza";
const string closedroom_path="C:\\Users\\Diana\\Desktop\\pozaclosed.jpg";
using namespace std;
using namespace cv;


void muzeu::AdaugaDepartament(string departament)
{
    nume_personal[departament];
}
void muzeu::AdaugaPersonal(string departament, string nume)
{
    if(nume_personal.count(departament)==0)
        cout<<"Acest departament nu exista!\n";
   else
       nume_personal[departament].push_back(nume);
}
void muzeu::AfiseazaPersonal()
{
    map <string, vector <string> >::iterator  iter;
    for(iter=nume_personal.begin();iter!=nume_personal.end();++iter)
    {
        int dimensiune=iter->second.size();
        //formatare
        cout << "Departamentul " << iter->first << " are ";
        if (dimensiune==0)
            cout<<"0 membri\n";
       else if(dimensiune==1)
        {cout<<"1 membru:";  cout << iter->second[0] ; cout<<"\n";}
        if(dimensiune>1) {
            cout<<dimensiune<<" membri:";
            cout << iter->second[0] ;
            for (int i = 1; i <dimensiune; i++)
                cout << "," << iter->second[i];
            cout << "\n";
        }

    }
}
int muzeu::PretZi(int nr_zi_saptamana){

    //returneaza pretul din ziua specificata
    return pret_zile[nr_zi_saptamana];
}

istream &operator >> (istream &in, muzeu &M){

in>>M.nume;
getline(in, M.adresa);
for(int i=0;i<7;i++)
    in>>M.ore_vizitare[i];
in>>M.nr_sali;
for(int i=0;i<7;i++)
    in>>M.pret_zile[i];

return in;
}
ostream &operator <<(ostream &out, const muzeu &M){

    //detalii despre muzeu
    out<<"Welcome to "<<M.nume<<". Our adress is "<<M.adresa<<"\n";
    out<<"Visiting hours and prices:\n";
    string zile_sapt[7]={"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for(int i=0;i<7;i++) {
        out << zile_sapt[i] << ": " << M.ore_vizitare[i] ;
        if (M.ore_vizitare[i] != "-")
            out<< ", "<<M.pret_zile[i]<<" lei";

        out<<"\n";

    }
  return out;
}

void DisplayImage(string path, string name_window) {

    Mat image = imread(path, IMREAD_UNCHANGED);
    namedWindow(name_window, WINDOW_AUTOSIZE);

    imshow(name_window, image);
    setWindowProperty(name_window, WND_PROP_TOPMOST, 1); //aduce imaginea in fata ide-ului
    waitKey(waiting_time);

}

void muzeu::ShowRoom(const int nrsala, sala S[]) {
    //afiseaza exponatele din camera data
    int i;
    if (S[nrsala].stare == 0)
    {//daca sala e inchisa
    DisplayImage(closedroom_path,"Sorry for the inconvenience!");
    return;
    }
    string src=generalpath;

    for(i=1;i<=S[nrsala].nr_exponate;i++) //iau fiecare exponat
    {
        string path;
        //compun path ul pozanrexp_nrsala !!!!!!!

        path=src+to_string(i)+"_";
        path+=to_string(nrsala)+".jpg";
        //afisez exponatul
        DisplayImage(path,"Museum Tour-Room "+to_string(nrsala+1));

    }
//
}

int Button(int nr_sala, int nr_total_sali, char nume_muzeu[])
{
    //codificare: 1- continua tur, 2- camera precendenta, 3-rewatch, 4-exit
   Mat frame=Mat(Size(650,150),CV_8UC3);
   cvui::init("Menu",10);
   while(true) {
       frame = Scalar(v0, v1, v2); //colour
       cvui::text(frame, 100, 40 , nume_muzeu);
       if ( nr_sala!=nr_total_sali-2 && cvui::button(frame, 320,80, "Continue tour")) {
          //doar pe la mijloc/inceput
           return 1;
       }
       if(nr_sala==nr_total_sali-2 && cvui::button(frame,500, 40, "Finish tour"))
       { //ultima sala- finish tour
           return 1;
       }
       if(nr_sala>0 && cvui::button(frame, 100,80, "Go to previous room"))
       {  // sa nu fie prima
           return 2;
       }
       if(nr_sala>0 && nr_sala!=nr_total_sali-1 &&  cvui:: button(frame,320,40, "See again this room"))
       { //sa nu fie nici ultima nici prima
           return 3;
       }
       if(nr_sala>0 && nr_sala!=nr_total_sali-2 && cvui::button(frame,500, 80, "Exit"))
       { //sa nu fie ultima, acolo exista "Finish tour" si sa nu fie prima
          return 4;
       }
       cvui::update(); //face automat waitkey
       imshow("Menu", frame);
       setWindowProperty("Menu", WND_PROP_TOPMOST, 1); //aduce butonul in fata ide-ului


   }


}
void muzeu::StartTour(sala S[]){

    //de la 0 la nrsali
 for(int i=0;i<nr_sali;i++) {
     ShowRoom(i, S);
     destroyAllWindows();
     if(i!=nr_sali-1) {
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
    string nume, prenume;
    int nota, ct = 0;
    int suma = 0;
    while (fin >> nume >> prenume >> nota) {
        ct++;
        suma+=nota;
    }
    feedback_score=(double)suma/ct;
    cout<<feedback_score<<" ";
}


