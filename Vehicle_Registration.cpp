

#include "VehicleRegistration.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;

string generateRandomPlateNumber() {
    const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string numbers = "0123456789";
    stringstream plateNumber;

    // Generate 3 random letters
    for (int i = 0; i < 3; ++i) {
        plateNumber << letters[rand() % letters.size()];
    }

    // Generate 4 random numbers
    for (int i = 0; i < 4; ++i) {
        plateNumber << numbers[rand() % numbers.size()];
    }

    return plateNumber.str();
}

void VehicleDetails::inputDetails() {
    cout << "Enter Owner Name: ";
    cin.ignore();
    getline(cin, ownerName);

    cout << "Enter Vehicle Make: ";
    getline(cin, vehicleMake);

    cout << "Enter Vehicle Model: ";
    getline(cin, vehicleModel);

    cout << "Enter Vehicle Year: ";
    getline(cin, vehicleYear);

    cout << "Enter Vehicle Identification Number (VIN): ";
    getline(cin, VIN);

    cout << "Enter Registration Date (YYYY-MM-DD): ";
    getline(cin, registrationDate);
}

void VehicleDetails::displayDetails() const {
    cout << "Vehicle Details:\n";
    cout << "Registration Number: " << registrationNumber << "\n";
    cout << "Owner Name: " << ownerName << "\n";
    cout << "Vehicle Make: " << vehicleMake << "\n";
    cout << "Vehicle Model: " << vehicleModel << "\n";
    cout << "Vehicle Year: " << vehicleYear << "\n";
    cout << "Vehicle Identification Number (VIN): " << VIN << "\n";
    cout << "Registration Date: " << registrationDate << "\n";
}

void VehicleDetails::writeToBinaryFile(ofstream &out) const {
    size_t size;

    // Write registrationNumber
    size = registrationNumber.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(registrationNumber.c_str(), size);

    // Write ownerName
    size = ownerName.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(ownerName.c_str(), size);

    // Write vehicleMake
    size = vehicleMake.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(vehicleMake.c_str(), size);

    // Write vehicleModel
    size = vehicleModel.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(vehicleModel.c_str(), size);

    // Write vehicleYear
    size = vehicleYear.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(vehicleYear.c_str(), size);

    // Write VIN
    size = VIN.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(VIN.c_str(), size);

    // Write registrationDate
    size = registrationDate.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(registrationDate.c_str(), size);
}

void VehicleDetails::readFromBinaryFile(ifstream &in) {
    size_t size;
    char *buffer;

    // Read registrationNumber
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    registrationNumber = buffer;
    delete[] buffer;

    // Read ownerName
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    ownerName = buffer;
    delete[] buffer;

    // Read vehicleMake
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    vehicleMake = buffer;
    delete[] buffer;

    // Read vehicleModel
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    vehicleModel = buffer;
    delete[] buffer;

    // Read vehicleYear
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    vehicleYear = buffer;
    delete[] buffer;

    // Read VIN
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    VIN = buffer;
    delete[] buffer;

    // Read registrationDate
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    registrationDate = buffer;
    delete[] buffer;
}

void VehicleDetails::updateRegistrationDate(const std::string &newDate) {
    registrationDate = newDate;
}

VehicleRegistrationSystem::VehicleRegistrationSystem(const std::string &filename) : databaseFilename(filename) {
    loadFromFile();
}

void VehicleRegistrationSystem::registerVehicle() {
    string registrationNumber = generateRandomPlateNumber();
    VehicleDetails details;

    if (vehicleDatabase.find(registrationNumber) != vehicleDatabase.end()) {
        cout << "This vehicle is already registered.\n";
        return;
    }

    details.inputDetails();
    details.registrationNumber = registrationNumber;  // Store the registration number in details
    vehicleDatabase[registrationNumber] = details;
    cout << "Vehicle registered successfully with Plate Number: " << registrationNumber << "\n\n";

    saveToFile(); // Save the updated database to the file in binary mode
}

void VehicleRegistrationSystem::searchVehicleByPlateNumber() const {
    string plateNumber;

    cout << "Enter Vehicle Plate Number: ";
    cin >> plateNumber;
    cout << "\n\n";

    auto it = vehicleDatabase.find(plateNumber);
    if (it != vehicleDatabase.end()) {
        it->second.displayDetails();
    } else {
        cout << "Vehicle not found.\n";
    }
}

void VehicleRegistrationSystem::loadFromFile() {
    ifstream inFile(databaseFilename, ios::binary);
    if (!inFile) {
        cerr << "Unable to open file: " << databaseFilename << "\n";
        return;
    }

    while (inFile.peek() != EOF) {
        VehicleDetails details;
        details.readFromBinaryFile(inFile);
        vehicleDatabase[details.registrationNumber] = details;
    }
    inFile.close();
}

void VehicleRegistrationSystem::saveToFile() const {
    ofstream outFile(databaseFilename, ios::binary);
    if (!outFile) {
        cerr << "Unable to open file: " << databaseFilename << "\n";
        return;
    }

    for (const auto &entry : vehicleDatabase) {
        entry.second.writeToBinaryFile(outFile);
    }
    outFile.close();
}

const std::unordered_map<std::string, VehicleDetails>& VehicleRegistrationSystem::getVehicleDatabase() const {
    return vehicleDatabase;
}

void VehicleRegistrationSystem::setVehicleDatabase(const std::unordered_map<std::string, VehicleDetails>& db) {
    vehicleDatabase = db;
}

BlueBookRenewalSystem::BlueBookRenewalSystem(VehicleRegistrationSystem &regSystem) : regSystem(regSystem) {}

void BlueBookRenewalSystem::renewVehicle() {
    string plateNumber;
    string newDate;
    double payment;

    cout << "Enter Vehicle Plate Number to renew: ";
    cin >> plateNumber;
    cout << "Enter new Registration Date (YYYY-MM-DD): ";
    cin >> newDate;
    cout << "Enter payment amount in Rs: ";
    cin >> payment;

    auto it = regSystem.getVehicleDatabase().find(plateNumber);
    if (it != regSystem.getVehicleDatabase().end()) {
        cout << "\nCurrent details before renewal:\n";
        it->second.displayDetails();

        // Simulate payment processing
        cout << "Processing payment of Rs " << payment << "...\n";
        cout << "Payment successful.\n";

        VehicleDetails updatedDetails = it->second;
        updatedDetails.updateRegistrationDate(newDate);

        // Update the database
        auto updatedDatabase = regSystem.getVehicleDatabase();
        updatedDatabase[plateNumber] = updatedDetails;
        regSystem.setVehicleDatabase(updatedDatabase);

        cout << "\nDetails after renewal:\n";
        updatedDetails.displayDetails();

        regSystem.saveToFile(); // Save the updated database to the file in binary mode
        cout << "Vehicle registration date updated successfully.\n";
    } else {
        cout << "Vehicle not found.\n";
    }
}

