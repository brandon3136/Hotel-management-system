#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function prototypes
void hotelDetails();
void bookRoom();
void displayBookedRooms();

vector<string> bookedRooms;

int main()
{
    cout << "GIOVANNA'S HOTEL MANAGEMENT SYSTEM" << endl;
    int choice = 0;

    do
    {
        cout << "\n1. Hotel's details" << endl;
        cout << "2. Book a room" << endl;
        cout << "3. Display booked rooms" << endl;
        cout << "4. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            hotelDetails();
            break;
        case 2:
            bookRoom();
            break;
        case 3:
            displayBookedRooms();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Wrong Input!" << endl;
            break;
        }

    } while (choice != 4);

    return 0;
}

void hotelDetails()
{
    cout << "\n----- HOTEL DETAILS -----" << endl;
    cout << "Hotel Name: Giovanna's Luxury Inn" << endl;
    cout << "Location: Gwen COld" << endl;
    cout << "Number of Rooms: 100" << endl;
    cout << "Facilities: Free WiFi, Swimming Pool, Restaurant" << endl;
    cout << "Contact: +255-789-567-980" << endl;
    cout << "---------------------------------" << endl;
}

void bookRoom()
{
    string guestName;
    int roomNumber;

    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, guestName);

    cout << "Enter room number to book (1-100): ";
    cin >> roomNumber;

    if (roomNumber < 1 || roomNumber > 100)
    {
        cout << "Invalid room number! Please choose between 1 and 50." << endl;
        return;
    }

    string room = "Room " + to_string(roomNumber);
    for (const auto &r : bookedRooms)
    {
        if (r == room)
        {
            cout << "Sorry, " << room << " is already booked!" << endl;
            return;
        }
    }

    bookedRooms.push_back(room);
    cout << "Room " << roomNumber << " has been successfully booked for " << guestName << "!" << endl;
}

void displayBookedRooms()
{
    cout << "\n----- BOOKED ROOMS -----" << endl;

    if (bookedRooms.empty())
    {
        cout << "No rooms have been booked yet!" << endl;
    }
    else
    {
        for (const auto &room : bookedRooms)
        {
            cout << room << endl;
        }
    }
    cout << "--------------------------" << endl;
}
