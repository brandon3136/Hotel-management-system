#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Global variables to store file names
const string GuestDetailsFile = "Guest Details File.txt";
const string roomsAvailable = "rooms available.txt";

// Structure to hold guest details
struct GuestDetails
{
    string guestName;
    string guestAddress;
    string phoneNo;
    string roomQuality;
    string roomNumber;
    int days;
};

// Hotel class to manage hotel operations
class Hotel
{
    // Room availability counters
    int luxurySuite = 20;
    int deluxeRooms = 30;
    int standardRooms = 40;
    int economyRooms = 10;

public:
    // Functions to manage hotel operations
    void addClient();             // Function to add a new client
    bool checkRoomAvailability(int roomQuality); // Function to check room availability
    vector<int> loadRoomAvailable();
    void saveRoomAvailable(const vector<int> &roomsRemains);
    void saveGuestDetails(const vector<GuestDetails> &guestDetails); // Save guest details to a file
    vector<GuestDetails> loadGuestDetails();                         // Load guest details from a file
};

// Global object for Hotel class
Hotel hotel;

// Function declarations
void mainMenu();
void hotelDetails();
void displayBookedRooms();
// Function to add a new client
void Hotel::addClient()
{
    vector<GuestDetails> guestDetails = loadGuestDetails(); // Vector to hold guest details
    GuestDetails g;                    // Temporary variable for guest details
    vector<int> roomsRemain = loadRoomAvailable();
    bool available;

    if(roomsRemain.empty()){
        roomsRemain.push_back(luxurySuite);
        roomsRemain.push_back(deluxeRooms);
        roomsRemain.push_back(standardRooms);
        roomsRemain.push_back(economyRooms);
        saveRoomAvailable(roomsRemain);
    }
    int roomChoice = 0; // Variable to store room choice
    
    do
    {
        // Display room options
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
        cin.ignore();

        switch (roomChoice)
        {
        case 1:
            if(checkRoomAvailability(0)){
                luxurySuite -= 1; // Decrease luxury suite count
                g.roomQuality = "Luxury Suite";
                g.roomNumber = "L"+luxurySuite;
            }  
            break;
        case 2:
            if(checkRoomAvailability(1)){
                deluxeRooms -= 1; // Decrease deluxe room count
                g.roomQuality = "Deluxe Rooms";
                g.roomNumber = "D"+ deluxeRooms;
            }
            
            break;
        case 3:
            if (checkRoomAvailability(2)){
                standardRooms -= 1; // Decrease standard room count
                g.roomQuality = "Standard Rooms";
                g.roomNumber = "S" + standardRooms;
            }
            break;
        case 4:
            if (checkRoomAvailability(3)){
                economyRooms -= 1; // Decrease economy room count
                g.roomQuality = "Economy Rooms";
                g.roomNumber = "E" + economyRooms;
            }
            break;
        default:
            cout << "Wrong input"<<endl; // Handle invalid input
            break;
        }
    } while (!(roomChoice <= 4 && roomChoice > 0)); // Repeat until valid input
    roomsRemain.clear();
    roomsRemain.push_back(luxurySuite);
    roomsRemain.push_back(deluxeRooms);
    roomsRemain.push_back(standardRooms);
    roomsRemain.push_back(economyRooms);
    saveRoomAvailable(roomsRemain);

    // Get guest details
    cout << "Enter your name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, g.guestName);

    cout << "Enter your phone number: ";
    getline(cin, g.phoneNo);

    cout << "Enter your address: ";
    getline(cin, g.guestAddress);

    cout << "Days to stay: ";
    cin >> g.days;
    guestDetails.push_back(g);

    saveGuestDetails(guestDetails);
}

// Function to save guest details to a file
void Hotel::saveGuestDetails(const vector<GuestDetails> &guestDetails){
    ofstream file(GuestDetailsFile, ios::trunc);
    if (file.is_open()){
        for(const auto &g : guestDetails){
            file << g.guestName<<endl;
            file << g.guestAddress << endl;
            file << g.phoneNo << endl;
            file << g.roomQuality << endl;
            file << g.roomNumber << endl;
            file << g.days << endl;
        }
        file.close();
    }
}

vector<GuestDetails> Hotel::loadGuestDetails(){
    ifstream file(GuestDetailsFile);
    vector<GuestDetails> guestdetails;

    if (file.is_open()){

        GuestDetails g;
        while(getline(file, g.guestName)){
            getline(file, g.guestAddress);
            getline(file, g.phoneNo);
            getline(file, g.roomQuality);
            getline(file, g.roomNumber);
            file >> g.days;
            guestdetails.push_back(g);
        }
        file.close();
    }
    return guestdetails;
}
int main()
{
    // Display the system title and start the main menu
    cout << "GIOVANNA'S HOTEL MANAGEMENT SYSTEM" << endl;
    mainMenu();

    return 0;
}

bool Hotel::checkRoomAvailability(int roomQuality)
{
    vector<int> roomsRemain = loadRoomAvailable();
    if ((roomsRemain[roomQuality] - 1)>0){
        return true;
    }
    else{
        return false;
    }
}

vector<int> Hotel::loadRoomAvailable()
{

    vector<int> roomsRemain;
    int temp;
    ifstream file(roomsAvailable);
    if (file.is_open())
    {
        while (file >> temp)
        {
            roomsRemain.push_back(temp);
        }
        file.close();
    }
    // cout << "loading..." << endl;
    // for(const auto &r : roomsRemain){
    //     cout << r << endl;
    // }
    return roomsRemain;
}

void Hotel::saveRoomAvailable(const vector<int> &roomsRemain)
{
    ofstream file(roomsAvailable, ios::trunc);
    if (file.is_open()){
        for (const auto &r : roomsRemain)
        {
            file << r << endl;
        }
        file.close();
    }    
}
// Function to display hotel details
void hotelDetails()
{
    cout << "\n----- HOTEL DETAILS -----" << endl;
    cout << "Hotel Name: Giovanna's Luxury Inn" << endl;
    cout << "Location: Gwen Cold" << endl;
    cout << "Facilities: Free WiFi, Swimming Pool, Restaurant" << endl;
    cout << "Contact: +255-789-567-980" << endl;

    cout << "\n\n\t\tNumber of Rooms: 100" << endl;
    cout << "Luxury Suites (20 rooms)" << endl;
    cout << "\tLarge rooms with premium features like king-sized beds, private balconies, and spa access." << endl;
    cout << "Deluxe Rooms(30 rooms)" << endl;
    cout << "\tHigh-end rooms with free WiFi, pool views, and upgraded furnishings." << endl;
    cout << "Standard Rooms(40 rooms)" << endl;
    cout << "\tComfortable rooms with essential amenities like free WiFi and quality furnishings." << endl;
    cout << "Economy Rooms(10 rooms)." << endl;
    cout << "\tAffordable rooms with basic features, targeting budget travelers." << endl;
    cout << "---------------------------------" << endl;
}

// Function to display booked rooms (to be implemented)
void displayBookedRooms()
{
    // Code to display booked rooms will be added later
}

// Main menu function
void mainMenu()
{
    int choice = 0; // Variable to store user choice

    do
    {
        // Display main menu options
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
            hotelDetails(); // Display hotel details
            break;
        case 2:
            hotel.addClient(); // Book a room
            break;
        case 3:
            displayBookedRooms(); // Display booked rooms
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Wrong Input!" << endl;
            break;
        }

    } while (choice != 4); // Repeat until the user chooses to exit
}
