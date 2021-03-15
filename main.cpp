#include <iostream>
#include <fstream>
#include "muzeu.h"
#include "client.h"
#include "sala.h"
#include <cmath>
#define NRMAXSALI 7

using namespace std;
ifstream fin("date.in.txt");

void Staff(muzeu M)
{
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

int main()
{
    muzeu M;
    client C("Timothy","Gates");
    sala S[6]{sala("Casierie",0),sala("SalaCuPicturi",1),sala("SalaCuMachete",1),sala("SalaCuSculpturi",2),sala("sala5",2), sala("Reviews-Iesire",1)};

    fin>>M; //citeste date despre muzeu (primele 3 randuri din fisier) - overloaded operator
    Staff(M); //citeste date despre staff
    //C.IncepeTur();

    S[1].AdaugaExponat("a", "b", 500);
    S[1].AdaugaExponat("c", "d", 700);

    //in functie de recenzii (array ul scor din clasa muzeu) se alege o data pe luna Sala Preferata-> constructor de copiere
   // sala Preferata (S[3]);
   cout<<S[1]; //afiseaza numele si numarul de exponate - overloaded operator

   return 0;

}


