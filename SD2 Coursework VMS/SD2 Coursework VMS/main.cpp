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

int main(int argc, const char * argv[]) {
    std::cout << "VMS v1.0.0\n---------\n";
    VMSDatabase VMSDatabase;

    std::cout << VMSDatabase.getData("pets")[0][2] << std::endl;
    
    
    
    VMSDatabase.printTable("owners");
    
    VMSDatabase.deleteRecord("owners", 5);
    
    // VMSDatabase.addRecord("owners", {"Roger", "12 Lane Street, London", "07365287615", "roger@mail.org"});
    
    return 0;
    
}
