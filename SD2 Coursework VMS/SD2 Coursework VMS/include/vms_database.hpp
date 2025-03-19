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
    
    VMSDatabase() {
        
        sqlite3 *db;
           char *zErrMsg = 0;
           int rc;
        char *sql;
        const char* data = "Callback function called";

           db_path = (fs::path(__FILE__).parent_path().parent_path() / "db" / "vms.db").string();
        
           rc = sqlite3_open(db_path.c_str(), &db);

           if( rc ) {
              fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
              
           } else {
              fprintf(stderr, "Opened database successfully\n");
             sql = "SELECT * from \"Appointment Management\";";
               
               rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
               
               if( rc != SQLITE_OK ){
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
               } else {
                   fprintf(stdout, "Operation done successfully\n");
               }
               
           }
           //sqlite3_close(db);
    }
};
