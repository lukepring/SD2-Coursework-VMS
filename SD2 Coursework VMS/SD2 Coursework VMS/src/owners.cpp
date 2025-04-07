#include "../include/owners.hpp"


void owner_management::display_menu() {

	int choice;
	do {
		cout << "\n--------Owner Management System--------\n" << endl;
		cout << "1. Add Owner" << endl;
		cout << "2. view Owners" << endl;
		cout << "3. Delete Owner" << endl;
		cout << "4. Update Owner" << endl;
		cout << "5. save owners to file\n" << endl;
		cout << "6. load owners from files\n" << endl;
		cout << "0. Return to main menu" << endl;
		cout << "----------------------------------------" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number: ";
			cin >> choice;
		}

		switch (choice) {
		case 1:
			add_owner();
			break;
		case 2:
			view_owner();
			break;
		case 3:
			delete_owner();
			break;
		case 4:
			update_owner();
			break;
		case 5:
			save_owners_to_file();
			break;
		case 6:
			load_owners_from_file();
			break;
		case 0:
			cout << "Returning to main menu..." << endl;
			break;

		default:
			cout << "invalid choice. please try again." << endl;
		}

	} while (choice != 0);

}

void owner_management::add_owner() {
	string name;
	string address;
	string phone_number;
	string email;
	int owner_id;

	int pet_id;

	// if/while to provide a number ID for each owner.

	do {
		cout << "Enter a number from 1-100 to assign an ID to the pet: ";
		cin >> owner_id;

		if (owner_id < 1 || owner_id > 100) {
			cout << "Invalid input. Please enter a number from 1-100.\n";
		}
	} while (owner_id < 1 || owner_id > 100);
	// Loop continues if input is out of range

   // Mapping pet_id to a new value
	int mappedvalue = 1000 + owner_id;
	cout << "Your owner ID is: " << mappedvalue << endl;


	cout << "Enter owner name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter owner address: ";
	getline(cin, address);

	//regex to check the phone number format

	regex ownernum_pattern(R"(\d{11})");

	do {
		cout << "Enter the owner's phone number: ";
		cin >> phone_number;

		if (!regex_match(phone_number, ownernum_pattern)) {
			cout << "Invalid input. Please enter a valid phone number.\n";
		}

	} while (!regex_match(phone_number, ownernum_pattern));

	// regex to check the email format
	regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	do {
		cout << "Enter the owner's email address: ";
		getline (cin, email);

		if (!regex_match(email, email_pattern)) {
			cout << "Invalid email format. Please enter a valid email address.\n";
		}
	} while (!regex_match(email, email_pattern));

	vector<string> owner_data = { name, address, phone_number, email, owner_id };
	db.addRecord("owner", owner_data);
	cout << "Owner added successfully.\n" << endl;
}

void owner_management::view_owner() {

	string term;
	cout << "Search by owner ID or Name:"; getline(cin >> ws, term);
	auto all_owners = db.getdata("owner");
	for (auto& owner : all_owners) {
		if (owner [0] == term || owner[1] == term) {
			cout << "\nOwner ID: " << owner[0] << endl;
			cout << "Name: " << owner[1] << endl;
			cout << "Address: " << owner[2] << endl;
			cout << "Phone Number: " << owner[3] << endl;
			cout << "Email: " << owner[4] << endl;
			cout << "----------------------------------------" << endl;

			return;
		}
	}
	cout << "No pet found with the given ID or Name.\n" << endl;
}

void owner_management::delete_owner() {
	string owner_id;
	cout << "Enter the owner ID to delete: "; getline(cin >> ws, owner_id);
	cin >> owner_id;
	char confirm;
	cout << "Are you sure you want to delete owner with ID" << owner_id << "? (y/n): ";
	if (tolower(confirm) == 'y') {
		db.deleteRecord("pets", stoi(owner_id));
		cout << "Owner deleted successfully.\n" << endl;	
		
	}
	else {
		cout << "Deletion cancelled.\n" << endl;
	}
}

void owner_management::update_owner() {
	string owner_id;
	cout << "Enter the owner ID to update: "; getline(cin >> ws, owner_id);
	cin >> owner_id;
	char confirm;
	cout << "Are you sure you want to update owner with ID" << owner_id << "? (y/n): ";
	if (tolower(confirm) == 'y') {
		db.updateRecord("pets", stoi(owner_id));
		cout << "Owner updated successfully.\n" << endl;
	}
	else {
		cout << "Update cancelled.\n" << endl;
	}
}

void owner_management::save_owners_to_file() {
	ofstream file("owners.txt");
	if (file.is_open()) {
		auto all_owners = db.getdata("owner");
		for (const auto& owner : all_owners) {
			file << owner[0] << "," << owner[1] << "," << owner[2] << "," << owner[3] << "," << owner[4] << endl;
		}
		file.close();
		cout << "Owners saved to file successfully.\n" << endl;
	}
	else {
		cout << "Error opening file for writing.\n" << endl;
	}
}

void owner_management::load_owners_from_file() {
	// Load owners from file
	ifstream file("owners.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			string name, address, phone_number, email;
			int owner_id;
			getline(iss, name, ',');
			getline(iss, address, ',');
			getline(iss, phone_number, ',');
			getline(iss, email, ',');
			iss >> owner_id;
			vector<string> owner_data = { name, address, phone_number, email, owner_id };
			db.addRecord("owner", owner_data);
		}
		file.close();
		cout << "Owners loaded from file successfully.\n" << endl;
	}
    
