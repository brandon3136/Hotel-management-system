#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Global variables to store file names
const string GuestDetailsFile = "Guest Details File.txt";
const string roomsAvailable = "rooms available.txt";
const string adminCredentialsFile = "Admin credentials.txt";

// Structure to hold guest details
struct GuestDetails
{
    string guestName;
    string guestAddress;
    string phoneNo;
    string roomQuality;
    string roomNumber;
    string password;
    int days;
};

struct AdminCredentials
{
    string newAdminUsername;
    string newAdminPassword;
    bool update = false;
};

// Hotel class to manage hotel operations
class Hotel
{
    // Room availability counters
    int luxurySuite = 20;
    int deluxeRooms = 30;
    int standardRooms = 40;
    int economyRooms = 10;

private:
    const string adminUsername = "admin";
    const string adminPassword = "admin";

public:
    // Functions to manage hotel operations
    void addClient();                            // Function to add a new client
    bool checkRoomAvailability(int roomQuality); // Function to check room availability
    vector<int> loadRoomAvailable();
    void saveRoomAvailable(const vector<int> &roomsRemains);
    void saveGuestDetails(const vector<GuestDetails> &guestDetails); // Save guest details to a file
    vector<GuestDetails> loadGuestDetails();                         // Load guest details from a file
    void displayGuestDetails();
    void guest();
    void guestMenu(const GuestDetails &g);
    void dispalyOneGuestDetails(const GuestDetails &g);
    int billing(string roomQuality, int days);
    int orderFood();
    void receipt(const GuestDetails &g);
    void deleteGuest();
    void adminLogin();
    void adminMenu();
    AdminCredentials loadAdminCredentials();
    void saveAdminCredentials(const AdminCredentials &a);
    void updateAdminCredentials();
    void displayAdminCredentials();
    void displayRoomsAvailable();
};

// Global object for Hotel class
Hotel hotel;

// Function declarations
void mainMenu();
void hotelDetails();
void displayBookedRooms();

void Hotel::displayRoomsAvailable(){
    vector<int> roomsRemain = loadRoomAvailable();
    if (roomsRemain.empty())
    {
        roomsRemain.push_back(luxurySuite);
        roomsRemain.push_back(deluxeRooms);
        roomsRemain.push_back(standardRooms);
        roomsRemain.push_back(economyRooms);
        saveRoomAvailable(roomsRemain);
    }
    cout << "----- Rooms Available -----" << endl;
    cout << "1. Luxury Suites :" << roomsRemain.at(0)  << endl;
    cout << "2. Deluxe Rooms :" << roomsRemain.at(1) << endl;
    cout << "3. Standard Rooms :" << roomsRemain.at(2) << endl;
    cout << "4. Economy Rooms :" << roomsRemain.at(3) << endl;
}

void Hotel::displayAdminCredentials()
{
    AdminCredentials a = loadAdminCredentials();
    if (!a.update)
    {
        cout << "username: " << adminUsername << endl;
        cout << "Password: " << adminPassword << endl;
    }
    else
    {
        cout << "username: " << a.newAdminUsername << endl;
        cout << "password: " << a.newAdminPassword << endl;
    }
}

void Hotel::updateAdminCredentials()
{
    AdminCredentials a;
    string password;
    string confirm;
    cout << "\n------ Updating Admin Credentials -------" << endl;
    cout << "Enter the User name: ";
    cin.ignore();
    getline(cin, a.newAdminUsername);

    while (true)
    {
        cout << "Enter the password: ";
        getline(cin, password);

        cout << "Confirm the password: ";
        getline(cin, confirm);

        if (confirm == password)
        {
            a.newAdminPassword = confirm;
            break;
        }
        else
        {
            cout << "\nWrong Password\n"
                 << endl;
        }
    }
    a.update = true;

    saveAdminCredentials(a);
    cout << "Update successfull" << endl;
}

AdminCredentials Hotel::loadAdminCredentials()
{
    AdminCredentials a;
    ifstream file(adminCredentialsFile);
    if (file.is_open())
    {
        while (file >> a.newAdminUsername)
        {
            file >> a.newAdminPassword;
            file >> a.update;
        }
    }
    file.close();
    return a;
}

