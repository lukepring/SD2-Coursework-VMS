//
//  main.cpp
//  SD2 Coursework VMS
//
//  Written by Jack Turner.
//

#ifndef APPOINTMENTS_HPP
#define APPOINTMENTS_HPP

#include <string>
#include <vector>

struct Appointment {
    int id;
    std::string dateTime;
    std::string details;
    int petID;
    int ownerID;
    std::string status;
};

extern std::vector<Appointment> appointments;

void appointmentMenu();
void scheduleAppointment();
//void modifyAppointment();
void removeAppointment();
void displayAppointments();
void loadAppointmentsFromFile();
void saveAppointmentsToFile();

#endif
