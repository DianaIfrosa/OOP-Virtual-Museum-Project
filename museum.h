#ifndef LABORATOR_POO_MUZEU_H
#define LABORATOR_POO_MUZEU_H
#include "MuseumRoom.h"
#include "SouvenirShop.h"
#include "room.h"
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

static const int no_days=7;

//singleton
class museum {

private:

	static museum* m; //instanta

    std::string name;
	std::string visiting_hours[no_days]; // la fiecare pozitie (zi a sapt)
    //e interval orar de genul 11-18 sau - daca nu se poate vizita in acea zi
    std::string adress;
    int prices[no_days]; //pret pe zile
	int museum_funds;

    double feedback_score;
    //map cu nume personal de tipul departament: nume; numele sunt retinute in vector de stringuri
    std::unordered_map<std::string, std::vector<std::string> > name_staff;

	museum();

protected:
	int number_of_rooms;
	//vector de pointeri la clasa de baza (sala); pe ultima pozitie e intotdeauna magazinul de suveniruri
	std:: vector< room*> S;

public:

	~museum();
    void AddStaff(const std::string& departament,const std::string& nume);
    void FeedbackScore();
    void DisplayStaff();
    void AddDepartment(const std::string& departament);

    void AddExhibit(int nr_sala, const std::string& nume_exponate="-", const std::string& data_aducerii="-", int pret=0);

    int  PricePerDay(int nr_zi_saptamana);
    void StartTour();
    void ShowRoom(int nsala);
    void ReadRoomsData();
    void Info() const ;
	void ReceiveDonations(int val);

	//setters
	void CloseCertainRoom(int number);
	void OpenCertainRoom(int number);

	//getters
	int NoRooms() const;
    //overload >>
    friend std::istream &operator >> (std::istream &in, museum &M);
    //overload <<
    friend std::ostream &operator <<(std::ostream &out, const museum &M);

    //sterg cc si op= pentru a nu putea duplica obiecte de tip muzeu
    museum(const museum&)=delete;
	museum& operator=(const museum&)=delete;

    static museum* get_museum(){
		if(m==nullptr)
			m=new museum;
		return m;
    }

};

#endif //LABORATOR_POO_MUZEU_H