void Hotel::saveAdminCredentials(const AdminCredentials &a)
{
    ofstream file(adminCredentialsFile, ios::trunc);
    if (file.is_open())
    {
        file << a.newAdminUsername << endl;
        file << a.newAdminPassword << endl;
        file << a.update;
    }
    else
    {
        cout << "File is not opened" << endl;
    }
    file.close();
}
void Hotel::adminMenu()
{
    AdminCredentials a = loadAdminCredentials();
    int choice = 0;
    if (!a.update)
    {
        cout << "\n Hello " << adminUsername;
    }
    else
    {
        cout << "\n Hello " << a.newAdminUsername;
    }

    do
    {
        cout << "\n------ Admin Menu -------" << endl;
        cout << "1. View guests' details" << endl;
        cout << "2. Delete a guest" << endl;
        cout << "3. Update your credentials" << endl;
        cout << "4. View your credentials" << endl;
        cout << "5. Display rooms available" << endl;

        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            hotel.displayGuestDetails();
            break;
        case 2:
            hotel.deleteGuest();
            break;
        case 3:
            updateAdminCredentials();
            break;
        case 4:
            displayAdminCredentials();
            break;
        case 5:
            displayRoomsAvailable();
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Wrong Input!" << endl;
            break;
        }

    } while (choice != 6);
}

void Hotel::adminLogin()
{
    string username, password;
    AdminCredentials a = loadAdminCredentials();
    cout << "\n--- Admin Login ---\n";

    while (true)
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (!a.update)
        {
            if (username == adminUsername && password == adminPassword)
            {
                cout << "\nLogin successful!\n";
                break;
            }
            else
            {
                cout << "\nInvalid credentials. Access denied.\n";
            }
        }
        else
        {
            if (username == a.newAdminUsername && password == a.newAdminPassword)
            {
                cout << "\nLogin successful!\n";
                break;
            }
            else
            {
                cout << "\nInvalid credentials. Access denied.\n";
            }
        }
    }
    adminMenu();
}

void Hotel::deleteGuest()
{
    vector<GuestDetails> guestDetails = loadGuestDetails();
    vector<int> roomsRemain = loadRoomAvailable();
    string rN;
    bool found = false;

    if (guestDetails.empty())
    {
        cout << "Guest data not found!, unable to delete guests' details" << endl;
    }
    else
    {
        cout << "Enter the Guest's room number to delete: ";
        cin >> rN;
        for (auto i = guestDetails.begin(); i != guestDetails.end(); i++)
        {
            if (i->roomNumber == rN)
            {
                if (i->roomQuality == "Luxury Suite"){
                    roomsRemain.at(0) += 1;
                }
                else if (i->roomQuality == "Deluxe Rooms"){
                    roomsRemain.at(1) += 1;
                }
                else if (i->roomQuality == "Standard Rooms"){
                    roomsRemain.at(2) += 1;
                }
                else if (i->roomQuality == "Economy Rooms"){
                    roomsRemain.at(3) += 1;
                }
                found = true;
                guestDetails.erase(i);
                saveRoomAvailable(roomsRemain);
                saveGuestDetails(guestDetails);
                cout << "The guest has been deleted successfully\n"
                     << endl;
            }
        }
        if (!found)
        {
            cout << "The guest is not found!"
                 << endl;
        }
    }
}

void Hotel::receipt(const GuestDetails &g)
{
    int bill = billing(g.roomQuality, g.days);
    cout << "\n\t------ RECEIPT ------" << endl;
    cout << "\tGiovanna's Luxury Inn" << endl;
    cout << "Name of the client: " << g.guestName << endl;
    cout << "Address of the client: " << g.guestAddress << endl;
    cout << "Phone No. of the client: " << g.phoneNo << endl;
    cout << "Room number of the client: " << g.roomNumber << endl;
    cout << "Room quality of the client: " << g.roomQuality << endl;
    cout << "Days to stay: " << g.days << endl;
    cout << "Price to stay: $" << bill << endl
         << endl;
    cout << "\t------ End Of Receipt -------" << endl;
    cout << "\t------ Thank you -------" << endl
         << endl;
}

void Hotel::guestMenu(const GuestDetails &g)
{
    cout << "\n\nHello, " << g.guestName << endl;
    int choice = 0;
    int bill;
    do
    {
        cout << "------- Guest Menu ------" << endl;
        cout << "1. Display your room details" << endl;
        cout << "2. Billing details" << endl;
        cout << "3. Order food" << endl;
        cout << "4. View receipt" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            dispalyOneGuestDetails(g);
            break;
        case 2:
            cout << "The total bill for the stay: $" << billing(g.roomQuality, g.days) << endl;
            break;
        case 3:
            bill = orderFood();
            break;
        case 4:
            receipt(g);
            break;
        default:
            cout << "Wrong Input";
            break;
        }
    } while (choice != 5);
}

