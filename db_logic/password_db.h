#ifndef PASSWORD_DB_H
#define PASSWORD_DB_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include "cstring"

struct TableMeta
{
    int recordSize;
    int recordCount;
    char tableName[50];
};

struct PasswordEntry
{
    char website[100];
    char username[100];
    char password[100];
    char remarks[100];
};

class PasswordDB
{
private:
    std::unordered_map<std::string, long> indexMap; // key as website name
    std::vector<long> freeList;                     // marked deleted node's location in db
    const char *tableFile = "passwords.tbl";        // actual database stores here
    const char *walFile = "wal.log";
    const char *indexFile = "index.idx"; // store indexes of those entries
    void saveMeta(std::fstream &file, const TableMeta &meta);

public:
    PasswordDB()
    {
        this->createTable();
        this->buildIndex();
    }

    void buildIndex()
    {
        std::ifstream indFile(indexFile, std::ios::binary);
        if (indFile.good())
        {
            int size;
            indFile.read((char *)&size, sizeof(size));
            // This reads 4 bytes (usually) from the binary file into the memory location of size.
            // we are assign value into size using file reading assinging input to var from file
            for (int i = 0; i < size; i++)
            { // inside file pointer is manhed by file itelf
                size_t lenghtOfWebsiteName;
                // platfrom dependent you and try to use sam as buidindex data type becyae int !=sizet
                indFile.read((char *)&lenghtOfWebsiteName, sizeof(lenghtOfWebsiteName));

                std::string websiteName(lenghtOfWebsiteName, ' ');
                indFile.read(&websiteName[0], lenghtOfWebsiteName);
                long indexOfEntry;
                indFile.read((char *)&indexOfEntry, sizeof(indexOfEntry));

                // buiding hashmap

                indexMap[websiteName] = indexOfEntry;
            }
            // done with hashmap now build deleted slot memory addres in a vector

            int numberOfDeletedRecords;
            indFile.read((char *)&numberOfDeletedRecords, sizeof(numberOfDeletedRecords));

            for (int i = 0; i < numberOfDeletedRecords; i++)
            {
                long indexOfDeletedEntry;
                indFile.read((char *)&indexOfDeletedEntry, sizeof(indexOfDeletedEntry));
                freeList.push_back(indexOfDeletedEntry);
            }
            indFile.close();
        }
        else
        {
            std::ifstream recordFile(tableFile, std::ios::binary);
            if (!recordFile)
                return;
            TableMeta meta;
            recordFile.read((char *)&meta, sizeof(meta));
            // skip metadat from file and update pos to first entry
            PasswordEntry entry;
            long indexOfEntry = recordFile.tellg(); // tell the current positon oif the pointer

            while (recordFile.read((char *)&entry, sizeof(entry)))
            {
                if (isDeleted(entry))
                {
                    freeList.push_back(indexOfEntry);
                }
                else
                {
                    // put in map
                    indexMap[entry.website] = indexOfEntry;
                }
                // update the index for next one
                indexOfEntry = recordFile.tellg();
            }
            recordFile.close();

            // now we need to save this hshmap into index db file

            saveIndex();
        }
        return;
    }

    void saveIndex()
    {
        // we are going to write inside a file in binary
        std::ofstream indFile(indexFile, std::ios::binary);
        int n = indexMap.size();
        // we are going to write the size of file in hashmao file first
        indFile.write((char *)&n, sizeof(n));

        for (auto &[website, ind] : indexMap)
        {
            size_t lengthOfWebsiteName = website.length();
            indFile.write((char *)&lengthOfWebsiteName, sizeof(lengthOfWebsiteName));
            indFile.write(website.c_str(), lengthOfWebsiteName); // c_str give the pointer with safety of null
            indFile.write((char *)&ind, sizeof(ind));
        } // hashmao only cnatins valid one

        n = freeList.size();
        indFile.write((char *)&n, sizeof(n));
        for (long indexOfDeletedEntry : freeList)
        {
            indFile.write((char *)&indexOfDeletedEntry, sizeof(indexOfDeletedEntry));
        }
        indFile.close();
    }

    void createTable()
    {
        std::ifstream openTableFile(tableFile); // open table file and assign into var
        if (openTableFile.good())
        { // check if we able to open it
            openTableFile.close();
            return; // table is already creted user not came first time
        }
        std::ofstream newFile(tableFile, std::ios::binary);
        TableMeta meta = {sizeof(PasswordEntry), 0, "passwords"};
        newFile.write((char *)&meta, sizeof(meta)); // writng value in bytes in file from meta structyre
        newFile.close();
        return;
    }

