#include "page.hpp"

//WRITNG FUNCTION BODY FOR PAGE STRUCT
template<TYPES(typename)>
Page<TYPES()>::Page(BPlusTree<TYPES()> *tree) : tree(tree){}



template<TYPES(typename)>
auto Page<TYPES()>::is_full() -> bool {
    return len() == max_capacity();
}


template<TYPES(typename)>
auto Page<TYPES()>::is_empty() -> bool {
    return len() == 0;
}

template<TYPES(typename)>
auto Page<TYPES()>::save(std::streampos pos) -> void {
    seek(this->tree->b_plus_index_file, pos);
    write();
}
template<TYPES(typename)>
auto Page<TYPES()>::load(std::streampos pos) -> void {
    seek(this->tree->b_plus_index_file, pos);
    read();
}