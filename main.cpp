#include <iostream>
#include <fstream>
#include <cmath>
#include "muzeu.h"
#include "client.h"
#include "sala.h"

using namespace std;

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
//calculeaza pretul/zi in functie de tipul de client si ce zi este; 0->duminica, 1->luni etc.
int CalculeazaPret(muzeu M, client C, int nr_zi_saptamana){

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

void MuseumIntroduction(muzeu &M){
    cout<<M;
}
void ReadRoomsData(sala S[],int nr_rooms){

    string nume, data_aducere;
    int pret,room_no;
    ifstream fin("rooms_data.in.txt");
    for(int i=0;i<nr_rooms;i++)
        fin>>S[i];
    while (fin>>room_no>>nume>>data_aducere>>pret) //fisierul de intrare e de forma: nr_sala nume_exponat data_aducere_exp pret_exp
        S[room_no].AdaugaExponat(nume, data_aducere,pret);

}
int main()
{
    muzeu M;
    client C;

    sala S[6];
    ReadMuseumData(M);
    ReadRoomsData(S,6);
    ReadStaffData(M); //citeste date despre staff

    cout<<M;
    //
    cin>>C; //citeste nume si prenume client
    cin.ignore();

    cout<<"Press enter if you would like to visit the museum";
    cin.get();
    C.IncepeTur();


    //in functie de recenzii (array ul scor din clasa muzeu) se alege o data pe luna Sala Preferata-> constructor de copiere
   // sala Preferata (S[3]);

   //cout<<S[2]; //afiseaza numele si numarul de exponate - overloaded operator
   //cout<<C;


   return 0;

}


