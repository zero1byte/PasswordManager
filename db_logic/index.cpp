
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cstring>
#include "password_db.h"

using namespace std;
int main() {
  
    PasswordDB db;
    PasswordEntry p1 = {"facebook.com", "user1", "pass1","fuck you bitch"};
    PasswordEntry p2 = {"gmail.com", "user2", "pass2"};

    db.insertEntry(p1);
    db.insertEntry(p2);

    std::cout<<db.viewEntry("facebook.com").username<<endl;
    std::cout<<db.viewEntry("facebook.com").password<<endl;
    std::cout<<db.viewEntry("facebook.com").remarks<<endl;
    db.updateEntry("facebook.com", "newpass123");
    db.viewEntry("facebook.com");

    db.deleteEntry("facebook.com");
    db.viewEntry("facebook.com");
     std::cout<<db.viewEntry("facebook.com").username<<endl;
    std::cout<<db.viewEntry("facebook.com").password<<endl;

    return 0;
}
