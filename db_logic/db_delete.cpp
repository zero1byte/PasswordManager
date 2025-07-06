#include "password_db.h"
#include "fstream"
#include "cstring"
bool PasswordDB::deleteEntry(const std::string& website){
    if(indexMap.find(website)==indexMap.end()){
        std::cout << "❌ Not found.\n";
        return false;
    }
    long indexTodelete = indexMap[website];
    indexMap.erase(website);
    PasswordEntry entry ={};// why empty why notintiliazed
    // to avoid garbage values it initilaze very value as emtu inside strcut
    strcpy(entry.website, "<DELETED>");
    std::fstream recordFile(tableFile,std::ios::in |std::ios::out |std::ios::binary);
    recordFile.seekp(indexTodelete);
    recordFile.write((char*)&entry,sizeof(entry));
    freeList.push_back(indexTodelete);


    //write insde the wal file 
    std::ofstream wal(walFile, std::ios::app);
    wal << "DELETE|" << website << "\n";
    wal.close();

    recordFile.close();
    saveIndex();
    std::cout<<"Sucessful deletion done";
    return true;

}