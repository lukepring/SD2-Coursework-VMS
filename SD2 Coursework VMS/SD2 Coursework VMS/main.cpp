//
//  main.cpp
//  SD2 Coursework VMS
//
//  Created by Luke Pring & Jack Turner on 10/03/2025.
//

#include <iostream>
#include "include/appointments.hpp"
#include "include/owners.hpp"
#include "include/pets.hpp"
#include "include/vms_database.hpp"

using namespace std;

/*int main(int argc, const char * argv[]) {
    std::cout << "VMS v1.0.0\n---------\n";
    VMSDatabase VMSDatabase;

    std::cout << VMSDatabase.getData("pets")[0][2] << std::endl;
    
    
    
    VMSDatabase.printTable("owners");
    
    VMSDatabase.deleteRecord("owners", 5);
    
    // VMSDatabase.addRecord("owners", {"Roger", "12 Lane Street, London", "07365287615", "roger@mail.org"});
    
    return 0;
    
}*/

void displayMainMenu() {
    cout << "=============================\n";
    cout << " Veterinary Management System\n";
    cout << "=============================\n";
    cout << "1. Manage Pets\n";
    cout << "2. Manage Owners (Coming Soon)\n";
    cout << "3. Manage Appointments (Coming Soon)\n";
    cout << "4. Billing & Payments (Coming Soon)\n";
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

            case 4:
                cout << "\n[!] Billing functionality not implemented yet.\n\n";
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
