//
//  vms_database.cpp
//  SD2 Coursework VMS
//
//  Written by Luke Pring.
//

#include "../include/vms_database.hpp"

std::vector<std::vector<std::string>> VMSDatabase::results;

// Database function implementation

VMSDatabase::VMSDatabase() {
    sqlite3 *db;
       char *zErrMsg = 0;
       int rc;

       db_path = (fs::path(__FILE__).parent_path().parent_path() / "db" / "vms.db").string();
    
       rc = sqlite3_open(db_path.c_str(), &db);

       if( rc ) {
          fprintf(stderr, "VMSDatabase - Can't open database: %s\n", sqlite3_errmsg(db), "Please restart the program and ensure the database is in the correct location. (/db/vms.db)");
       } else {
          fprintf(stderr, "VMSDatabase - Database connected successfully!\n");
       }
       sqlite3_close(db);
}

std::vector<std::vector<std::string>> VMSDatabase::getData(string request) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string sql;
    const char* data = "Callback function called";

    db_path = (fs::path(__FILE__).parent_path().parent_path() / "db" / "vms.db").string();
    rc = sqlite3_open(db_path.c_str(), &db);

    if (rc) {
        fprintf(stderr, "VMSDatabase - Can't open database: %s\n", sqlite3_errmsg(db));
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
            fprintf(stderr, "VMSDatabase - Invalid request\n");
            return results;
        }

        // Clear previous results before running the query
        results.clear();

        rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "VMSDatabase - SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            //fprintf(stdout, "Operation done successfully\n");

            // Print the retrieved data
            if (results.empty()) {
                std::cout << "VMSDatabase - No results found.\n";
            }
        }
    }
    sqlite3_close(db);

    return results;
}

void VMSDatabase::printTable(string request) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string sql;
    const char* data = "Callback function called";

    db_path = (fs::path(__FILE__).parent_path().parent_path() / "db" / "vms.db").string();
    rc = sqlite3_open(db_path.c_str(), &db);

    if (rc) {
        fprintf(stderr, "VMSDatabase - Can't open database: %s\n", sqlite3_errmsg(db));
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
        }

        // Clear previous results before running the query
        results.clear();

        rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "VMSDatabase - SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            //fprintf(stdout, "Operation done successfully\n");

            // Print the retrieved data
            if (!results.empty()) {
                for (const auto& row : results) {
                    for (const auto& col : row) {
                        std::cout << col << " | ";
                    }
                    std::cout << std::endl;
                }
            } else {
                std::cout << "VMSDatabase - No results found.\n";
            }
        }
    }
    sqlite3_close(db);
}

void VMSDatabase::addRecord(string request, std::vector<std::string> fields) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string sql;
    const char* data = "Callback function called";

    db_path = (fs::path(__FILE__).parent_path().parent_path() / "db" / "vms.db").string();
    rc = sqlite3_open(db_path.c_str(), &db);

    if (rc) {
        fprintf(stderr, "VMSDatabase - Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        if (request == "pets") {
            sql = "INSERT INTO \"Pet Management\" (Name, Breed, Age, MedicalHistory, VaccinationStatus, OwnerID) VALUES (\"" + fields[0] + "\", \"" + fields[1] + "\", " + fields[2] + ", \"" + fields[3] + "\", " + fields[4] + ", " + fields[5] + ");";
        } else if (request == "owners") {
            sql = "INSERT INTO \"Owner Management\" (Name, Address, PhoneNumber, Email) VALUES (\"" + fields[0] + "\", \"" + fields[1] + "\", \"" + fields[2] + "\", \"" + fields[3] + "\");";
            cout << sql;
        } else if (request == "appointments") {
            sql = "INSERT INTO \"Appointment Management\" (DateTime, AppointmentDetails, PetID, OwnerID) VALUES (\"" + fields[0] + "\", \"" + fields[1] + "\", " + fields[2] + ", " + fields[3] + ");";
        } else if (request == "staff") {
            sql = "INSERT INTO \"Staff Management\" (Type, AccessLevel, Name, Passcode) VALUES (\"" + fields[0] + "\", " + fields[1] + ", \"" + fields[2] + "\", " + fields[3] + ");";
        } else {
            fprintf(stderr, "VMSDatabase - Invalid request\n");
            return;
        }

        // Clear previous results before running the query
        results.clear();

        rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "VMSDatabase - SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
    }
    sqlite3_close(db);

    return;
}

void VMSDatabase::deleteRecord(string request, int id) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string sql;
    const char* data = "Callback function called";

    db_path = (fs::path(__FILE__).parent_path().parent_path() / "db" / "vms.db").string();
    rc = sqlite3_open(db_path.c_str(), &db);

    if (rc) {
        fprintf(stderr, "VMSDatabase - Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        if (request == "pets") {
            sql = "DELETE FROM \"Pet Management\" WHERE PetID = " + std::to_string(id);
        } else if (request == "owners") {
            sql = "DELETE FROM \"Owner Management\" WHERE OwnerID = " + std::to_string(id);
        } else if (request == "appointments") {
            sql = "DELETE FROM \"Appointment Management\" WHERE AppointmentID = " + std::to_string(id);
        } else if (request == "staff") {
            sql = "DELETE FROM \"Staff Management\" WHERE StaffID = " + std::to_string(id);
        } else {
            fprintf(stderr, "VMSDatabase - Invalid request\n");
            return;
        }

        // Clear previous results before running the query
        results.clear();

        rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "VMSDatabase - SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
    }
    sqlite3_close(db);

    return;
}
