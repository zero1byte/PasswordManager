// #include "password_db.h"

PasswordEntry PasswordDB::viewEntry(const std::string& website) {
    if (indexMap.find(website) == indexMap.end()) {
        std::cout << "❌ Not found.\n";
        return {};
    }
    std::ifstream file(tableFile, std::ios::binary);
    file.seekg(indexMap[website]);
    PasswordEntry entry;
    file.read((char*)&entry, sizeof(entry));
    file.close();
    
    if (!isDeleted(entry)) {
        return entry;
    } else {
        std::cout << "❌ Entry was deleted.\n";

    }
    
    return entry;
}