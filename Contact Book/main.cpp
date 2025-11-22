#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CONTACTS = 200;
const string FILENAME = "contacts.txt";

struct Contact {
    int id;
    string name;
    string phoneNumber;
    string email;
    string address;
    string category; // Family, Friends, Work, Business, Other
    bool isFavorite;
};

// Function prototypes
void displayMenu();
void addContact(Contact contacts[], int &count);
void viewAllContacts(Contact contacts[], int count);
void searchContact(Contact contacts[], int count);
void updateContact(Contact contacts[], int count);
void deleteContact(Contact contacts[], int &count);
void viewContactsByCategory(Contact contacts[], int count);
void viewFavoriteContacts(Contact contacts[], int count);
void markAsFavorite(Contact contacts[], int count);
void sortContactsByName(Contact contacts[], int count);
void exportContacts(Contact contacts[], int count);
void importContacts(Contact contacts[], int &count);
void viewContactDetails(Contact contacts[], int count);
void saveToFile(Contact contacts[], int count);
void loadFromFile(Contact contacts[], int &count);

int main() {
    Contact contacts[MAX_CONTACTS];
    int contactCount = 0;
    int choice;
    
    // Load existing data from file
    loadFromFile(contacts, contactCount);
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                addContact(contacts, contactCount);
                break;
            case 2:
                viewAllContacts(contacts, contactCount);
                break;
            case 3:
                searchContact(contacts, contactCount);
                break;
            case 4:
                updateContact(contacts, contactCount);
                break;
            case 5:
                deleteContact(contacts, contactCount);
                break;
            case 6:
                viewContactsByCategory(contacts, contactCount);
                break;
            case 7:
                viewFavoriteContacts(contacts, contactCount);
                break;
            case 8:
                markAsFavorite(contacts, contactCount);
                break;
            case 9:
                sortContactsByName(contacts, contactCount);
                break;
            case 10:
                viewContactDetails(contacts, contactCount);
                break;
            case 11:
                exportContacts(contacts, contactCount);
                break;
            case 12:
                saveToFile(contacts, contactCount);
                cout << "Data saved successfully!" << endl;
                break;
            case 13:
                saveToFile(contacts, contactCount);
                cout << "Exiting Contact Book. Data saved!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
        if(choice != 13) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while(choice != 13);
    
    return 0;
}

void displayMenu() {
    system("cls");
    cout << "\n================================================" << endl;
    cout << "            CONTACT BOOK MANAGER" << endl;
    cout << "================================================" << endl;
    cout << "1.  Add New Contact" << endl;
    cout << "2.  View All Contacts" << endl;
    cout << "3.  Search Contact" << endl;
    cout << "4.  Update Contact" << endl;
    cout << "5.  Delete Contact" << endl;
    cout << "6.  View by Category" << endl;
    cout << "7.  View Favorite Contacts" << endl;
    cout << "8.  Mark/Unmark as Favorite" << endl;
    cout << "9.  Sort Contacts by Name" << endl;
    cout << "10. View Contact Details" << endl;
    cout << "11. Export Contacts to File" << endl;
    cout << "12. Save Data" << endl;
    cout << "13. Exit" << endl;
    cout << "================================================" << endl;
}

void addContact(Contact contacts[], int &count) {
    if(count >= MAX_CONTACTS) {
        cout << "Error: Maximum contact limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Add New Contact ---" << endl;
    
    contacts[count].id = count + 1;
    
    cout << "Enter Name: ";
    getline(cin, contacts[count].name);
    
    cout << "Enter Phone Number: ";
    getline(cin, contacts[count].phoneNumber);
    
    // Check for duplicate phone number
    for(int i = 0; i < count; i++) {
        if(contacts[i].phoneNumber == contacts[count].phoneNumber) {
            cout << "\nWarning: This phone number already exists for " 
                 << contacts[i].name << "!" << endl;
            cout << "Continue anyway? (y/n): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if(choice != 'y' && choice != 'Y') {
                return;
            }
            break;
        }
    }
    
    cout << "Enter Email: ";
    getline(cin, contacts[count].email);
    
    cout << "Enter Address: ";
    getline(cin, contacts[count].address);
    
    cout << "Category (Family/Friends/Work/Business/Other): ";
    getline(cin, contacts[count].category);
    
    cout << "Mark as favorite? (y/n): ";
    char fav;
    cin >> fav;
    cin.ignore();
    contacts[count].isFavorite = (fav == 'y' || fav == 'Y');
    
    count++;
    cout << "\nContact added successfully! (ID: " << contacts[count-1].id << ")" << endl;
}

