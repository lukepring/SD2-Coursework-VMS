//
//  vms_database.hpp
//  SD2 Coursework VMS
//
//  Created by Luke Pring on 19/03/2025.
//

#include <sqlite3.h>
#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

class VMSDatabase {
private:
    string db_path = "";
    
    static vector<vector<string>> results; // Stores all query results

    static int callback(void *data, int argc, char **argv, char **azColName) {
        vector<string> row;
        for (int i = 0; i < argc; i++) {
            row.push_back(argv[i] ? argv[i] : "NULL");
        }
        results.push_back(row); // Store each row properly
        return 0;
    }
    
    
public:
    
    // Database function declarations
    VMSDatabase();
    std::vector<std::vector<std::string>> getData(string request);
    void printTable(string request);
    void addRecord(string request, std::vector<std::string> fields);
    
};

