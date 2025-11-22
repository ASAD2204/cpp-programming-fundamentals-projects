#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

const int MAX_EXPENSES = 500;
const string FILENAME = "expenses.txt";

struct Expense {
    int id;
    string category; // Food, Transport, Bills, Education, Entertainment, etc.
    string description;
    double amount;
    string date;
    string paymentMethod; // Cash, Card, UPI, etc.
};

// Function prototypes
void displayMenu();
void addExpense(Expense expenses[], int &count);
void viewAllExpenses(Expense expenses[], int count);
void viewExpensesByCategory(Expense expenses[], int count);
void viewExpensesByDate(Expense expenses[], int count);
void viewExpensesByMonth(Expense expenses[], int count);
void updateExpense(Expense expenses[], int count);
void deleteExpense(Expense expenses[], int &count);
void calculateTotalExpenses(Expense expenses[], int count);
void calculateCategoryWiseTotal(Expense expenses[], int count);
void searchExpense(Expense expenses[], int count);
void viewExpensesSummary(Expense expenses[], int count);
void sortExpensesByAmount(Expense expenses[], int count);
void exportMonthlyReport(Expense expenses[], int count);
void saveToFile(Expense expenses[], int count);
void loadFromFile(Expense expenses[], int &count);
string getCurrentDate();
bool isValidDate(string date);

int main() {
    Expense expenses[MAX_EXPENSES];
    int expenseCount = 0;
    int choice;
    
    // Load existing data from file
    loadFromFile(expenses, expenseCount);
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                addExpense(expenses, expenseCount);
                break;
            case 2:
                viewAllExpenses(expenses, expenseCount);
                break;
            case 3:
                viewExpensesByCategory(expenses, expenseCount);
                break;
            case 4:
                viewExpensesByMonth(expenses, expenseCount);
                break;
            case 5:
                updateExpense(expenses, expenseCount);
                break;
            case 6:
                deleteExpense(expenses, expenseCount);
                break;
            case 7:
                calculateTotalExpenses(expenses, expenseCount);
                break;
            case 8:
                calculateCategoryWiseTotal(expenses, expenseCount);
                break;
            case 9:
                searchExpense(expenses, expenseCount);
                break;
            case 10:
                viewExpensesSummary(expenses, expenseCount);
                break;
            case 11:
                sortExpensesByAmount(expenses, expenseCount);
                break;
            case 12:
                exportMonthlyReport(expenses, expenseCount);
                break;
            case 13:
                saveToFile(expenses, expenseCount);
                cout << "Data saved successfully!" << endl;
                break;
            case 14:
                saveToFile(expenses, expenseCount);
                cout << "Exiting Expense Tracker. Data saved!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
        if(choice != 14) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while(choice != 14);
    
    return 0;
}

void displayMenu() {
    system("cls");
    cout << "\n================================================" << endl;
    cout << "           EXPENSE TRACKER SYSTEM" << endl;
    cout << "================================================" << endl;
    cout << "1.  Add New Expense" << endl;
    cout << "2.  View All Expenses" << endl;
    cout << "3.  View Expenses by Category" << endl;
    cout << "4.  View Expenses by Month" << endl;
    cout << "5.  Update Expense" << endl;
    cout << "6.  Delete Expense" << endl;
    cout << "7.  Calculate Total Expenses" << endl;
    cout << "8.  Category-wise Total" << endl;
    cout << "9.  Search Expense" << endl;
    cout << "10. View Expenses Summary" << endl;
    cout << "11. Sort Expenses by Amount" << endl;
    cout << "12. Export Monthly Report" << endl;
    cout << "13. Save Data" << endl;
    cout << "14. Exit" << endl;
    cout << "================================================" << endl;
}

