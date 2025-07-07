#ifndef CONSTANT_FILE_FLAG
#define CONSTANT_FILE_FLAG 


const char *APP_NAME = "Password Manager";

// this is used to encrypt the password or data, whereas private key (Master Key) is known by only user
const char *PUBLIC_KEY = "public key";

// folder name, where we store all the data files
// const char *DATA_FOLDER="cryptolib//temp"; // 1
const char *DATA_FOLDER = "database_folder";

const char *PRIVATE_KEY_FILE_NAME = "private_key.txt";
const char *PUBLIC_KEY_FILE_NAME = "public_key.txt";

#endif