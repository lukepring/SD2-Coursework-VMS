//
//  vms_database.cpp
//  SD2 Coursework VMS
//
//  Created by Luke Pring on 19/03/2025.
//

#include "../include/vms_database.hpp"


string VMSDatabase::output[9];

VMSDatabase::VMSDatabase() {
    sqlite3 *db;
       char *zErrMsg = 0;
       int rc;

       db_path = (fs::path(__FILE__).parent_path().parent_path() / "db" / "vms.db").string();
    
       rc = sqlite3_open(db_path.c_str(), &db);

       if( rc ) {
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db), "Please restart the program and ensure the database is in the correct location. (/db/vms.db)");
       } else {
          fprintf(stderr, "Database connected successfully!\n---------\n");
       }
       sqlite3_close(db);
}

string VMSDatabase::getData(string request) {
    
    sqlite3 *db;
       char *zErrMsg = 0;
       int rc;
    string sql;
    const char* data = "Callback function called";

       db_path = (fs::path(__FILE__).parent_path().parent_path() / "db" / "vms.db").string();
    
       rc = sqlite3_open(db_path.c_str(), &db);

       if( rc ) {
           fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db), "Please restart the program and ensure the database is in the correct location. (/db/vms.db)");
          
       } else {
           
           if (request == "appointments") {
               sql = "SELECT * from \"Appointment Management\";";
               fprintf(stdout, "Appointments\n");
           } else if (request == "owners") {
               sql = "SELECT * from \"Owner Management\";";
               fprintf(stdout, "Owners\n");
               std::cout << sql;
           } else if (request == "pets") {
               sql = "SELECT * from \"Pet Management\";";
           } else if (request == "staff") {
                sql = "SELECT * from \"Staff Management\";";
           } else {
               fprintf(stderr, "Invalid request\n");
           }
                  
           std::cout << sql.c_str();
           rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
           std::cout << "Output array memory address: " << output << std::endl;
           
           if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
           } else {
               fprintf(stdout, "Operation done successfully\n");
               fprintf(stdout, "Data: %s\n", output[0].c_str());
           }
           
       }
       sqlite3_close(db);
    
    return "";
}
