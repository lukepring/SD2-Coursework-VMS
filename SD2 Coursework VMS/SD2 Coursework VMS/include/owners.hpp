//
//  owners.hpp
//  SD2 Coursework VMS
//
//  Written by Oluwatobi Obafemi.
//

#ifndef OWNERS_HPP
#define OWNERS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

// Define the Owner structure to hold owner-related data
struct owner {
    string name;
    string email;
    string address;
    string phone_number;
    int owner_id;
};

class owner_management {
    // Declare the pet management menu function
    void display_menu();
    
    
    
    
    // Declare function to add a owner
    void add_owner();
    
    // Declare function to view a pet by ID or name
    void view_owner();
    
    // Declare function to delete owner by ID or name
    void delete_owner();
    
    // Declare function to update owner by ID or name
    void update_owner();
    
    // Declare function to load owner records to file
    void load_owners_from_file();
    
    // Declare function to save owner records from file
    void loadPetsFromFile();
    
    void save_owners_to_file();
    
};

// Declare a global vector to store pets (this could later be encapsulated in a class)
extern vector<owner> owners;

#endif // OWNER_HPP
