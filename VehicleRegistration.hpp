
#ifndef VEHICLEREGISTRATIONSYSTEM_HPP
#define VEHICLEREGISTRATIONSYSTEM_HPP

#include <string>
#include <unordered_map>

class VehicleDetails {
public:
    std::string registrationNumber;
    std::string ownerName;
    std::string vehicleMake;
    std::string vehicleModel;
    std::string vehicleYear;
    std::string VIN; // Vehicle Identification Number
    std::string registrationDate;

    void inputDetails();
    void displayDetails() const;
    void writeToBinaryFile(std::ofstream &out) const;
    void readFromBinaryFile(std::ifstream &in);
    void updateRegistrationDate(const std::string &newDate);
};

class VehicleRegistrationSystem {
private:
    std::unordered_map<std::string, VehicleDetails> vehicleDatabase;
    std::string databaseFilename;

public:
    VehicleRegistrationSystem(const std::string &filename);
    void registerVehicle();
    void searchVehicleByPlateNumber() const;
    void loadFromFile();
    void saveToFile() const;

    const std::unordered_map<std::string, VehicleDetails>& getVehicleDatabase() const;
    void setVehicleDatabase(const std::unordered_map<std::string, VehicleDetails>& db);
};

class BlueBookRenewalSystem {
private:
    VehicleRegistrationSystem &regSystem;

public:
    BlueBookRenewalSystem(VehicleRegistrationSystem &regSystem);
    void renewVehicle();
};

std::string generateRandomPlateNumber();

#endif // VEHICLEREGISTRATIONSYSTEM_HPP