    bool isDeleted(const PasswordEntry &entry)
    { // use const you cant chnage the entry here
        if (strcmp(entry.website, "<DELETED>") == 0)
            return true; // return 0 1 or -ve base on condtions
        return false;
    }

    PasswordEntry viewEntry(const std::string &website)
    {
        if (indexMap.find(website) == indexMap.end())
        {
            std::cout << "❌ Not found.\n";
            return {};
        }
        std::ifstream file(tableFile, std::ios::binary);
        file.seekg(indexMap[website]);
        PasswordEntry entry;
        file.read((char *)&entry, sizeof(entry));
        file.close();

        if (!isDeleted(entry))
        {
            return entry;
        }
        else
        {
            std::cout << "❌ Entry was deleted.\n";
        }

        return entry;
    }

    bool deleteEntry(const std::string &website)
    {
        if (indexMap.find(website) == indexMap.end())
        {
            std::cout << "❌ Not found.\n";
            return false;
        }
        long indexTodelete = indexMap[website];
        indexMap.erase(website);
        PasswordEntry entry = {}; // why empty why notintiliazed
        // to avoid garbage values it initilaze very value as emtu inside strcut
        strcpy(entry.website, "<DELETED>");
        std::fstream recordFile(tableFile, std::ios::in | std::ios::out | std::ios::binary);
        recordFile.seekp(indexTodelete);
        recordFile.write((char *)&entry, sizeof(entry));
        freeList.push_back(indexTodelete);

        // write insde the wal file
        std::ofstream wal(walFile, std::ios::app);
        wal << "DELETE|" << website << "\n";
        wal.close();

        recordFile.close();
        saveIndex();
        std::cout << "Sucessful deletion done";
        return true;
    }

    bool updateEntry(const std::string &website, const std::string &newPassword)
    {
        if (indexMap.find(website) == indexMap.end())
        {
            std::cout << "❌ Not found.\n";
            return false;
        }
        std::fstream recordFile(tableFile, std::ios::in | std::ios::out | std::ios::binary);
        recordFile.seekg(indexMap[website]);
        PasswordEntry entry;
        recordFile.read((char *)&entry, sizeof(entry));
        strcpy(entry.password, newPassword.c_str());
        recordFile.seekp(indexMap[website]);
        recordFile.write((char *)&entry, sizeof(entry));
        recordFile.close();

        std::ofstream wal(walFile, std::ios::app);
        wal << "UPDATE|" << website << "|" << newPassword << "\n";
        wal.close();

        saveIndex();
        std::cout << "🔁 Updated password for: " << website << "\n";
        return 0;
    };

    bool insertEntry(const PasswordEntry &entry)
    {
        std::ofstream wal(walFile, std::ios::app); // only for output into file
        // app means append
        wal << "INSERT|" << entry.website << "|" << entry.username << "|" << entry.password << "\n";
        wal.close();

        std::fstream recordFile(tableFile, std::ios::in | std::ios::out | std::ios::binary); // support both input output in file
        // in for input out for output and biary for formet

        TableMeta meta;
        recordFile.read((char *)&meta, sizeof(meta));

        if (!freeList.empty())
        {
            long deletedIndex = freeList.back();
            freeList.pop_back();

            recordFile.seekp(deletedIndex); // Changing the current write position pointer in file
            // we have open file as fstream so it gonna overwrite at that position
            recordFile.write((char *)&entry, sizeof(entry));
            indexMap[entry.website] = deletedIndex;
        }
        else
        {
            recordFile.seekp(0, std::ios::end); //__off – A file offset object.
                                                //__dir – The direction in which to seek.
                                                // pointer at the end of file
            long insertIndex = recordFile.tellp();
            recordFile.write((char *)&entry, sizeof(entry));
            indexMap[entry.website] = insertIndex;

            // incread record count in meta and then update meta in file

            meta.recordCount++;
            recordFile.seekp(0);
            recordFile.write((char *)&meta, sizeof(meta));
        }
        recordFile.close();
        saveIndex();
        std::cout << "Sucessful insertion done";
        return true;
    };


};

#endif // PASSWORD_DB_H
