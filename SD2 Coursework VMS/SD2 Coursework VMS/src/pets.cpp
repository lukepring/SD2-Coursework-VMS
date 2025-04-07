//
//  pets.cpp
//  SD2 Coursework VMS
//
//  Created by Luke Pring on 15/03/2025.
//

#include "../include/pets.hpp"
#include "../include/vms_database.hpp"
#include <iostream>
#include <fstream>

using namespace std;

VMSDatabase db;

// Display Menu
void displayPetMenu() {
    int choice;
    do {
        cout << "\n-------- Pet Management --------\n";
        cout << "1. Add New Pet\n";
        cout << "2. View Pet\n";
        cout << "3. Update Pet\n";
        cout << "4. Remove Pet\n";
        cout << "5. View Appointment History\n";
        cout << "6. Save Pets to File\n";
        cout << "7. Load Pets from File\n";
        cout << "0. Return to Main Menu\n";
        cout << "--------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid input
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                addPet();
                break;
            case 2:
                viewPet();
                break;
            case 3:
                updatePet();
                break;
            case 4:
                removePet();
                break;
            case 5:
                viewAppointmentHistory();
                break;
            case 6:
                savePetsToFile();
                break;
            case 7:
                loadPetsFromFile();
                break;
            case 0:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}

// Add Pet
void addPet() {
    string name, breed, age, medHist, vacStatus, ownerID;
    cout << "Enter Pet Name: "; getline(cin >> ws, name);
    cout << "Enter Breed: "; getline(cin, breed);
    cout << "Enter Age: "; getline(cin, age);
    cout << "Enter Medical History: "; getline(cin, medHist);
    cout << "Enter Vaccination Status (0 or 1): "; getline(cin, vacStatus);
    cout << "Enter Owner ID: "; getline(cin, ownerID);

    vector<string> petData = { name, breed, age, medHist, vacStatus, ownerID };
    db.addRecord("pets", petData);
    cout << "Pet added successfully.\n";
}

// View Pet
void viewPet() {
    string term;
    cout << "Search by Pet ID or Name: "; getline(cin >> ws, term);
    auto allPets = db.getData("pets");
    for (auto &pet : allPets) {
        if (pet[0] == term || pet[1] == term) {
            cout << "\nPet ID: " << pet[0] << endl;
            cout << "Name: " << pet[1] << endl;
            cout << "Breed: " << pet[2] << endl;
            cout << "Age: " << pet[3] << endl;
            cout << "Medical History: " << pet[4] << endl;
            cout << "Vaccination Status: " << pet[5] << endl;
            cout << "Owner ID: " << pet[6] << endl;
            return;
        }
    }
    cout << "No pet found with that ID or Name.\n";
}

// Update Pet
void updatePet() {
    string petID;
    cout << "Enter Pet ID to update: "; getline(cin >> ws, petID);
    auto pets = db.getData("pets");
    for (auto &pet : pets) {
        if (pet[0] == petID) {
            string name, breed, age, medHist, vacStatus, ownerID;
            cout << "Enter new name (current: " << pet[1] << "): "; getline(cin, name);
            cout << "Enter new breed (current: " << pet[2] << "): "; getline(cin, breed);
            cout << "Enter new age (current: " << pet[3] << "): "; getline(cin, age);
            cout << "Enter new medical history: "; getline(cin, medHist);
            cout << "Enter new vaccination status: "; getline(cin, vacStatus);
            cout << "Enter new owner ID: "; getline(cin, ownerID);

            vector<string> updatedPet = { name, breed, age, medHist, vacStatus, ownerID };
            db.deleteRecord("pets", stoi(petID));
            db.addRecord("pets", updatedPet);
            cout << "Pet updated successfully.\n";
            return;
        }
    }
    cout << "Pet ID not found.\n";
}

// Remove Pet
void removePet() {
    string petID;
    cout << "Enter Pet ID to remove: "; getline(cin >> ws, petID);
    char confirm;
    cout << "Are you sure you want to delete pet with ID " << petID << "? (y/n): ";
    cin >> confirm;
    if (tolower(confirm) == 'y') {
        db.deleteRecord("pets", stoi(petID));
        cout << "Pet deleted successfully.\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

// View Appointment History
void viewAppointmentHistory() {
    string term;
    cout << "Enter Pet ID or Name to view appointment history: "; getline(cin >> ws, term);
    auto pets = db.getData("pets");
    string petID = "";
    for (auto &pet : pets) {
        if (pet[0] == term || pet[1] == term) {
            petID = pet[0];
            break;
        }
    }
    if (petID.empty()) {
        cout << "Pet not found.\n";
        return;
    }
    auto appointments = db.getData("appointments");
    for (auto &appt : appointments) {
        if (appt[3] == petID) {
            cout << "\nAppointment ID: " << appt[0] << endl;
            cout << "Date/Time: " << appt[1] << endl;
            cout << "Details: " << appt[2] << endl;
        }
    }
}

// Save Pets to File
void savePetsToFile() {
    ofstream file("pets_backup.txt");
    auto pets = db.getData("pets");
    for (auto &pet : pets) {
        for (size_t i = 0; i < pet.size(); ++i) {
            file << pet[i];
            if (i != pet.size() - 1) file << ",";
        }
        file << endl;
    }
    file.close();
    cout << "Pet records saved to pets_backup.txt\n";
}

// Load Pets from File
void loadPetsFromFile() {
    ifstream file("pets_backup.txt");
    string line;
    while (getline(file, line)) {
        vector<string> fields;
        string value;
        for (char c : line) {
            if (c == ',') {
                fields.push_back(value);
                value = "";
            } else {
                value += c;
            }
        }
        fields.push_back(value);
        if (fields.size() == 7) {
            fields.erase(fields.begin()); // remove ID if present
        }
        db.addRecord("pets", fields);
    }
    file.close();
    cout << "Pet records loaded from pets_backup.txt\n";
}
