#ifndef LABORATOR_POO_CLIENT_H
#define LABORATOR_POO_CLIENT_H
#include <string>
#include <iostream>


class client {

	std::string lastname, firstname;
	std::string type; //1- adult, 2-student, 3-child =>se acorda reduceri in functie de tip; adult->0%, 2->20%, 3->50%

public:
    //constructor
    explicit client(std::string lastname="-", std::string firstname="-", std::string type="-");
    virtual ~client()=default;
    void Feedback();
    int Type() const;
    friend std::ostream &operator<<(std::ostream &out, const client &C);
    friend std::istream &operator>>(std::istream &in, client &C);

};

#endif //LABORATOR_POO_CLIENT_H
