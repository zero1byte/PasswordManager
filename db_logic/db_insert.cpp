#include "password_db.h"
#include "cstring"
#include <fstream>

bool PasswordDB::insertEntry(const PasswordEntry &entry){
    std::ofstream wal(walFile, std::ios::app);//only for output into file
    //app means append
    wal << "INSERT|" << entry.website << "|" << entry.username << "|" << entry.password << "\n";
    wal.close();

    std::fstream recordFile(tableFile,std::ios::in | std::ios::out |std::ios::binary);//support both input output in file
    //in for input out for output and biary for formet
   
    TableMeta meta;
    recordFile.read((char*)&meta,sizeof(meta));

    if(!freeList.empty()){
        long deletedIndex = freeList.back();
        freeList.pop_back();

        recordFile.seekp(deletedIndex);//Changing the current write position pointer in file
        //we have open file as fstream so it gonna overwrite at that position 
        recordFile.write((char*)&entry,sizeof(entry));
        indexMap[entry.website] =deletedIndex;

    }
    else{
        recordFile.seekp(0, std::ios::end);//__off – A file offset object.
                                      //__dir – The direction in which to seek.
                                      //pointer at the end of file
        long insertIndex  = recordFile.tellp();
        recordFile.write((char*)&entry,sizeof(entry));
        indexMap[entry.website] =insertIndex;
        
        //incread record count in meta and then update meta in file

        meta.recordCount++;
        recordFile.seekp(0);
        recordFile.write((char*)&meta,sizeof(meta));
    }
    recordFile.close();
    saveIndex();
    std::cout<<"Sucessful insertion done";
    return true;
}