void addExpense(Expense expenses[], int &count) {
    if(count >= MAX_EXPENSES) {
        cout << "Error: Maximum expense limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Add New Expense ---" << endl;
    
    expenses[count].id = count + 1;
    
    cout << "Categories: Food, Transport, Bills, Education, Entertainment, Shopping, Health, Other" << endl;
    cout << "Enter Category: ";
    getline(cin, expenses[count].category);
    
    cout << "Enter Description: ";
    getline(cin, expenses[count].description);
    
    cout << "Enter Amount: Rs. ";
    cin >> expenses[count].amount;
    cin.ignore();
    
    cout << "Enter Date (YYYY-MM-DD) or press Enter for today: ";
    getline(cin, expenses[count].date);
    
    if(expenses[count].date.empty()) {
        expenses[count].date = getCurrentDate();
    }
    
    cout << "Payment Method (Cash/Card/UPI/Other): ";
    getline(cin, expenses[count].paymentMethod);
    
    count++;
    cout << "\nExpense added successfully! (ID: " << expenses[count-1].id << ")" << endl;
}

void viewAllExpenses(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    cout << "\n--- All Expenses ---" << endl;
    cout << left << setw(6) << "ID" 
         << setw(15) << "Category" 
         << setw(25) << "Description" 
         << setw(12) << "Amount"
         << setw(15) << "Date"
         << setw(12) << "Payment" << endl;
    cout << string(85, '-') << endl;
    
    for(int i = 0; i < count; i++) {
        cout << left << setw(6) << expenses[i].id
             << setw(15) << expenses[i].category
             << setw(25) << expenses[i].description
             << "Rs. " << setw(8) << fixed << setprecision(2) << expenses[i].amount
             << setw(15) << expenses[i].date
             << setw(12) << expenses[i].paymentMethod << endl;
    }
}

void viewExpensesByCategory(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    string category;
    cout << "\nEnter Category to filter: ";
    getline(cin, category);
    
    cout << "\n--- Expenses in Category: " << category << " ---" << endl;
    cout << left << setw(6) << "ID" 
         << setw(25) << "Description" 
         << setw(12) << "Amount"
         << setw(15) << "Date" << endl;
    cout << string(58, '-') << endl;
    
    double total = 0;
    bool found = false;
    
    for(int i = 0; i < count; i++) {
        if(expenses[i].category == category) {
            cout << left << setw(6) << expenses[i].id
                 << setw(25) << expenses[i].description
                 << "Rs. " << setw(8) << fixed << setprecision(2) << expenses[i].amount
                 << setw(15) << expenses[i].date << endl;
            total += expenses[i].amount;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No expenses found in this category!" << endl;
    } else {
        cout << string(58, '-') << endl;
        cout << "Total: Rs. " << fixed << setprecision(2) << total << endl;
    }
}

void viewExpensesByMonth(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    string month;
    cout << "\nEnter Month (YYYY-MM): ";
    getline(cin, month);
    
    cout << "\n--- Expenses for " << month << " ---" << endl;
    cout << left << setw(6) << "ID" 
         << setw(15) << "Category"
         << setw(25) << "Description" 
         << setw(12) << "Amount"
         << setw(15) << "Date" << endl;
    cout << string(73, '-') << endl;
    
    double total = 0;
    bool found = false;
    
    for(int i = 0; i < count; i++) {
        if(expenses[i].date.substr(0, 7) == month) {
            cout << left << setw(6) << expenses[i].id
                 << setw(15) << expenses[i].category
                 << setw(25) << expenses[i].description
                 << "Rs. " << setw(8) << fixed << setprecision(2) << expenses[i].amount
                 << setw(15) << expenses[i].date << endl;
            total += expenses[i].amount;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No expenses found for this month!" << endl;
    } else {
        cout << string(73, '-') << endl;
        cout << "Total Monthly Expense: Rs. " << fixed << setprecision(2) << total << endl;
    }
}

void updateExpense(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Expense ID to update: ";
    cin >> id;
    cin.ignore();
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(expenses[i].id == id) {
            cout << "\n--- Current Expense Details ---" << endl;
            cout << "Category: " << expenses[i].category << endl;
            cout << "Description: " << expenses[i].description << endl;
            cout << "Amount: Rs. " << expenses[i].amount << endl;
            cout << "Date: " << expenses[i].date << endl;
            cout << "Payment: " << expenses[i].paymentMethod << endl;
            
            cout << "\n--- Enter New Details ---" << endl;
            cout << "Enter Category: ";
            getline(cin, expenses[i].category);
            
            cout << "Enter Description: ";
            getline(cin, expenses[i].description);
            
            cout << "Enter Amount: Rs. ";
            cin >> expenses[i].amount;
            cin.ignore();
            
            cout << "Enter Date (YYYY-MM-DD): ";
            getline(cin, expenses[i].date);
            
            cout << "Payment Method: ";
            getline(cin, expenses[i].paymentMethod);
            
            cout << "\nExpense updated successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nExpense with ID " << id << " not found!" << endl;
    }
}

void deleteExpense(Expense expenses[], int &count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Expense ID to delete: ";
    cin >> id;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(expenses[i].id == id) {
            for(int j = i; j < count - 1; j++) {
                expenses[j] = expenses[j + 1];
            }
            count--;
            cout << "\nExpense deleted successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nExpense with ID " << id << " not found!" << endl;
    }
}

void calculateTotalExpenses(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    double total = 0;
    for(int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }
    
    cout << "\n--- Total Expenses Summary ---" << endl;
    cout << "Total Expenses Recorded: " << count << endl;
    cout << "Total Amount Spent: Rs. " << fixed << setprecision(2) << total << endl;
    cout << "Average Expense: Rs. " << fixed << setprecision(2) << (total / count) << endl;
}

void calculateCategoryWiseTotal(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    // Array to store unique categories and their totals
    string categories[50];
    double totals[50];
    int categoryCount = 0;
    
    for(int i = 0; i < count; i++) {
        bool found = false;
        for(int j = 0; j < categoryCount; j++) {
            if(categories[j] == expenses[i].category) {
                totals[j] += expenses[i].amount;
                found = true;
                break;
            }
        }
        
        if(!found) {
            categories[categoryCount] = expenses[i].category;
            totals[categoryCount] = expenses[i].amount;
            categoryCount++;
        }
    }
    
    cout << "\n--- Category-wise Expenses ---" << endl;
    cout << left << setw(20) << "Category" 
         << setw(15) << "Total Amount"
         << setw(15) << "Percentage" << endl;
    cout << string(50, '-') << endl;
    
    double grandTotal = 0;
    for(int i = 0; i < categoryCount; i++) {
        grandTotal += totals[i];
    }
    
    for(int i = 0; i < categoryCount; i++) {
        double percentage = (totals[i] / grandTotal) * 100;
        cout << left << setw(20) << categories[i]
             << "Rs. " << setw(11) << fixed << setprecision(2) << totals[i]
             << setw(15) << fixed << setprecision(1) << percentage << "%" << endl;
    }
    
    cout << string(50, '-') << endl;
    cout << "Grand Total: Rs. " << fixed << setprecision(2) << grandTotal << endl;
}

void searchExpense(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    string keyword;
    cout << "\nEnter keyword to search in description: ";
    getline(cin, keyword);
    
    cout << "\n--- Search Results ---" << endl;
    cout << left << setw(6) << "ID" 
         << setw(15) << "Category"
         << setw(25) << "Description" 
         << setw(12) << "Amount"
         << setw(15) << "Date" << endl;
    cout << string(73, '-') << endl;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(expenses[i].description.find(keyword) != string::npos) {
            cout << left << setw(6) << expenses[i].id
                 << setw(15) << expenses[i].category
                 << setw(25) << expenses[i].description
                 << "Rs. " << setw(8) << fixed << setprecision(2) << expenses[i].amount
                 << setw(15) << expenses[i].date << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No expenses found matching the keyword!" << endl;
    }
}

void viewExpensesSummary(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    double total = 0;
    double maxExpense = expenses[0].amount;
    double minExpense = expenses[0].amount;
    string maxCategory = expenses[0].category;
    string minCategory = expenses[0].category;
    
    for(int i = 0; i < count; i++) {
        total += expenses[i].amount;
        if(expenses[i].amount > maxExpense) {
            maxExpense = expenses[i].amount;
            maxCategory = expenses[i].category;
        }
        if(expenses[i].amount < minExpense) {
            minExpense = expenses[i].amount;
            minCategory = expenses[i].category;
        }
    }
    
    cout << "\n========================================" << endl;
    cout << "        EXPENSES SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "Total Expenses: " << count << endl;
    cout << "Total Amount: Rs. " << fixed << setprecision(2) << total << endl;
    cout << "Average Expense: Rs. " << fixed << setprecision(2) << (total / count) << endl;
    cout << "\nHighest Expense: Rs. " << fixed << setprecision(2) << maxExpense 
         << " (" << maxCategory << ")" << endl;
    cout << "Lowest Expense: Rs. " << fixed << setprecision(2) << minExpense 
         << " (" << minCategory << ")" << endl;
    cout << "========================================" << endl;
}

void sortExpensesByAmount(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    cout << "\n1. Sort Highest to Lowest" << endl;
    cout << "2. Sort Lowest to Highest" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    
    // Bubble sort
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            bool swap = false;
            if(choice == 1 && expenses[j].amount < expenses[j + 1].amount) {
                swap = true;
            } else if(choice == 2 && expenses[j].amount > expenses[j + 1].amount) {
                swap = true;
            }
            
            if(swap) {
                Expense temp = expenses[j];
                expenses[j] = expenses[j + 1];
                expenses[j + 1] = temp;
            }
        }
    }
    
    cout << "\nExpenses sorted successfully!" << endl;
    viewAllExpenses(expenses, count);
}

void exportMonthlyReport(Expense expenses[], int count) {
    if(count == 0) {
        cout << "\nNo expenses found!" << endl;
        return;
    }
    
    string month;
    cout << "\nEnter Month (YYYY-MM) for report: ";
    getline(cin, month);
    
    string reportFile = "report_" + month + ".txt";
    ofstream outFile(reportFile);
    
    if(!outFile) {
        cout << "Error: Unable to create report file!" << endl;
        return;
    }
    
    outFile << "========================================" << endl;
    outFile << "    MONTHLY EXPENSE REPORT - " << month << endl;
    outFile << "========================================" << endl;
    
    double total = 0;
    int expCount = 0;
    
    for(int i = 0; i < count; i++) {
        if(expenses[i].date.substr(0, 7) == month) {
            outFile << expenses[i].date << " | " 
                    << expenses[i].category << " | "
                    << expenses[i].description << " | Rs. "
                    << fixed << setprecision(2) << expenses[i].amount << endl;
            total += expenses[i].amount;
            expCount++;
        }
    }
    
    outFile << "========================================" << endl;
    outFile << "Total Expenses: " << expCount << endl;
    outFile << "Total Amount: Rs. " << fixed << setprecision(2) << total << endl;
    outFile << "========================================" << endl;
    
    outFile.close();
    cout << "\nMonthly report exported to: " << reportFile << endl;
}

void saveToFile(Expense expenses[], int count) {
    ofstream outFile(FILENAME);
    
    if(!outFile) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }
    
    outFile << count << endl;
    for(int i = 0; i < count; i++) {
        outFile << expenses[i].id << endl;
        outFile << expenses[i].category << endl;
        outFile << expenses[i].description << endl;
        outFile << expenses[i].amount << endl;
        outFile << expenses[i].date << endl;
        outFile << expenses[i].paymentMethod << endl;
    }
    
    outFile.close();
}

void loadFromFile(Expense expenses[], int &count) {
    ifstream inFile(FILENAME);
    
    if(!inFile) {
        count = 0;
        return;
    }
    
    inFile >> count;
    inFile.ignore();
    
    for(int i = 0; i < count; i++) {
        inFile >> expenses[i].id;
        inFile.ignore();
        getline(inFile, expenses[i].category);
        getline(inFile, expenses[i].description);
        inFile >> expenses[i].amount;
        inFile.ignore();
        getline(inFile, expenses[i].date);
        getline(inFile, expenses[i].paymentMethod);
    }
    
    inFile.close();
}

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    string year = to_string(1900 + ltm->tm_year);
    string month = (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(1 + ltm->tm_mon);
    string day = (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday);
    
    return year + "-" + month + "-" + day;
}

bool isValidDate(string date) {
    return date.length() == 10 && date[4] == '-' && date[7] == '-';
}
