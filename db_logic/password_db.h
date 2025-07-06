#ifndef PASSWORD_DB_H
#define PASSWORD_DB_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

struct TableMeta {
    int recordSize;
    int recordCount;
    char tableName[50];
};

struct PasswordEntry {
    char website[100];
    char username[100];
    char password[100];
    char remarks[100];
};

class PasswordDB {
private:
    std::unordered_map<std::string, long> indexMap;  //key as websote name
    std::vector<long> freeList;//marked deleted node's location in db 
    const char* tableFile = "passwords.tbl";//actual database stores here
    const char* walFile = "wal.log";
    const char* indexFile = "index.idx";// stor indexes of those entries

    bool isDeleted(const PasswordEntry& entry);

    void saveIndex();
    void saveMeta(std::fstream& file, const TableMeta& meta);

public:
    PasswordDB();
    void createTable();
    void buildIndex();

    bool insertEntry(const PasswordEntry& entry);
    PasswordEntry viewEntry(const std::string& website);
    bool deleteEntry(const std::string& website);
    bool updateEntry(const std::string& website, const std::string& newPassword);
};

#endif // PASSWORD_DB_H
