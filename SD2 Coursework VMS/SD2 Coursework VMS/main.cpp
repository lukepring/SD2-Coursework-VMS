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
owner_management owner;

string name;
int accessLevel;
string type;

void authentication() {
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
                    type = record[1];
                    loggedIn = true;
                    break;
                } else {
                    cout << "Incorrect password. Please try again.";
                }
            }
        }
    }
}

void displayMainMenu() {
    cout << "=============================\n";
    cout << "Veterinary Management System\n";
    cout << "=============================\n";
    
    cout << "Welcome, " << name << " (" << type << ")!\n";
    // Menu (Jack)

    cout << "=============================\n";
    cout << "1. Manage Pets\n";
    cout << "2. Manage Owners (Coming Soon)\n";
    cout << "3. Manage Appointments\n";
    cout << "0. Exit\n";
    cout << "=============================\n";
    cout << "Enter your choice: ";
}

int main() {
    
    cout << "=============================\n";
    cout << "Please log in.\n";
    cout << "=============================\n";
    
    authentication();
    
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
                if(accessLevel > 1) {
                    owner.display_owner_menu();
                } else {
                    cout << "=============================\n";
                    cout << "Access denied for " << name << " at access level " << accessLevel;
                }
                
                break;

            case 3:
                if(accessLevel > 1) {
                    cout << "\n[!] Appointment system not implemented yet.\n\n";
                } else {
                    cout << "=============================\n";
                    cout << "Access denied for " << name << " at access level " << accessLevel;
                }
                
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
