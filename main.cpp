using namespace std;

#include <iostream>
#include <string.h>

#include "cryptolib/keys.cpp"

#ifndef FILES_FLAG
#include "cryptolib/files.cpp"
#elifndef CONSTANT_FILE_FLAG
#include "constants.cpp"
#elifndef DATA_FILE_FLAG
#include "db_logic/data.cpp"
#endif

int main()
{
    // string str="X0NJjA/onqSIodeyEb5R9BLyfLVTHXgT3r6XagBOo/Ow1bbpFiy63oBIjjNseFDMPNchQU2UMHzpTrU+NGvy8VdrxWyCN6fsI7PC2xp95Yeay/Vwxaeb9dvicEd5esGjT0pmvn1YrEDR+5fF2ksOWGeuX2//JRTL9+cr71QFh0N3L7P2Nk78GFOgTlK0T1+ALjEkKaQf416sU3SnM+nbv/LlGieApYUlz5kPDDgwrHHk8eDbr1RJlg8SFAF1BIzkuWNykVHZlnn1eH34SBweqaN3D91GxzF300LPh7unID+wN0iE2V5m7OH2iV/MD5tXxJ5eU17lPFeKUl+8fCxShg=="
    // ;cout<<str.length()<<endl;
    // filesManagement f1(DATA_FOLDER);

    // if (!f1.is_directory())
    // {
    //     f1.create_database_folder();
    // }

    // keys k1;
    // // k1.rsa_key_pair();
    // string encrypted_key = k1.encrypt("HELLO World !");
    // cout <<"Encrypted key: "<< k1.decrypt(encrypted_key) << endl;

    // string private_key = f1.get_private_key();
    // string public_key = f1.get_public_key();
    // string key = "helloworld";
    // AES sysmmentric(public_key, private_key, key);

    // string encrypted_private_key = sysmmentric.encrypt_private_key();
    // string encrypted_public_key = sysmmentric.encrypt_public_key();
    // cout<<encrypted_private_key<<endl;
    // cout<<"Decrypt : "<<sysmmentric.decrypt_public_key(key)<<endl;


    Object object("facebook.com","#JNJD)#$","first Account");
    object.print();

}