//
//  main.cpp
//  SD2 Coursework VMS
//
//  Written by Luke Pring, Jack Turner and Richard Akole.
//

#include <iostream>
#include "include/appointments.hpp"
#include "include/owners.hpp"
#include "include/pets.hpp"
#include "include/vms_database.hpp"

using namespace std;

VMSDatabase db;

string name;
int accessLevel;

void displayMainMenu() {
    cout << "=============================\n";
    cout << " Veterinary Management System\n";
    cout << "=============================\n";
    
    // User Roles / Login (Luke & Richard)
    
    bool loggedIn = false;
    
    while (!loggedIn) {
    
        string nameInput = "";
        string passwordInput = "";
        
        cout << "Name: ";
        cin >> nameInput;
        
        cout << "Password: ";
        cin >> passwordInput;
        
        vector staffData = db.getData("staff");
    
    
        for(vector record : staffData) {
            if(nameInput == record[3]) {
                if(passwordInput == record[4]) {
                    name = record[3];
                    accessLevel = stoi(record[2]);
                    cout << "=============================\nWelcome, " << name << "\nAccess Level: " << record[1] << "\n";
                    loggedIn = true;
                    break;
                } else {
                    cout << "Incorrect password. Please try again.";
                }
            }
        }
    }
    
    
    // Menu (Jack)

    cout << "=============================\n";
    cout << "1. Manage Pets\n";
    cout << "2. Manage Owners (Coming Soon)\n";
    cout << "3. Manage Appointments (Coming Soon)\n";
    cout << "0. Exit\n";
    cout << "=============================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    

    do {
        displayMainMenu();
        cin >> choice;
        cin.ignore(); // to clear newline left in buffer

        switch (choice) {
            case 1:
                displayPetMenu();
                break;

            case 2:
                cout << "\n[!] Owner management not implemented yet.\n\n";
                break;

            case 3:
                cout << "\n[!] Appointment system not implemented yet.\n\n";
                break;

            case 0:
                cout << "Exiting VMS. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}
