#include <iostream>
#include "bplustree.hpp"
#include "record.hpp"


int main(){
    // if you want multiple treee then use in main else can use in our contructor itslef
    const Property props(
        "./index/record/",// Path where index + metadata files are stored.
        "metadata_index_by_id_1",
        "index_by_id_1",
        get_expected_index_page_capacity<std::int32_t>(),
        get_expected_data_page_capacity<Record>(), 
        //value got from above function will be used to send as props
        true
    );
    //const std::function<std::int32_t(Record &)> used auto  here
      auto index_by_id = [](Record &record){
        return record.id;
    };

    BPlusTree<std::int32_t, Record> bPlusTree(props, index_by_id);// build btree this key
    // templaate class we are providng the type of key and value in class name rest is as useual

    // Insert some records
     

    Record record1(1, "Alice", 30);
    Record record2(2, "Bob", 25);
    Record record3(3, "Charlie", 35);

    bPlusTree.insert(record1);
    bPlusTree.insert(record2);
    bPlusTree.insert(record3);

    // Search for a record
    auto results = bPlusTree.search(2);
    for (const auto& rec : results) {
        std::cout << "Found: " << rec << std::endl;
    }

    // Remove a record
    bPlusTree.remove(2);

    // Search again to confirm removal
    results = bPlusTree.search(2);
    if (results.empty()) {
        std::cout << "Record with ID 2 not found." << std::endl;
    }

    return 0;



}


// std::istream& operator>>(std::istream& in, Record& record) {
//     return in >> record.id >> record.username >> record.email;
// } operator overload for reading Record from input stream
// std::ostream& operator<<(std::ostream& out, const Record& record) {
//     return out << record.id << " " << record.username << " " << record.email;
// }

// Option 3: mmap + binary search
// If you store dictionary like this on disk:

// csharp
// Copy
// Edit
// [id][string]
// [id][string]
// ...
// You can:

// mmap the file

// binary search by string without loading all to RAM

// get ID fast → then use int in real tree

// That’s what DBs like SQLite do under the hood for metadata.

// Even in PostgreSQL:

// sql
// Copy
// Edit
// SELECT * FROM users WHERE username = 'github.com';
// Postgres will:

// Search 'github.com' in the string index

// Grab the row’s actual ID (internal int)

// Fetch the data using that

// They still do string comparison at index level, just like us.
// But they:

// Use prefix compression

// Avoid string keys in main tables

// Cache stuff in memory

// Avoid full table scans