#include "password_db.h"
#include "cstring"
#include <fstream>

bool PasswordDB::updateEntry(const std::string& website, const std::string& newPass) {
    if(indexMap.find(website)==indexMap.end()){
        std::cout << "❌ Not found.\n";
        return false;
    }
    std::fstream recordFile(tableFile, std::ios::in | std::ios::out | std::ios::binary);
    recordFile.seekg(indexMap[website]);
    PasswordEntry entry;
    recordFile.read((char*)&entry, sizeof(entry));
    strcpy(entry.password, newPass.c_str());
    recordFile.seekp(indexMap[website]);
    recordFile.write((char*)&entry, sizeof(entry));
    recordFile.close();

    std::ofstream wal(walFile, std::ios::app);
    wal << "UPDATE|" << website << "|" << newPass << "\n";
    wal.close();

    saveIndex();
    std::cout << "🔁 Updated password for: " << website << "\n";
    return 0;
}