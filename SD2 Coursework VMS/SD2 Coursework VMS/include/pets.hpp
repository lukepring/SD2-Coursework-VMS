//
//  pets.hpp
//  SD2 Coursework VMS
//
//  Written by Jack Turner.
//

#ifndef PETS_HPP
#define PETS_HPP

#include <string>
#include <vector>
using namespace std;

// Define the Pet structure to hold pet-related data
struct Pet {
    int id;
    string name;
    string breed;
    int age;
    string medicalHistory;
    bool vaccinated;
    int ownerId;
};

// Declare the pet management menu function
void displayPetMenu();

// Declare function to add a pet
void addPet();

// Declare function to view a pet by ID or name
void viewPet();

// Declare function to update a pet by ID or name
void updatePet();

// Declare function to remove a pet by ID or name
void removePet();

// Declare function to view appointment history for a pet
void viewAppointmentHistory();

// Declare function to save pet records to file
void savePetsToFile();

// Declare function to load pet records from file
void loadPetsFromFile();

// Declare a global vector to store pets (this could later be encapsulated in a class)
extern vector<Pet> pets;

#endif // PETS_HPP
