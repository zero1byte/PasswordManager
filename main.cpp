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
    // string encrypted_key = k1.encrypt("HELLO World !");
    // cout <<"Encrypted key: "<< k1.decrypt(encrypted_key) << endl;

    string private_key = f1.get_private_key();
    string public_key = f1.get_public_key();
    string key = "helloworld";
    AES sysmmentric(public_key, private_key, key);

    // string encrypted_private_key = sysmmentric.encrypt_private_key();
    // string encrypted_public_key = sysmmentric.encrypt_public_key();

    // cout<<"Decrypt : "<<sysmmentric.decrypt_public_key(key)<<endl;
}