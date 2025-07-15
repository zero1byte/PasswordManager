#ifndef B_PLUS_TREE_PROPERTY_HPP
#define B_PLUS_TREE_PROPERTY_HPP

#include <string>
#include <cstdint>//provide fixed width int8_t, int16_t, int32_t, int64_t
#include <fstream>
#include <cmath>


enum PageType{
    emptyPage = -1,
    indexPage = 0,
    dataPage = 1,
};
    //  Without enum:
    // int status = 0; // What does 0 mean?
    //  With enum:
    // enum Status { PENDING, APPROVED, REJECTED };
    // Status currentStatus = PENDING; // Clearer intent

struct Property {
    std::string DIRECTORY_PATH; // Path where index + metadata files are stored.
    std::string METADATA_FILE_NAME; // Metadata file name.
    std::string INDEX_FILE_NAME; // Index file name.
    std::string INDEX_FULL_PATH;
    std::string METADATA_FULL_PATH;

    std::int64_t SEEK_ROOT;
    std::int32_t MAX_INDEX_PAGE_CAPACITY; 
    std::int32_t MAX_DATA_PAGE_CAPACITY; 
    std::int32_t MIN_DATA_PAGE_CAPACITY; 
    std::int32_t MIN_INDEX_PAGE_CAPACITY; // to consider split and merge in btree
    std::int32_t SPLIT_POS_INDEX_PAGE;//split posiotion
    std::int32_t SPLIT_POS_DATA_PAGE; 

    std::int32_t ROOT_STATUS; 

    bool UNIQUE;
    



    explicit Property(std::string directory_path,
                      const std::string& metadata_file_name,
                      const std::string& index_file_name,
                      int32_t index_page_capacity,
                      int32_t data_page_capacity,
                      bool unique_key);

//Property p = { "./path/", "meta", "index", 1, 1, true }; // ⚠️ IMPLICIT conversion can not do this after it
// Property p("./path/", "meta", "index", 1, 1, true); // ⚠️ EXPLICIT conversion

void load(std::fstream &file);//fstream is a class
void save(std::fstream &file) const;
//const used it Won’t change any member variables of the object it’s called on
};
#endif



