// #include "password_db.h"
#include <cstring>

PasswordDB::PasswordDB(){
    createTable();
    buildIndex();
}
void PasswordDB::createTable(){
    std::ifstream openTableFile(tableFile);//open table file and assign into var 
    if(openTableFile.good()){//check if we able to open it
        openTableFile.close();
        return; // table is already creted user not came first time
    }
    std::ofstream newFile(tableFile,std::ios::binary);
    TableMeta meta = { sizeof(PasswordEntry), 0, "passwords" };
    newFile.write((char*)&meta, sizeof(meta)); //writng value in bytes in file from meta structyre
    newFile.close();
    return;
}

bool PasswordDB::isDeleted(const PasswordEntry & entry){//use const you cant chnage the entry here
    if(strcmp(entry.website,"<DELETED>")==0) return true;// return 0 1 or -ve base on condtions
    return false;

}
void PasswordDB::saveIndex(){
    // we are going to write inside a file in binary
    std::ofstream indFile(indexFile,std::ios::binary);
    int n  = indexMap.size();
    //we are going to write the size of file in hashmao file first
    indFile.write((char*)&n,sizeof(n));

    for(auto &[website,ind] :indexMap){
        size_t lengthOfWebsiteName = website.length();
        indFile.write((char*)&lengthOfWebsiteName,sizeof(lengthOfWebsiteName));
        indFile.write(website.c_str(),lengthOfWebsiteName);// c_str give the pointer with safety of null
        indFile.write((char*)&ind,sizeof(ind));
    }//hashmao only cnatins valid one

    n = freeList.size();
    indFile.write((char*)&n, sizeof(n));
    for (long indexOfDeletedEntry : freeList) {
        indFile.write((char*)&indexOfDeletedEntry , sizeof(indexOfDeletedEntry));
    }
    indFile.close();


}
void PasswordDB::buildIndex(){
    std::ifstream indFile(indexFile,std::ios::binary);
    if(indFile.good()){
        int size;
        indFile.read((char*)&size,sizeof(size));
        //This reads 4 bytes (usually) from the binary file into the memory location of size.
        //we are assign value into size using file reading assinging input to var from file
        for(int i =0; i<size; i++){//inside file pointer is manhed by file itelf
            size_t lenghtOfWebsiteName;
            //platfrom dependent you and try to use sam as buidindex data type becyae int !=sizet
            indFile.read((char*)&lenghtOfWebsiteName,sizeof(lenghtOfWebsiteName));

            std::string websiteName(lenghtOfWebsiteName,' ');
            indFile.read(&websiteName[0],lenghtOfWebsiteName);
            long indexOfEntry;
            indFile.read((char*)&indexOfEntry,sizeof(indexOfEntry));

            //buiding hashmap

            indexMap[websiteName] = indexOfEntry;

        }
        //done with hashmap now build deleted slot memory addres in a vector

        int numberOfDeletedRecords;
        indFile.read((char*)&numberOfDeletedRecords,sizeof(numberOfDeletedRecords));

        for(int i =0; i<numberOfDeletedRecords;i++){
                long indexOfDeletedEntry;
                indFile.read((char*)&indexOfDeletedEntry,sizeof(indexOfDeletedEntry));
                freeList.push_back(indexOfDeletedEntry);

        }
        indFile.close();
    }
    else{
         std::ifstream recordFile(tableFile, std::ios::binary);
         if (!recordFile) return;
         TableMeta meta;
         recordFile.read((char*)&meta, sizeof(meta));
         //skip metadat from file and update pos to first entry 
        PasswordEntry entry;
        long indexOfEntry =recordFile.tellg();//tell the current positon oif the pointer

        while(recordFile.read((char*)&entry,sizeof(entry))){
            if(isDeleted(entry)){
                freeList.push_back(indexOfEntry);
            }
            else{
                //put in map
                indexMap[entry.website] = indexOfEntry;
            }
            //update the index for next one
            indexOfEntry = recordFile.tellg();
        }
        recordFile.close();

        // now we need to save this hshmap into index db file 

        saveIndex();

    }
    return ;

    
}