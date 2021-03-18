#include <iostream>
#include "muzeu.h"


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
    out<<"Bine ati venit la "<<M.nume<<" situat la adresa "<<M.adresa<<"\n";
    out<<"Programul de vizitare si preturile aferente:\n";
    string zile_sapt[7]={"Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica"};
    for(int i=0;i<7;i++) {
        out << zile_sapt[i] << ": " << M.ore_vizitare[i] ;
        if (M.ore_vizitare[i] != "-")
            out<< ", "<<M.pret_zile[i]<<" lei";

        out<<"\n";

    }
  return out;
}