int Hotel::orderFood()
{
    int choice = 0;
    string food;
    int billOfFood;
    cout << "\n Welcome to Giovanna's Restaurant" << endl;
    cout << "Order food here...\n"
         << endl;

    cout << "1. Burger (@$40)" << endl;
    cout << "2. Pizza (@$80)" << endl;
    cout << "3. Hamburger (@$45)" << endl;
    cout << "4. Rice (@$60)" << endl;
    cout << "5. Ugali (@30)" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        food = "Burger";
        billOfFood = 40;
        break;
    case 2:
        food = "Pizza";
        billOfFood = 80;
        break;
    case 3:
        food = "Hamburger";
        billOfFood = 45;
        break;
    case 4:
        food = "Rice";
        billOfFood = 60;
        break;
    case 5:
        food = "Ugali";
        billOfFood = 30;
        break;
    default:
        cout << "Wrong input" << endl;
    }

    cout << "Ok," << food << " done ordered" << endl;

    return billOfFood;
}

void Hotel::dispalyOneGuestDetails(const GuestDetails &g)
{
    cout << "\nInfo details about, " << g.guestName << endl
         << endl;
    cout << "Guest name: " << g.guestName << endl;
    cout << "Room Number: " << g.roomNumber << endl;
    cout << "Room Quality: " << g.roomQuality << endl;
    cout << "Days to stay: " << g.days << endl;
    cout << "Address: " << g.guestAddress << endl;
    cout << "Phone No.: " << g.phoneNo << endl
         << endl;
}

void Hotel::guest()
{
    vector<GuestDetails> guestDetails = loadGuestDetails();
    string guestId;
    bool found = false;

    cout << "Your name or room number: ";
    cin.ignore();
    getline(cin, guestId);
    string password;
    int count = 3;

    for (auto &g : guestDetails)
    {
        if ((guestId == g.guestName) || (guestId == g.roomNumber))
        {
            found = true;
            while (count)
            {
                cout << "Enter your password: ";
                getline(cin, password);

                if (password == g.password)
                {
                    guestMenu(g);
                    break;
                }
                else
                {
                    cout << "Enter the password again " << count << " left" << endl;
                    count -= 1;
                }
            }
        }
    }
    if (!found)
    {
        cout << "That room number or name has not been found!!" << endl;
    }
}
int Hotel::billing(string roomQuality, int days)
{
    int bill = 0;
    if (roomQuality == "Luxury Suite")
    {
        bill = 1000 * days;
    }
    else if (roomQuality == "Deluxe Rooms")
    {
        bill = 800 * days;
    }
    else if (roomQuality == "Standard Rooms")
    {
        bill = 600 * days;
    }
    else if (roomQuality == "Economy Rooms")
    {
        bill = 400 * days;
    }

    return bill;
}

void Hotel::displayGuestDetails()
{
    vector<GuestDetails> guestDetails = loadGuestDetails();
    int count = 1;

    if (!guestDetails.empty())
    {
        cout << "\n\t\t\t\t-------- Guest Details --------" << endl;
        cout << left << setw(5) << "No."
             << setw(20) << "Guest Name"
             << setw(15) << "Guest Address"
             << setw(15) << "Phone No."
             << setw(15) << "Room Quality"
             << setw(15) << "Room Number"
             << setw(5) << "Days" << endl;
        for (const auto &g : guestDetails)
        {
            cout << left << setw(5) << count
                 << setw(20) << g.guestName
                 << setw(15) << g.guestAddress
                 << setw(15) << g.phoneNo
                 << setw(15) << g.roomQuality
                 << setw(15) << g.roomNumber
                 << setw(5) << g.days << endl;

            count += 1;
        }
    }
    else
    {
        cout << "\nNo guest details found!!" << endl;
    }
}
// Function to add a new client
void Hotel::addClient()
{
    vector<GuestDetails> guestDetails = loadGuestDetails(); // Vector to hold guest details
    GuestDetails g;                                         // Temporary variable for guest details
    vector<int> roomsRemain = loadRoomAvailable();
    bool available;

    if (roomsRemain.empty())
    {
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
        cout << "1. Luxury Suites (" << roomsRemain.at(0) << ")" << endl;
        cout << "2. Deluxe Rooms (" << roomsRemain.at(1) << ")" << endl;
        cout << "3. Standard Rooms (" << roomsRemain.at(2) << ")" << endl;
        cout << "4. Economy Rooms (" << roomsRemain.at(3) << ")" << endl;
        cout << "5. Go to main menu\n"
             << endl;

        cout << "Enter your choice(1-4): ";
        cin >> roomChoice;
        cin.ignore();

        switch (roomChoice)
        {
        case 1:
            if (checkRoomAvailability(0))
            {
                roomsRemain.at(roomChoice - 1) = roomsRemain[roomChoice - 1] - 1;
                g.roomQuality = "Luxury Suite";
                g.roomNumber = "L" + to_string(roomsRemain.at(roomChoice - 1));
            }
            break;
        case 2:
            if (checkRoomAvailability(1))
            {
                roomsRemain.at(roomChoice - 1) = roomsRemain[roomChoice - 1] - 1;
                g.roomQuality = "Deluxe Rooms";
                g.roomNumber = "D" + to_string(roomsRemain.at(roomChoice - 1));
            }
            break;
        case 3:
            if (checkRoomAvailability(2))
            {
                roomsRemain.at(roomChoice - 1) = roomsRemain[roomChoice - 1] - 1;
                g.roomQuality = "Standard Rooms";
                g.roomNumber = "S" + to_string(roomsRemain.at(roomChoice - 1));
            }
            break;
        case 4:
            if (checkRoomAvailability(3))
            {
                roomsRemain.at(roomChoice - 1) = roomsRemain[roomChoice - 1] - 1;
                g.roomQuality = "Economy Rooms";
                g.roomNumber = "E" + to_string(roomsRemain.at(roomChoice - 1));
            }
            break;
        case 5:
            cout << "Exiting to main menu..." << endl;
            break;
        default:
            cout << "Wrong input" << endl; // Handle invalid input
            break;
        }
    } while (!(roomChoice <= 5 && roomChoice > 0)); // Repeat until valid input

    if (roomChoice != 5)
    {
        saveRoomAvailable(roomsRemain);

        // Get guest details
        cout << "Enter your name: ";
        getline(cin, g.guestName);

        string confirm;
        cout << "Enter your password: ";
        getline(cin, g.password);
        while (true)
        {
            cout << "Confirm your password: ";
            getline(cin, confirm);

            if (g.password == confirm)
            {
                break;
            }
            else
            {
                cout << "Wrong Password!!!" << endl;
            }
        }

        cout << "Enter your phone number: ";
        getline(cin, g.phoneNo);

        cout << "Enter your address: ";
        getline(cin, g.guestAddress);

        cout << "Days to stay: ";
        cin >> g.days;
        guestDetails.push_back(g);

        saveGuestDetails(guestDetails);

        receipt(g);
    }
}

