#ifndef DB_FILE_FLAG

#define DB_FILE_FLAG

#include <fstream>
#include <iostream>
#include <vector>

#include "../cryptolib/keys.cpp"

#include "../utility/color.h"
#include "../utility/data.cpp"

#include "files.cpp"

#include "../constants.cpp"

class Database
{
private:
    string file_name = "storage.json";
    string directory = DATA_FOLDER;
    string path;

public:
    Database()
    {
        // make a path of file
        filesManagement file;
        string path = this->directory;
        path.append("/");
        path.append(file_name);
        this->path = path;
        // check for is storage file exists or not
        if (!file.is_fileExist(path))
        {
            // create storage file
            file.create_file(this->file_name);
        }
    }

    // insert a object into storage
    bool insert(const Object &obj)
    {

        return true;
    }
    // get a all object from storage
    void *get()
    {
        std::ifstream file(this->path, std::ios::binary);
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0);

        // assign array of object to Object type pointer
        void *buffer = new Object[size];
        cout << "Size : " << size << endl;
        file.read(reinterpret_cast<char *>(buffer), size);

        return buffer;
    }
};

class localStorage
{
private:
    Object *store = NULL;
    size_t length = 0;

public:
    localStorage()
    {
        Database db;
        // assign file data to this array of objects
        if (this->store == NULL)
            this->store = reinterpret_cast<Object *>(db.get());
    };

    // get total number of objects store at 'store' data structure
    int collections()
    {
        if (this->store == NULL)
            return -1;

        cout << 0 << ". Domain name : " << this->store->domain << endl;
        cout << "Error : Something went wrong" << endl;
        return -1;
    };

    bool insert(Object obj)
    {
        return true;
    };
};
#endif