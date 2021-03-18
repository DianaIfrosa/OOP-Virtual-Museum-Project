#include "client.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//using namespace cv;
using namespace std;

void client::IncepeTur(){
//    Mat imagine = imread("poza_muzeu.jpg", CV_LOAD_IMAGE_COLOR);
//    namedWindow("display window");
//    imshow("display window", imagine);
//    waitKey(0);
//    for(int i=0;i<6;i++)
//        if(S[i].Stare()==1) //daca sala e deschisa
//            cout<<"Sala "<<i<<" este deschisa\n";

}
void client::AdaugaLaPreferinte() {
    //de facut

}
int client::Tip() {
    return tip;
}
client ::client(string nume, string prenume, int tip) {
this->nume=nume;
this->prenume=prenume;
this->tip=tip;

}
ostream &operator << (ostream &out, const client &C){
    out<<"Clientul "<<C.nume<<" "<<C.prenume<<" este de tipul "<<C.tip<<"\n";
    return out;
}
istream &operator >> (istream &in, client &C){
    cout<<"Introduceti numele si prenumele: ";
    in>>C.nume>>C.prenume;
    return in;

}

