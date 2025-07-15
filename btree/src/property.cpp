#include "property.hpp"

Property::Property(std::string directory_path,
                   const std::string &metadata_file_name,//use const while using 
                   const std::string &index_file_name,
                   int32_t index_page_capacity,
                   int32_t data_page_capacity,
                   bool unique)
                   :DIRECTORY_PATH(std::move(directory_path)),// we are using it directly wothut no change so we can use move here
                   INDEX_FILE_NAME(index_file_name+".tree"),// can use move as anuways + will give a new copy
                   METADATA_FILE_NAME(metadata_file_name+".meta"),// we adding here as we want more control for file fomet not want tp rely on user 
                   SEEK_ROOT(emptyPage),//enum vlaue 0 but we can read 
                   MAX_INDEX_PAGE_CAPACITY(index_page_capacity),
                   MAX_DATA_PAGE_CAPACITY(data_page_capacity),
                   ROOT_STATUS(emptyPage),
                     UNIQUE(unique){
    INDEX_FULL_PATH = DIRECTORY_PATH + INDEX_FILE_NAME;
    METADATA_FULL_PATH = DIRECTORY_PATH + METADATA_FILE_NAME;
    MIN_DATA_PAGE_CAPACITY = static_cast<int32_t>(std::ceil(MAX_DATA_PAGE_CAPACITY / 2.0))-1;//can have haif ot max 
    MIN_INDEX_PAGE_CAPACITY = static_cast<int32_t>(std::ceil(MAX_INDEX_PAGE_CAPACITY / 2.0))-1;
    SPLIT_POS_INDEX_PAGE = static_cast<int32_t>(std::ceil(MAX_INDEX_PAGE_CAPACITY / 2.0));//on the middle
    SPLIT_POS_DATA_PAGE = static_cast<int32_t>(std::ceil(MAX_DATA_PAGE_CAPACITY / 2.0));
                     }


//use memeber initilaxer when you are using const refernce and some valye going to neeed inside body

//move is used to tanfer data without copying 
// ceil to round up neares int as it can be float bcz we are not sure amx size is int or float return double 
// can use (int_32)val insted of staic_cast



void Property::load(std::fstream &file) {
    file >> DIRECTORY_PATH >> INDEX_FILE_NAME >> METADATA_FILE_NAME >> SEEK_ROOT
         >> MAX_INDEX_PAGE_CAPACITY >> MAX_DATA_PAGE_CAPACITY >> ROOT_STATUS >> UNIQUE;// overload >> operator is used to read from file overwrite the values whic was used by constructor 

    INDEX_FULL_PATH = DIRECTORY_PATH + INDEX_FILE_NAME;
    METADATA_FULL_PATH = DIRECTORY_PATH + METADATA_FILE_NAME;
    MIN_INDEX_PAGE_CAPACITY = static_cast<std::int32_t>(std::ceil(MAX_INDEX_PAGE_CAPACITY / 2.0)) - 1;
    MIN_DATA_PAGE_CAPACITY = static_cast<std::int32_t>(std::ceil(MAX_DATA_PAGE_CAPACITY / 2.0)) - 1;
    SPLIT_POS_INDEX_PAGE = static_cast<std::int32_t>(std::floor(MAX_INDEX_PAGE_CAPACITY / 2.0));
    SPLIT_POS_DATA_PAGE = static_cast<std::int32_t>(std::floor(MAX_DATA_PAGE_CAPACITY / 2.0));
}

void Property::save(std::fstream &file) const {
    file << DIRECTORY_PATH << " " << INDEX_FILE_NAME << " " << METADATA_FILE_NAME << " "
         << SEEK_ROOT << " " << MAX_INDEX_PAGE_CAPACITY << " " << MAX_DATA_PAGE_CAPACITY << " "
         << ROOT_STATUS << " " << UNIQUE;
}
