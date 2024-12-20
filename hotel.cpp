#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Global variables to store file names
const string GuestDetailsFile = "Guest Details File.txt"; 
const string roomsAvailble = "rooms available.txt";  


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
    void addClient();                                                // Function to add a new client
    void checkRoomAvailability();                                    // Function to check room availability
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
    vector<GuestDetails> guestDetails; // Vector to hold guest details
    GuestDetails g;                    // Temporary variable for guest details

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

      
        switch (roomChoice)
        {
        case 1:
            luxurySuite -= 1; // Decrease luxury suite count
            g.roomQuality = "Luxury Suite";
            break;
        case 2:
            deluxeRooms -= 1; // Decrease deluxe room count
            g.roomQuality = "Deluxe Rooms";
            break;
        case 3:
            standardRooms -= 1; // Decrease standard room count
            g.roomQuality = "Standard Rooms";
            break;
        case 4:
            economyRooms -= 1; // Decrease economy room count
            g.roomQuality = "Economy Rooms";
            break;
        default:
            cout << "Wrong input"; // Handle invalid input
            break;
        }
    } while (!(roomChoice <= 4 && roomChoice > 0)); // Repeat until valid input

    // Get guest details
    cout << "Enter your name: ";
    cin.ignore();              // Clear input buffer
    getline(cin, g.guestName); 

    cout << "Enter your phone number: ";
    getline(cin, g.phoneNo);

    cout << "Enter your address: ";
    getline(cin, g.guestAddress);

    cout << "Days to stay: ";
    cin >> g.days; 
}

// Function to save guest details to a file
void Hotel::saveGuestDetails(const vector<GuestDetails> &guestDetails)
{
    ofstream file(GuestDetailsFile); 
    // Code to write guest details will be added later
}

int main()
{
    // Display the system title and start the main menu
    cout << "GIOVANNA'S HOTEL MANAGEMENT SYSTEM" << endl;
    mainMenu();

    return 0;
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
