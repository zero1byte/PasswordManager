#ifndef DATA_FILE_FLAG
#define DATA_FILE_FLAG


using namespace std;
#include <iostream>
#include <string>
#include <ctime>
#include "../utility/color.h"


#define undefined "Undefined"
#define EMPTY ""
#define PATTERN FWHT("<<------------------------------------------>>")




class Object
{
private:
    string timeDate()
    {
        time_t timestamp;
        time(&timestamp);
        return ctime(&timestamp);
    }

public:
    string domain;
    string password;
    string remarks;
    string createdAt;
    string updatedAt;
    int ID = 0;

    Object(string domain, string password, string remarks)
    {
        this->domain = domain;
        this->password = password;
        this->remarks = remarks;

        // initialize date and time to object (e.g. createdAt)
        this->createdAt = this->timeDate();
        this->updatedAt = this->timeDate();
    };

    Object()
    {
        // cout << "Empty Object Init" << endl;
    };

    Object(Object &d) = default;
    // {
    //     cout << "Assign to other Object" << endl;
    //     this->domain = d.domain;
    // }

    bool print()
    {
        cout << PATTERN << endl;
        cout << KRED << "Id          : " << (this->ID) << RST << endl;
        cout << KBLU << "Domain Name : " << (this->domain == EMPTY ? undefined : this->domain) << RST << endl;
        cout << KMAG << "Password    : " <<(this->password == EMPTY ? undefined : this->password) << RST <<endl;
        cout << KWHT << "Remarks     : " <<(this->remarks == EMPTY ? undefined : this->remarks) << RST <<endl;
        cout << RST << "Created At  : " <<(this->createdAt == EMPTY ? undefined "\n" : this->createdAt)<<RST;
        cout << RST << "Updated At  : " <<(this->updatedAt == EMPTY ? undefined "\n" : this->updatedAt)<<RST;
        cout << PATTERN << endl;
        return true;
    };

    bool input()
    {
        cout << "Enter Domain name : ";
        cin >> this->domain;
        cout << "Enter Password : ";
        cin >> this->password;
        cout << "Enter Remarks : ";
        cin >> this->remarks;
        this->createdAt = this->timeDate();
        this->updatedAt = this->timeDate();
        return true;
    };
};


#endif