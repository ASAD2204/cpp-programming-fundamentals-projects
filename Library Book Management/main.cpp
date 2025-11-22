#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

const int MAX_BOOKS = 200;
const string FILENAME = "library_books.txt";

struct Book {
    int bookId;
    string title;
    string author;
    string isbn;
    int quantity;
    int availableQty;
    string category;
    bool isIssued;
    string issuedTo;
    string issueDate;
};

// Function prototypes
void displayMenu();
void addBook(Book books[], int &count);
void viewAllBooks(Book books[], int count);
void searchBook(Book books[], int count);
void issueBook(Book books[], int count);
void returnBook(Book books[], int count);
void viewAvailableBooks(Book books[], int count);
void viewIssuedBooks(Book books[], int count);
void updateBookQuantity(Book books[], int count);
void deleteBook(Book books[], int &count);
void searchByCategory(Book books[], int count);
void saveToFile(Book books[], int count);
void loadFromFile(Book books[], int &count);
string getCurrentDate();

int main() {
    Book books[MAX_BOOKS];
    int bookCount = 0;
    int choice;
    
    // Load existing data from file
    loadFromFile(books, bookCount);
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                addBook(books, bookCount);
                break;
            case 2:
                viewAllBooks(books, bookCount);
                break;
            case 3:
                searchBook(books, bookCount);
                break;
            case 4:
                issueBook(books, bookCount);
                break;
            case 5:
                returnBook(books, bookCount);
                break;
            case 6:
                viewAvailableBooks(books, bookCount);
                break;
            case 7:
                viewIssuedBooks(books, bookCount);
                break;
            case 8:
                searchByCategory(books, bookCount);
                break;
            case 9:
                updateBookQuantity(books, bookCount);
                break;
            case 10:
                deleteBook(books, bookCount);
                break;
            case 11:
                saveToFile(books, bookCount);
                cout << "Data saved successfully!" << endl;
                break;
            case 12:
                saveToFile(books, bookCount);
                cout << "Exiting program. Data saved!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
        if(choice != 12) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while(choice != 12);
    
    return 0;
}

void displayMenu() {
    system("cls");
    cout << "\n================================================" << endl;
    cout << "      LIBRARY BOOK MANAGEMENT SYSTEM" << endl;
    cout << "================================================" << endl;
    cout << "1.  Add New Book" << endl;
    cout << "2.  View All Books" << endl;
    cout << "3.  Search Book by ID/Title" << endl;
    cout << "4.  Issue Book" << endl;
    cout << "5.  Return Book" << endl;
    cout << "6.  View Available Books" << endl;
    cout << "7.  View Issued Books" << endl;
    cout << "8.  Search by Category" << endl;
    cout << "9.  Update Book Quantity" << endl;
    cout << "10. Delete Book" << endl;
    cout << "11. Save Data to File" << endl;
    cout << "12. Exit" << endl;
    cout << "================================================" << endl;
}

