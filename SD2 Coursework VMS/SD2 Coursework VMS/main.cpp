//
//  main.cpp
//  SD2 Coursework VMS
//
//  Written by Luke Pring & Jack Turner.
//

#include <iostream>
#include "include/appointments.hpp"
#include "include/owners.hpp"
#include "include/pets.hpp"
#include "include/vms_database.hpp"

using namespace std;

VMSDatabase db;

void displayMainMenu() {
    cout << "=============================\n";
    cout << " Veterinary Management System\n";
    cout << "=============================\n";
    
    // User Roles / Login
    
    string nameInput = "";
    string passwordInput = "";
    
    cout << "Name: ";
    cin >> nameInput;
    
    cout << "Password: ";
    cin >> passwordInput;
    
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
