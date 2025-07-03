// All files operation e.g: keys files & directory

using namespace std;
#include <iostream>
#include <string.h>

#include <filesystem>
#include <sys/stat.h>
#include <fstream>

class filesManagement
{

public:
    string database_dir;

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
            return true;
        }

        cout << "Creating file : " << file_path << endl;
        ofstream file;
        file.open(file_path, std::ios::ate);
        cout << file.is_open() << endl;
        if (file.is_open())
            // cout << "file created success" << endl;
            return true;
        else
            // cout << "file creation failed" << endl;
            return false;
        file.close();
        return false;
    }

    //write inside files
    
};
