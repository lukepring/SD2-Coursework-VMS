//
//  appointments.cpp
//  SD2 Coursework VMS
//
//  Written by Jack Turner.
//

#ifndef APPOINTMENTS_HPP
#define APPOINTMENTS_HPP

#include <string>
#include "../include/vms_database.hpp"

class Appointment {
public:
    Appointment();
    void appointmentMenu();
    void scheduleAppointment();
    void modifyAppointment();
    void removeAppointment();
    void displayAppointments();
};

#endif
