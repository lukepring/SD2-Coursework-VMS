//
//  vms_database.hpp
//  SD2 Coursework VMS
//
//  Created by Luke Pring on 19/03/2025.
//

#include <sqlite3.h>
#include <iostream>

using namespace std;

class VMSDatabase {
private:
    string db_path = "";
public:
    VMSDatabase() {
        sqlite3 *db;
           char *zErrMsg = 0;
           int rc;

           rc = sqlite3_open("test.db", &db);

           if( rc ) {
              fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
              
           } else {
              fprintf(stderr, "Opened database successfully\n");
           }
           sqlite3_close(db);
    }
};
