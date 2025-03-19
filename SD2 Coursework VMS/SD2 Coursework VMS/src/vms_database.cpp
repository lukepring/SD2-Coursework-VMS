//
//  vms_database.cpp
//  SD2 Coursework VMS
//
//  Created by Luke Pring on 19/03/2025.
//

#include "../include/vms_database.hpp"

VMSDatabase::VMSDatabase() {
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
          fprintf(stderr, "Database connected successfully!\n---------\n");
         sql = "SELECT * from \"Appointment Management\";";
           
           rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
           
           if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
           } else {
               fprintf(stdout, "Operation done successfully\n");
           }
           
       }
       sqlite3_close(db);
}

string VMSDatabase::getData(string request) {
    return "";
}
