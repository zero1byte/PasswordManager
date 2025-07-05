using namespace std;

#include <iostream>
#include <string.h>

#include "cryptolib/keys.cpp"

#ifndef FILES_FLAG
#include "cryptolib/files.cpp"
#elifndef CONSTANT_FILE_FLAG
#include "constants.cpp"
#endif

int main()
{
    filesManagement f1(DATA_FOLDER);
    if (!f1.is_directory())
    {
        f1.create_database_folder();
    }

    keys k1;
    // k1.rsa_key_pair();
    string encrypted_key = k1.encrypt("HELLO World !");
    cout << k1.decrypt("encrypted_key") << endl;
}