//
//  appointments.cpp
//  SD2 Coursework VMS
//
//  Written by Jack Turner.
//

#include "../include/appointments.hpp"
#include "../include/vms_database.hpp"
#include "../include/externals.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void appointmentMenu() {
    Appointment appointment;
    int choice;

    do {
        std::cout << "\n-------- Appointment Menu --------\n";
        std::cout << "1. Schedule Appointment\n";
        std::cout << "2. Modify Appointment\n";
        std::cout << "3. Cancel Appointment\n";
        std::cout << "4. View Appointments\n";
        std::cout << "0. Return to Main Menu\n";
        std::cout << "----------------------------------\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                scheduleAppointment();
                break;
            case 2:
                modifyAppointment();
                break;
            case 3:
                removeAppointment();
                break;
            case 4:
                displayAppointments();
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void scheduleAppointment() {
    string date, time, details;
    int petID, ownerID;

    cout << "Enter appointment date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter appointment time (HH:MM): ";
    cin >> time;
    cin.ignore();
    cout << "Enter details for the appointment: ";
    getline(cin, details);
    cout << "Enter Pet ID: ";
    cin >> petID;
    cout << "Enter Owner ID: ";
    cin >> ownerID;

    vector<string> fields = {
        "'" + date + "'",
        "'" + time + "'",
        "'" + details + "'",
        to_string(petID),
        to_string(ownerID),
        "'scheduled'"
    };

    string query = "INSERT INTO `Appointment Management` (date, time, appointment_details, pet_id, owner_id, status) VALUES";
    db.addRecord(query, fields);

    cout << "Appointment scheduled successfully.\n";
}

void modifyAppointment() {
    int appointmentID;
    cout << "Enter appointment ID to modify: ";
    cin >> appointmentID;

    string query = "SELECT * FROM `Appointment Management` WHERE `Appointment ID` = " + to_string(appointmentID) + " LIMIT 1;";
    auto result = db.getData(query);

    if (result.empty()) {
        cout << "Appointment not found.\n";
        return;
    }

    cout << "Current appointment info:\n";
    vector<string> fields = result[0];
    cout << "Date: " << fields[1] << ", Time: " << fields[2] << ", Details: " << fields[3] << "\n";

    int choice;
    cout << "What would you like to modify?\n1. Date\n2. Time\n3. Details\n4. Status\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    string newValue, column;
    switch (choice) {
        case 1: column = "date"; cout << "Enter new date (YYYY-MM-DD): "; break;
        case 2: column = "time"; cout << "Enter new time (HH:MM): "; break;
        case 3: column = "appointment_details"; cout << "Enter new details: "; break;
        case 4: column = "status"; cout << "Enter new status: "; break;
        default: cout << "Invalid choice.\n"; return;
    }

    getline(cin, newValue);
    string updateQuery = "UPDATE `Appointment Management` SET " + column + " = '" + newValue + "' WHERE `Appointment ID` = " + to_string(appointmentID) + ";";
    db.getData(updateQuery);

    cout << "Appointment updated.\n";
}

void removeAppointment() {
    int appointmentID;
    cout << "Enter appointment ID to remove: ";
    cin >> appointmentID;

    string query = "SELECT * FROM `Appointment Management` WHERE `Appointment ID` = " + to_string(appointmentID) + " LIMIT 1;";
    auto result = db.getData(query);

    if (result.empty()) {
        cout << "Appointment not found.\n";
        return;
    }

    cout << "Are you sure you want to delete this appointment? (y/n): ";
    char confirm;
    cin >> confirm;
    if (tolower(confirm) == 'y') {
        db.deleteRecord("Appointment Management", appointmentID);
        cout << "Appointment removed.\n";
    } else {
        cout << "Operation cancelled.\n";
    }
}

void displayAppointments() {
    string query = "SELECT * FROM `Appointment Management`;";
    auto results = db.getData(query);

    if (results.empty()) {
        cout << "No appointments scheduled.\n";
        return;
    }

    cout << left << setw(5) << "ID" << setw(12) << "Date" << setw(8) << "Time"
         << setw(25) << "Details" << setw(8) << "Pet ID" << setw(10)
         << "Owner ID" << setw(12) << "Status" << endl;
    cout << string(80, '-') << endl;

    for (auto& row : results) {
        for (auto& col : row) {
            cout << setw(12) << col;
        }
        cout << endl;
    }
}