// Function to save guest details to a file
void Hotel::saveGuestDetails(const vector<GuestDetails> &guestDetails)
{

    ofstream file(GuestDetailsFile, ios::trunc); // Overwrite file with all current records
    if (file.is_open())
    {
        for (const auto &g : guestDetails)
        {
            file << g.guestName << endl;
            file << g.password << endl;
            file << g.guestAddress << endl;
            file << g.phoneNo << endl;
            file << g.roomQuality << endl;
            file << g.roomNumber << endl;
            file << g.days << endl;
            file << "----------" << endl; // Delimiter between guest records
        }
        file.close();
    }
}

vector<GuestDetails> Hotel::loadGuestDetails()
{
    ifstream file(GuestDetailsFile);
    vector<GuestDetails> guestDetails;

    if (file.is_open())
    {
        GuestDetails g;
        string line;

        while (getline(file, line))
        {
            if (line == "----------")
            {
                guestDetails.push_back(g);
                g = GuestDetails();
                continue;
            }

            if (g.guestName.empty())
                g.guestName = line;
            else if (g.password.empty())
                g.password = line;
            else if (g.guestAddress.empty())
                g.guestAddress = line;
            else if (g.phoneNo.empty())
                g.phoneNo = line;
            else if (g.roomQuality.empty())
                g.roomQuality = line;
            else if (g.roomNumber.empty())
                g.roomNumber = line;
            else
                g.days = stoi(line); // Convert string to int
        }

        file.close();
    }
    return guestDetails;
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
    if ((roomsRemain[roomQuality] - 1) > 0)
    {
        return true;
    }
    else
    {
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

    return roomsRemain;
}

void Hotel::saveRoomAvailable(const vector<int> &roomsRemain)
{
    ofstream file(roomsAvailable, ios::trunc);
    if (file.is_open())
    {
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
    cout << "\tLarge rooms with premium features like king-sized beds, private balconies, and spa access.\n\t Price: $1000 per night\n"
         << endl;
    cout << "Deluxe Rooms(30 rooms)" << endl;
    cout << "\tHigh-end rooms with free WiFi, pool views, and upgraded furnishings.\n\t Price: $800 per night\n"
         << endl;
    cout << "Standard Rooms(40 rooms)" << endl;
    cout << "\tComfortable rooms with essential amenities like free WiFi and quality furnishings.\n\t Price: $600 per night\n"
         << endl;
    cout << "Economy Rooms(10 rooms)." << endl;
    cout << "\tAffordable rooms with basic features, targeting budget travelers.\n\t Price: $400 per night\n"
         << endl;
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
        cout << "3. Guest login" << endl;
        cout << "4. Admin login" << endl;
        cout << "5. Exit" << endl;

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
            hotel.guest();
            break;
        case 4:
            hotel.adminLogin();
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Wrong Input!" << endl;
            break;
        }

    } while (choice != 5); // Repeat until the user chooses to exit
}