void addBook(Book books[], int &count) {
    if(count >= MAX_BOOKS) {
        cout << "Error: Maximum book limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Add New Book ---" << endl;
    
    cout << "Enter Book ID: ";
    cin >> books[count].bookId;
    cin.ignore();
    
    cout << "Enter Book Title: ";
    getline(cin, books[count].title);
    
    cout << "Enter Author Name: ";
    getline(cin, books[count].author);
    
    cout << "Enter ISBN: ";
    getline(cin, books[count].isbn);
    
    cout << "Enter Category (Fiction/Non-Fiction/Science/History/etc.): ";
    getline(cin, books[count].category);
    
    cout << "Enter Total Quantity: ";
    cin >> books[count].quantity;
    
    books[count].availableQty = books[count].quantity;
    books[count].isIssued = false;
    books[count].issuedTo = "";
    books[count].issueDate = "";
    
    count++;
    cout << "\nBook added successfully!" << endl;
}

void viewAllBooks(Book books[], int count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    cout << "\n--- All Books in Library ---" << endl;
    cout << left << setw(8) << "ID" 
         << setw(30) << "Title" 
         << setw(20) << "Author" 
         << setw(15) << "Category"
         << setw(10) << "Qty" 
         << setw(12) << "Available" << endl;
    cout << string(95, '-') << endl;
    
    for(int i = 0; i < count; i++) {
        cout << left << setw(8) << books[i].bookId
             << setw(30) << books[i].title
             << setw(20) << books[i].author
             << setw(15) << books[i].category
             << setw(10) << books[i].quantity
             << setw(12) << books[i].availableQty << endl;
    }
}

void searchBook(Book books[], int count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    cout << "\n1. Search by Book ID" << endl;
    cout << "2. Search by Title" << endl;
    cout << "Enter choice: ";
    int searchChoice;
    cin >> searchChoice;
    cin.ignore();
    
    bool found = false;
    
    if(searchChoice == 1) {
        int searchId;
        cout << "Enter Book ID: ";
        cin >> searchId;
        
        for(int i = 0; i < count; i++) {
            if(books[i].bookId == searchId) {
                cout << "\n--- Book Found ---" << endl;
                cout << "Book ID: " << books[i].bookId << endl;
                cout << "Title: " << books[i].title << endl;
                cout << "Author: " << books[i].author << endl;
                cout << "ISBN: " << books[i].isbn << endl;
                cout << "Category: " << books[i].category << endl;
                cout << "Total Quantity: " << books[i].quantity << endl;
                cout << "Available: " << books[i].availableQty << endl;
                found = true;
                break;
            }
        }
    } else if(searchChoice == 2) {
        string searchTitle;
        cout << "Enter Book Title: ";
        getline(cin, searchTitle);
        
        for(int i = 0; i < count; i++) {
            if(books[i].title.find(searchTitle) != string::npos) {
                cout << "\n--- Book Found ---" << endl;
                cout << "Book ID: " << books[i].bookId << endl;
                cout << "Title: " << books[i].title << endl;
                cout << "Author: " << books[i].author << endl;
                cout << "ISBN: " << books[i].isbn << endl;
                cout << "Category: " << books[i].category << endl;
                cout << "Total Quantity: " << books[i].quantity << endl;
                cout << "Available: " << books[i].availableQty << endl;
                found = true;
            }
        }
    }
    
    if(!found) {
        cout << "\nBook not found!" << endl;
    }
}

void issueBook(Book books[], int count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    int bookId;
    cout << "\nEnter Book ID to issue: ";
    cin >> bookId;
    cin.ignore();
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(books[i].bookId == bookId) {
            if(books[i].availableQty > 0) {
                cout << "Enter Student/Member Name: ";
                getline(cin, books[i].issuedTo);
                
                books[i].issueDate = getCurrentDate();
                books[i].availableQty--;
                books[i].isIssued = true;
                
                cout << "\nBook issued successfully!" << endl;
                cout << "Issued to: " << books[i].issuedTo << endl;
                cout << "Issue Date: " << books[i].issueDate << endl;
            } else {
                cout << "\nSorry, this book is currently not available!" << endl;
            }
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nBook with ID " << bookId << " not found!" << endl;
    }
}

void returnBook(Book books[], int count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    int bookId;
    cout << "\nEnter Book ID to return: ";
    cin >> bookId;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(books[i].bookId == bookId) {
            if(books[i].availableQty < books[i].quantity) {
                books[i].availableQty++;
                cout << "\nBook returned successfully!" << endl;
                cout << "Title: " << books[i].title << endl;
                
                // Reset if all copies returned
                if(books[i].availableQty == books[i].quantity) {
                    books[i].isIssued = false;
                    books[i].issuedTo = "";
                    books[i].issueDate = "";
                }
            } else {
                cout << "\nError: All copies of this book are already in the library!" << endl;
            }
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nBook with ID " << bookId << " not found!" << endl;
    }
}

void viewAvailableBooks(Book books[], int count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    cout << "\n--- Available Books ---" << endl;
    cout << left << setw(8) << "ID" 
         << setw(30) << "Title" 
         << setw(20) << "Author" 
         << setw(15) << "Category"
         << setw(12) << "Available" << endl;
    cout << string(85, '-') << endl;
    
    bool hasAvailable = false;
    for(int i = 0; i < count; i++) {
        if(books[i].availableQty > 0) {
            cout << left << setw(8) << books[i].bookId
                 << setw(30) << books[i].title
                 << setw(20) << books[i].author
                 << setw(15) << books[i].category
                 << setw(12) << books[i].availableQty << endl;
            hasAvailable = true;
        }
    }
    
    if(!hasAvailable) {
        cout << "No books currently available!" << endl;
    }
}

void viewIssuedBooks(Book books[], int count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    cout << "\n--- Issued Books ---" << endl;
    cout << left << setw(8) << "ID" 
         << setw(30) << "Title" 
         << setw(20) << "Issued To" 
         << setw(15) << "Issue Date" << endl;
    cout << string(73, '-') << endl;
    
    bool hasIssued = false;
    for(int i = 0; i < count; i++) {
        if(books[i].isIssued && books[i].issuedTo != "") {
            cout << left << setw(8) << books[i].bookId
                 << setw(30) << books[i].title
                 << setw(20) << books[i].issuedTo
                 << setw(15) << books[i].issueDate << endl;
            hasIssued = true;
        }
    }
    
    if(!hasIssued) {
        cout << "No books currently issued!" << endl;
    }
}

void searchByCategory(Book books[], int count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    string category;
    cout << "\nEnter Category to search: ";
    getline(cin, category);
    
    cout << "\n--- Books in Category: " << category << " ---" << endl;
    cout << left << setw(8) << "ID" 
         << setw(30) << "Title" 
         << setw(20) << "Author" 
         << setw(12) << "Available" << endl;
    cout << string(70, '-') << endl;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(books[i].category.find(category) != string::npos) {
            cout << left << setw(8) << books[i].bookId
                 << setw(30) << books[i].title
                 << setw(20) << books[i].author
                 << setw(12) << books[i].availableQty << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No books found in this category!" << endl;
    }
}

void updateBookQuantity(Book books[], int count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    int bookId;
    cout << "\nEnter Book ID to update: ";
    cin >> bookId;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(books[i].bookId == bookId) {
            cout << "Current Quantity: " << books[i].quantity << endl;
            cout << "Available Quantity: " << books[i].availableQty << endl;
            
            int newQty;
            cout << "Enter New Total Quantity: ";
            cin >> newQty;
            
            int issuedBooks = books[i].quantity - books[i].availableQty;
            books[i].quantity = newQty;
            books[i].availableQty = newQty - issuedBooks;
            
            cout << "\nQuantity updated successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nBook with ID " << bookId << " not found!" << endl;
    }
}

void deleteBook(Book books[], int &count) {
    if(count == 0) {
        cout << "\nNo books found in the library!" << endl;
        return;
    }
    
    int bookId;
    cout << "\nEnter Book ID to delete: ";
    cin >> bookId;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(books[i].bookId == bookId) {
            // Shift all elements after this index
            for(int j = i; j < count - 1; j++) {
                books[j] = books[j + 1];
            }
            count--;
            cout << "\nBook deleted successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nBook with ID " << bookId << " not found!" << endl;
    }
}

void saveToFile(Book books[], int count) {
    ofstream outFile(FILENAME);
    
    if(!outFile) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }
    
    outFile << count << endl;
    for(int i = 0; i < count; i++) {
        outFile << books[i].bookId << endl;
        outFile << books[i].title << endl;
        outFile << books[i].author << endl;
        outFile << books[i].isbn << endl;
        outFile << books[i].quantity << endl;
        outFile << books[i].availableQty << endl;
        outFile << books[i].category << endl;
        outFile << books[i].isIssued << endl;
        outFile << books[i].issuedTo << endl;
        outFile << books[i].issueDate << endl;
    }
    
    outFile.close();
}

void loadFromFile(Book books[], int &count) {
    ifstream inFile(FILENAME);
    
    if(!inFile) {
        count = 0;
        return;
    }
    
    inFile >> count;
    inFile.ignore();
    
    for(int i = 0; i < count; i++) {
        inFile >> books[i].bookId;
        inFile.ignore();
        getline(inFile, books[i].title);
        getline(inFile, books[i].author);
        getline(inFile, books[i].isbn);
        inFile >> books[i].quantity;
        inFile >> books[i].availableQty;
        inFile.ignore();
        getline(inFile, books[i].category);
        inFile >> books[i].isIssued;
        inFile.ignore();
        getline(inFile, books[i].issuedTo);
        getline(inFile, books[i].issueDate);
    }
    
    inFile.close();
}

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    string date = to_string(1900 + ltm->tm_year) + "-" +
                  to_string(1 + ltm->tm_mon) + "-" +
                  to_string(ltm->tm_mday);
    return date;
}
