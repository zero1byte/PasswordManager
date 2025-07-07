#ifndef FILES_FLAG
#define FILES_FLAG
// All files operation e.g: keys files & directory

#include <iostream>
#include <string.h>

#include <filesystem>
#include <sys/stat.h>
#include <fstream>

namespace fs=std::filesystem;

using namespace std;
#ifndef CONSTANT_FILE_FLAG
#include "constants.cpp"
#endif

// flag for files check

class filesManagement
{

public:
    string database_dir;

    //make a folder
    filesManagement(string data_folder)
    {
        database_dir = data_folder;

        // At begin  check from a dir, which use to store all data
        filesystem::path path = data_folder;
        if (!filesystem::is_directory(path))
        {
            cout << "Error : data folder not exists !!\n";
        }
    }

    filesManagement()
    {

        database_dir = DATA_FOLDER;

        // At begin  check from a dir, which use to store all data
        filesystem::path path = DATA_FOLDER;
        if (!filesystem::is_directory(path))
        {
            cout << "Error : data folder not exists !!\n";
        }
    }

    // check for either dir created or not
    bool is_directory()
    {
        return filesystem::is_directory(database_dir);
    }

    // create database directory
    bool create_database_folder()
    {
        const char *dir = database_dir.c_str();

        // mode_t permissions = S_IRWXU | S_IRGRP | S_IXGRP | S_IXOTH;

        int r = mkdir(dir,
                      __S_IREAD | __S_IWRITE | __S_IEXEC |
                          S_IRWXG | S_IRWXU);

        if (!r)
            cout << "Database folder created" << endl;
        else
            cout << "Database folder create failed !!" << endl;

        return r;
    }

    // create file inside database folder
    bool create_file(string file_name)
    {

        // check file_name include "//" or not
        if (file_name.find("/"))
            file_name.insert(0, "/");

        string file_path = database_dir.append(file_name);

        // check is file already exists
        if (filesystem::exists(file_path))
        {
            cout << "File already exixts" << endl;
            return false;
        }

        cout << "Creating file : " << file_path << endl;
        ofstream file;
        file.open(file_path, std::ios::ate);
        if (file.is_open())
            // cout << "file created success" << endl;
            return true;
        else
            // cout << "file creation failed" << endl;
            return false;
        file.close();
        return false;
    }

    // write inside files
    string get_private_key()
    {
        string path = DATA_FOLDER;
        path.append("/");
        path.append(string(PRIVATE_KEY_FILE_NAME));

        std::ifstream inputFile(path);
        if (!inputFile.is_open())
        {
            cout << "private key find could not open!!\n";
            return NULL;
        }
        string line;
        string private_key;

        // get line by line data from file
        while (std::getline(inputFile, line))
        {
            private_key.append(line);
            private_key.append("\n");
        }

        inputFile.close();
        return private_key;
    }
    string get_public_key()
    {
        string path = DATA_FOLDER;
        path.append("/");
        path.append(string(PUBLIC_KEY_FILE_NAME));

        std::ifstream inputFile(path);
        if (!inputFile.is_open())
        {
            cout << "public_key key find could not open!!\n";
            return NULL;
        }
        string line;
        string public_key;

        // get line by line data from file
        while (std::getline(inputFile, line))
        {
            public_key.append(line);
            public_key.append("\n");
        }

        inputFile.close();
        return public_key;
    }

    //check is file have inside in folder or not
    bool is_fileExist(string filename){
        return fs::exists(filename);
    }

};


#endif