void viewAllContacts(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    cout << "\n--- All Contacts (" << count << ") ---" << endl;
    cout << left << setw(6) << "ID" 
         << setw(25) << "Name" 
         << setw(18) << "Phone" 
         << setw(15) << "Category"
         << setw(8) << "Favorite" << endl;
    cout << string(72, '-') << endl;
    
    for(int i = 0; i < count; i++) {
        cout << left << setw(6) << contacts[i].id
             << setw(25) << contacts[i].name
             << setw(18) << contacts[i].phoneNumber
             << setw(15) << contacts[i].category
             << setw(8) << (contacts[i].isFavorite ? "Yes" : "No") << endl;
    }
}

void searchContact(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    cout << "\n1. Search by Name" << endl;
    cout << "2. Search by Phone Number" << endl;
    cout << "3. Search by Email" << endl;
    cout << "Enter choice: ";
    int searchChoice;
    cin >> searchChoice;
    cin.ignore();
    
    string searchTerm;
    bool found = false;
    
    switch(searchChoice) {
        case 1:
            cout << "Enter name to search: ";
            getline(cin, searchTerm);
            cout << "\n--- Search Results ---" << endl;
            for(int i = 0; i < count; i++) {
                if(contacts[i].name.find(searchTerm) != string::npos) {
                    cout << "\nID: " << contacts[i].id << endl;
                    cout << "Name: " << contacts[i].name << endl;
                    cout << "Phone: " << contacts[i].phoneNumber << endl;
                    cout << "Email: " << contacts[i].email << endl;
                    cout << "Category: " << contacts[i].category << endl;
                    cout << string(40, '-') << endl;
                    found = true;
                }
            }
            break;
            
        case 2:
            cout << "Enter phone number to search: ";
            getline(cin, searchTerm);
            for(int i = 0; i < count; i++) {
                if(contacts[i].phoneNumber.find(searchTerm) != string::npos) {
                    cout << "\nContact Found:" << endl;
                    cout << "ID: " << contacts[i].id << endl;
                    cout << "Name: " << contacts[i].name << endl;
                    cout << "Phone: " << contacts[i].phoneNumber << endl;
                    cout << "Email: " << contacts[i].email << endl;
                    cout << "Address: " << contacts[i].address << endl;
                    found = true;
                }
            }
            break;
            
        case 3:
            cout << "Enter email to search: ";
            getline(cin, searchTerm);
            for(int i = 0; i < count; i++) {
                if(contacts[i].email.find(searchTerm) != string::npos) {
                    cout << "\nContact Found:" << endl;
                    cout << "Name: " << contacts[i].name << endl;
                    cout << "Phone: " << contacts[i].phoneNumber << endl;
                    cout << "Email: " << contacts[i].email << endl;
                    found = true;
                }
            }
            break;
            
        default:
            cout << "Invalid choice!" << endl;
            return;
    }
    
    if(!found) {
        cout << "No contacts found matching your search!" << endl;
    }
}

void updateContact(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Contact ID to update: ";
    cin >> id;
    cin.ignore();
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(contacts[i].id == id) {
            cout << "\n--- Current Contact Details ---" << endl;
            cout << "Name: " << contacts[i].name << endl;
            cout << "Phone: " << contacts[i].phoneNumber << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Address: " << contacts[i].address << endl;
            cout << "Category: " << contacts[i].category << endl;
            
            cout << "\n--- Enter New Details ---" << endl;
            cout << "Enter Name: ";
            getline(cin, contacts[i].name);
            
            cout << "Enter Phone Number: ";
            getline(cin, contacts[i].phoneNumber);
            
            cout << "Enter Email: ";
            getline(cin, contacts[i].email);
            
            cout << "Enter Address: ";
            getline(cin, contacts[i].address);
            
            cout << "Category: ";
            getline(cin, contacts[i].category);
            
            cout << "\nContact updated successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nContact with ID " << id << " not found!" << endl;
    }
}

void deleteContact(Contact contacts[], int &count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Contact ID to delete: ";
    cin >> id;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(contacts[i].id == id) {
            cout << "\nDeleting contact: " << contacts[i].name << endl;
            cout << "Are you sure? (y/n): ";
            char confirm;
            cin >> confirm;
            
            if(confirm == 'y' || confirm == 'Y') {
                for(int j = i; j < count - 1; j++) {
                    contacts[j] = contacts[j + 1];
                }
                count--;
                cout << "\nContact deleted successfully!" << endl;
            } else {
                cout << "\nDeletion cancelled!" << endl;
            }
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nContact with ID " << id << " not found!" << endl;
    }
}

void viewContactsByCategory(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    string category;
    cout << "\nEnter Category (Family/Friends/Work/Business/Other): ";
    getline(cin, category);
    
    cout << "\n--- Contacts in Category: " << category << " ---" << endl;
    cout << left << setw(6) << "ID" 
         << setw(25) << "Name" 
         << setw(18) << "Phone" 
         << setw(30) << "Email" << endl;
    cout << string(79, '-') << endl;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(contacts[i].category == category) {
            cout << left << setw(6) << contacts[i].id
                 << setw(25) << contacts[i].name
                 << setw(18) << contacts[i].phoneNumber
                 << setw(30) << contacts[i].email << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No contacts found in this category!" << endl;
    }
}

