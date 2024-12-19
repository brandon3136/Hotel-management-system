#include <iostream>
#include <vector>
#include <string>

using namespace std;


//global variables

const string GuestDetailsFile = "Guest Details File";

struct GuestDetails
{
    string guestName;
    string guestAddress;
    string phoneNo;
    string roomQuality;
    string roomNumber;
    int days;
};

class Hotel{

    int luxurySuite = 20;
    int deluxeRooms = 30;
    int standardRooms = 40;
    int economyRooms = 10;

    public:
        void addClient();
        void checkRoomAvailability();
        vector<GuestDetails> loadGuestDetails();
};
//global object variable
Hotel hotel;

void Hotel::addClient(){

    vector<GuestDetails> guestDetails;
    GuestDetails g;

    int roomChoice = 0;
    do
    {
        cout << "-----Booking a Room -----\n"
             << endl;
        cout << "1. Luxury Suites" << endl;
        cout << "2. Deluxe Rooms" << endl;
        cout << "3. Standard Rooms" << endl;
        cout << "4. Economy Rooms" << endl;
        cout << "5. Go to main menu\n"
             << endl;

        cout << "Enter your choice(1-4): ";
        cin >> roomChoice;

        switch (roomChoice)
        {
            case 1:
                luxurySuite -= 1;
                g.roomQuality = "Luxury Suite";
                break;
            case 2:
                deluxeRooms -= 1;
                g.roomQuality = "Deluxe Rooms";
                break;
            case 3:
                standardRooms -= 1;
                g.roomQuality = "Standard Rooms";
                break;
            case 4:
                economyRooms -= 1;
                g.roomQuality = "Economy Rooms";
                break;
            default:
                cout << "Wrong input";
                break;
        }
    } while (roomChoice != 5);

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, g.guestName);

    cout << "Enter your phone number: ";
    getline(cin, g.phoneNo);

    cout << "Enter your address: ";
    getline(cin, g.guestAddress);

    cout << "Days to stay: ";
    cin >> g.days;
}



int main()
{
    cout << "GIOVANNA'S HOTEL MANAGEMENT SYSTEM" << endl;
    mainMenu();

    return 0;
}

void hotelDetails()
{
    cout << "\n----- HOTEL DETAILS -----" << endl;
    cout << "Hotel Name: Giovanna's Luxury Inn" << endl;
    cout << "Location: Gwen Cold" << endl;
    cout << "Facilities: Free WiFi, Swimming Pool, Restaurant" << endl;
    cout << "Contact: +255-789-567-980" << endl;

    cout << "\n\n\t\tNumber of Rooms: 100" << endl;
    cout << "Luxury Suites (20 rooms)" <<endl;
    cout << "\tLarge rooms with premium features like king-sized beds, private balconies, and spa access." << endl;
    cout << "Deluxe Rooms(30 rooms)" << endl;
    cout << "\t High-end rooms with free WiFi, pool views, and upgraded furnishings." << endl;
    cout << "Standard Rooms(40 rooms)" << endl;
    cout << "\t Comfortable rooms with essential amenities like free WiFi and quality furnishings." << endl;
    cout << "Economy Rooms(10 rooms)." << endl;
    cout << "\tAffordable rooms with basic features, targeting budget travelers." << endl;
    cout << "---------------------------------" << endl;
}



void displayBookedRooms()
{
    
}


void mainMenu(){
    int choice = 0;

    do
    {
        cout << "\n------ MAIN MENU ------" << endl;
        cout << "1. Hotel's details" << endl;
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
            hotel.addClient();
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
}