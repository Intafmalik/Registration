// #include <iostream>
// #include "OnlineForm.h"
// #include <fstream>
// #include <regex>
// #include <limits>
// #include <cstdlib>

#include <iostream>
#include "OnlineForm.h"
#include "VehicleRegistration.hpp"
#include <fstream>
#include <regex>
#include <limits> // For std::numeric_limits
#include <cstdlib>
#include <iomanip>

using namespace std;

void options()
{
    cout << "Enter 1 for  registration: " << endl
         << "Enter 2 for LISCENSE exam: " << endl
         << "Enter 3 for Vehicle Registration: " << endl
         << "Enter 4 for BlueBook Renew: " << endl
         << "Enter 5 Exit:  " << endl;
}

int main()
{
    int userInput = 0;

    VehicleRegistrationSystem regSystem("vehicle_database.bin");
    BlueBookRenewalSystem blueBookRenewalSystem(regSystem);

    while (true)
    {
        options();
        cout << setfill(' ');
        cout << setw(15) << "Enter your choice: ";
        cin >> userInput;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number.\n";
            continue;
        }

        switch (userInput)
        {
        case 1:
        {
            OnlineForm o1;
            o1.display();
            o1.saveToFile();
            o1.loadFromFile();
            break;
        }

        case 2:
        {
        }
        case 3:
        {
            srand(time(0));
            int choice;

            while (true)
            {
                cout << "\n\n";
                cout << "1. Register Vehicle\n";
                cout << "2. Search Vehicle by Plate Number\n";
                cout << "3. Return to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;

                // Handle invalid input in the inner loop
                if (cin.fail())
                {
                    cin.clear();                                         // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input, please enter a number.\n";
                    continue; // Skip to the next iteration of the loop
                }

                switch (choice)
                {
                case 1:
                {
                    int result = system("clear"); // Use "cls" for Windows
                    if (result == -1)
                    {
                        cerr << "Error clearing the screen" << endl;
                    }
                    regSystem.registerVehicle();
                    break;
                }
                case 2:
                {
                    int result = system("clear"); // Use "cls" for Windows
                    if (result == -1)
                    {
                        cerr << "Error clearing the screen" << endl;
                    }
                    regSystem.searchVehicleByPlateNumber();
                    break;
                }
                case 3:
                    goto main_menu;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            }
        main_menu:
            break;
        }

        case 4:
        {
            int result = system("clear"); // Use "cls" for Windows
            if (result == -1)
            {
                cerr << "Error clearing the screen" << endl;
            }
            blueBookRenewalSystem.renewVehicle();
            break;
        }
        case 5:
        {
            cout << "Exiting...\n";
            return 0;
        }
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        exit(0);
    }

    return 0;
}