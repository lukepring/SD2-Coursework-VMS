//
//  main.cpp
//  SD2 Coursework VMS
//
//  Written by Jack Turner.
//

#include "../include/appointments.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

vector<Appointment> appointments;

void loadAppointmentsFromFile() {
    appointments.clear();
    ifstream file("appointments.txt");
    if (!file) return;

    string line;
    while (getline(file, line)) {
        Appointment a;
        stringstream ss(line);
        string field;

        getline(ss, field, ','); a.id = stoi(field);
        getline(ss, a.dateTime, ',');
        getline(ss, a.details, ',');
        getline(ss, field, ','); a.petID = stoi(field);
        getline(ss, field, ','); a.ownerID = stoi(field);
        getline(ss, a.status, ',');

        appointments.push_back(a);
    }

    file.close();
}

void saveAppointmentsToFile() {
    ofstream file("appointments.txt");
    for (const auto& a : appointments) {
        file << a.id << "," << a.dateTime << "," << a.details << ","
             << a.petID << "," << a.ownerID << "," << a.status << "\n";
    }
    file.close();
}

void appointmentMenu() {
    loadAppointmentsFromFile();
    int choice;

    do {
        cout << "\n-------- Appointment Menu --------\n";
        cout << "1. Schedule Appointment\n";
        cout << "2. Modify Appointment\n";
        cout << "3. Cancel Appointment\n";
        cout << "4. View Appointments\n";
        cout << "0. Return to Main Menu\n";
        cout << "----------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: scheduleAppointment(); break;
            case 2: modifyAppointment(); break;
            case 3: removeAppointment(); break;
            case 4: displayAppointments(); break;
            case 0: cout << "Returning to Main Menu...\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void scheduleAppointment() {
    Appointment a;
    string date, time;

    cout << "Enter appointment date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter appointment time (HH:MM): ";
    cin >> time;
    cin.ignore();
    cout << "Enter details for the appointment: ";
    getline(cin, a.details);
    cout << "Enter Pet ID: ";
    cin >> a.petID;
    cout << "Enter Owner ID: ";
    cin >> a.ownerID;

    a.id = appointments.empty() ? 1 : appointments.back().id + 1;
    a.dateTime = date + " " + time;
    a.status = "scheduled";

    appointments.push_back(a);
    saveAppointmentsToFile();

    cout << "Appointment scheduled successfully.\n";
}

void modifyAppointment() {
    int appointmentID;
    cout << "Enter appointment ID to modify: ";
    cin >> appointmentID;

    auto it = find_if(appointments.begin(), appointments.end(), [appointmentID](const Appointment& a) {
        return a.id == appointmentID;
    });

    if (it == appointments.end()) {
        cout << "Appointment not found.\n";
        return;
    }

    cout << "Current appointment info:\n";
    cout << "DateTime: " << it->dateTime << ", Details: " << it->details << ", Status: " << it->status << "\n";

    int choice;
    cout << "What would you like to modify?\n1. Date & Time\n2. Details\n3. Status\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: {
            string date, time;
            cout << "Enter new date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter new time (HH:MM): ";
            cin >> time;
            it->dateTime = date + " " + time;
            break;
        }
        case 2: {
            cout << "Enter new details: ";
            getline(cin, it->details);
            break;
        }
        case 3: {
            cout << "Enter new status (e.g., scheduled, completed, cancelled): ";
            getline(cin, it->status);
            break;
        }
        default:
            cout << "Invalid choice.\n";
            return;
    }

    saveAppointmentsToFile();
    cout << "Appointment updated.\n";
}

void removeAppointment() {
    int appointmentID;
    cout << "Enter appointment ID to remove: ";
    cin >> appointmentID;

    auto it = remove_if(appointments.begin(), appointments.end(), [appointmentID](const Appointment& a) {
        return a.id == appointmentID;
    });

    if (it == appointments.end()) {
        cout << "Appointment not found.\n";
        return;
    }

    appointments.erase(it, appointments.end());
    saveAppointmentsToFile();
    cout << "Appointment removed.\n";
}

void displayAppointments() {
    if (appointments.empty()) {
        cout << "No appointments scheduled.\n";
        return;
    }

    cout << left << setw(5) << "ID" << setw(20) << "Date & Time"
         << setw(25) << "Details" << setw(8) << "Pet ID"
         << setw(10) << "Owner ID" << setw(12) << "Status" << "\n";
    cout << string(80, '-') << "\n";

    for (const auto& a : appointments) {
        cout << left << setw(5) << a.id << setw(20) << a.dateTime
             << setw(25) << a.details << setw(8) << a.petID
             << setw(10) << a.ownerID << setw(12) << a.status << "\n";
    }
}
