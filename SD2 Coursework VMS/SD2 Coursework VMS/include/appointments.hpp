//
//  appointments.cpp
//  SD2 Coursework VMS
//
//  Written by Jack Turner.
//

#ifndef APPOINTMENTS_HPP
#define APPOINTMENTS_HPP

#include <string>
#include <vector>
using namespace std;
 
struct Appointment {
    int id;
    std::string dateTime;
    std::string details;
    int petID;
    int ownerID;
    std::string status;
};
 
 void appointmentMenu();
 void scheduleAppointment();
 void modifyAppointment();
 void removeAppointment();
 void displayAppointments();
 
 #endif



