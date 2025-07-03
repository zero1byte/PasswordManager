using namespace std;

#include <iostream>
#include <string.h>

#include "constants.cpp"
#include "cryptolib/files.cpp"

int main()
{
    filesManagement f1(DATA_FOLDER);
    if (!f1.is_directory())
    {
       f1.create_database_folder();
    }

    f1.create_file("hello.json");
}