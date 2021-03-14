#include <iostream>
#include "muzeu.h"
#include "client.h"
#include "sala.h"
#include <cmath>
#define NRMAXSALI 7

using namespace std;

void Staff(muzeu M)
{
    M.AdaugaDepartament("Curatenie");
    M.AdaugaDepartament("Management");
    M.AdaugaDepartament("Paza");
    M.AdaugaDepartament("Casierie");
    M.AdaugaDepartament("Ghid");
    M.AdaugaPersonal("Paza", "Alexander Hunold");
    M.AdaugaPersonal("Paza", "Lex De Haan");
    M.AdaugaPersonal("Management", "Daniel Faviet");
    M.AdaugaPersonal("Casierie", "Lisa Ozer");
    M.AdaugaPersonal("Curatenie", "Nandita Sarchand");
    M.AdaugaPersonal("Curatenie", "Curtis Davies");
    M.AdaugaPersonal("Ghid", "Louise Doran");


    M.AfiseazaPersonal();
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
    Staff(M);
    //C.IncepeTur();

    S[1].AdaugaExponat("a", "b", 500);
    //in functie de recenzii (array ul scor din clasa muzeu) se alege o data pe luna Sala Preferata-> constructor de copiere
   // sala Preferata (S[3]);

   return 0;

}


