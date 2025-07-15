#ifndef B_PLUS_TREE_BPLUSTREE_HPP
#define B_PLUS_TREE_BPLUSTREE_HPP
#include <vector>
#include <functional>
#include <queue>

#include <data_page.hpp>
#include <index_page.hpp>


template<
typename FieldType,
typename RecordType,
typename Compare = std::greater<FieldType>,//compare keys bydefault is greter set if you dont give itslef is a type
typename FieldMapping = std::function<FieldType(RecordType&)>
>



class BPlusTree {

    friend struct Page<TYPES()>;//allow this struct to use my privete things
    friend struct DataPage<TYPES()>;
    friend struct IndexPage<TYPES()>;

    private:

    std::fstream b_plus_index_file;
    std::fstream metadata_file;
    Property properties;
    Compare gt;
    FieldMapping get_search_field;

   auto create_index()->void;

   auto locate_data_page(const FieldType& key) -> std::streampos;// return a pointer to the data page where the key is located streampos is pointer data type in file 

   auto insert(std::streampos seek_page, PageType type, RecordType& record) -> InsertResult;//return tyoe definde in page

   auto remove(std::streampos seek_page, PageType type, const FieldType& key) -> RemoveResult<FieldType>;

   public:

   explicit BPlusTree(Property property,FieldMapping search_field,Compare greater =Compare());

   auto insert(RecordType& record) -> void;//function overloding 

   auto remove(const FieldType& key) -> void;

   auto search(const FieldType& key) -> std::vector<RecordType>;

   auto above(const FieldType & lower_bound) -> std::vector<RecordType>;

   auto below(const FieldType & upper_bound) -> std::vector<RecordType>;

   auto between(const FieldType & lower_bound, const FieldType & upper_bound) -> std::vector<RecordType>;
};

#include "bplustree.tpp"

#endif // B_PLUS_TREE_BPLUSTREE_HPP

    
    