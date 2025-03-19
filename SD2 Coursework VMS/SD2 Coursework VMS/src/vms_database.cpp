//
//  vms_database.cpp
//  SD2 Coursework VMS
//
//  Created by Luke Pring on 19/03/2025.
//

#include "../include/vms_database.hpp"

std::vector<std::vector<std::string>> VMSDatabase::results;

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

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        if (request == "appointments") {
            sql = "SELECT * FROM \"Appointment Management\";";
        } else if (request == "owners") {
            sql = "SELECT * FROM \"Owner Management\";";
        } else if (request == "pets") {
            sql = "SELECT * FROM \"Pet Management\";";
        } else if (request == "staff") {
            sql = "SELECT * FROM \"Staff Management\";";
        } else {
            fprintf(stderr, "Invalid request\n");
            return "";
        }

        // Clear previous results before running the query
        results.clear();

        rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Operation done successfully\n");

            // Print the retrieved data
            if (!results.empty()) {
                for (const auto& row : results) {
                    for (const auto& col : row) {
                        std::cout << col << " | ";
                    }
                    std::cout << std::endl;
                }
            } else {
                std::cout << "No results found.\n";
            }
        }
    }
    sqlite3_close(db);

    return results.empty() ? "" : results[0][0];  // Return first result (or empty if no data)
}
