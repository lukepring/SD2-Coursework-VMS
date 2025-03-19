//
//  vms_database.hpp
//  SD2 Coursework VMS
//
//  Created by Luke Pring on 19/03/2025.
//

#include <sqlite3.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

class VMSDatabase {
private:
    string db_path = "";
    static int callback(void *data, int argc, char **argv, char **azColName){
        int i;
        fprintf(stderr, "%s: ", (const char*)data);
        for(i = 0; i<argc; i++){
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }
public:
    
    VMSDatabase();
    
    string getData(string request);
    
};