void viewFavoriteContacts(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    cout << "\n--- Favorite Contacts ---" << endl;
    cout << left << setw(6) << "ID" 
         << setw(25) << "Name" 
         << setw(18) << "Phone" 
         << setw(15) << "Category" << endl;
    cout << string(64, '-') << endl;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(contacts[i].isFavorite) {
            cout << left << setw(6) << contacts[i].id
                 << setw(25) << contacts[i].name
                 << setw(18) << contacts[i].phoneNumber
                 << setw(15) << contacts[i].category << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No favorite contacts!" << endl;
    }
}

void markAsFavorite(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Contact ID: ";
    cin >> id;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(contacts[i].id == id) {
            contacts[i].isFavorite = !contacts[i].isFavorite;
            cout << "\n" << contacts[i].name << " is now " 
                 << (contacts[i].isFavorite ? "marked as favorite!" : "unmarked from favorites!") 
                 << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nContact with ID " << id << " not found!" << endl;
    }
}

void sortContactsByName(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    // Bubble sort - alphabetical order
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(contacts[j].name > contacts[j + 1].name) {
                Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
    
    cout << "\nContacts sorted alphabetically!" << endl;
    viewAllContacts(contacts, count);
}

void viewContactDetails(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts found!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Contact ID: ";
    cin >> id;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(contacts[i].id == id) {
            cout << "\n========================================" << endl;
            cout << "         CONTACT DETAILS" << endl;
            cout << "========================================" << endl;
            cout << "ID:       " << contacts[i].id << endl;
            cout << "Name:     " << contacts[i].name << endl;
            cout << "Phone:    " << contacts[i].phoneNumber << endl;
            cout << "Email:    " << contacts[i].email << endl;
            cout << "Address:  " << contacts[i].address << endl;
            cout << "Category: " << contacts[i].category << endl;
            cout << "Favorite: " << (contacts[i].isFavorite ? "Yes" : "No") << endl;
            cout << "========================================" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nContact with ID " << id << " not found!" << endl;
    }
}

void exportContacts(Contact contacts[], int count) {
    if(count == 0) {
        cout << "\nNo contacts to export!" << endl;
        return;
    }
    
    string filename;
    cout << "\nEnter filename to export (e.g., backup.txt): ";
    getline(cin, filename);
    
    ofstream outFile(filename);
    
    if(!outFile) {
        cout << "Error: Unable to create export file!" << endl;
        return;
    }
    
    outFile << "========================================" << endl;
    outFile << "       CONTACT BOOK EXPORT" << endl;
    outFile << "       Total Contacts: " << count << endl;
    outFile << "========================================" << endl << endl;
    
    for(int i = 0; i < count; i++) {
        outFile << "ID: " << contacts[i].id << endl;
        outFile << "Name: " << contacts[i].name << endl;
        outFile << "Phone: " << contacts[i].phoneNumber << endl;
        outFile << "Email: " << contacts[i].email << endl;
        outFile << "Address: " << contacts[i].address << endl;
        outFile << "Category: " << contacts[i].category << endl;
        outFile << "Favorite: " << (contacts[i].isFavorite ? "Yes" : "No") << endl;
        outFile << "----------------------------------------" << endl;
    }
    
    outFile.close();
    cout << "\nContacts exported successfully to: " << filename << endl;
}

void saveToFile(Contact contacts[], int count) {
    ofstream outFile(FILENAME);
    
    if(!outFile) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }
    
    outFile << count << endl;
    for(int i = 0; i < count; i++) {
        outFile << contacts[i].id << endl;
        outFile << contacts[i].name << endl;
        outFile << contacts[i].phoneNumber << endl;
        outFile << contacts[i].email << endl;
        outFile << contacts[i].address << endl;
        outFile << contacts[i].category << endl;
        outFile << contacts[i].isFavorite << endl;
    }
    
    outFile.close();
}

void loadFromFile(Contact contacts[], int &count) {
    ifstream inFile(FILENAME);
    
    if(!inFile) {
        count = 0;
        return;
    }
    
    inFile >> count;
    inFile.ignore();
    
    for(int i = 0; i < count; i++) {
        inFile >> contacts[i].id;
        inFile.ignore();
        getline(inFile, contacts[i].name);
        getline(inFile, contacts[i].phoneNumber);
        getline(inFile, contacts[i].email);
        getline(inFile, contacts[i].address);
        getline(inFile, contacts[i].category);
        inFile >> contacts[i].isFavorite;
        inFile.ignore();
    }
    
    inFile.close();
}
