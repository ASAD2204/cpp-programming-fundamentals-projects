#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

const int MAX_ACCOUNTS = 100;
const string FILENAME = "bank_accounts.txt";
const string TRANS_FILE = "transactions.txt";

struct Account {
    int accountNumber;
    string accountHolder;
    string accountType; // Savings, Current, Fixed
    double balance;
    string dateOpened;
    string pin;
    bool isActive;
};

struct Transaction {
    int accountNumber;
    string type; // Deposit, Withdraw, Transfer
    double amount;
    string date;
    double balanceAfter;
};

// Function prototypes
void displayMenu();
void createAccount(Account accounts[], int &count);
void viewAllAccounts(Account accounts[], int count);
void depositMoney(Account accounts[], int count);
void withdrawMoney(Account accounts[], int count);
void transferMoney(Account accounts[], int count);
void checkBalance(Account accounts[], int count);
void viewAccountDetails(Account accounts[], int count);
void closeAccount(Account accounts[], int count);
void searchAccount(Account accounts[], int count);
void viewTransactionHistory(int accountNumber);
void calculateTotalBalance(Account accounts[], int count);
void saveAccountsToFile(Account accounts[], int count);
void loadAccountsFromFile(Account accounts[], int &count);
void saveTransaction(Transaction trans);
string getCurrentDateTime();
bool verifyPIN(Account accounts[], int count, int accNum, string pin);
int findAccountIndex(Account accounts[], int count, int accNum);

int main() {
    Account accounts[MAX_ACCOUNTS];
    int accountCount = 0;
    int choice;
    
    // Load existing data from file
    loadAccountsFromFile(accounts, accountCount);
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                createAccount(accounts, accountCount);
                break;
            case 2:
                viewAllAccounts(accounts, accountCount);
                break;
            case 3:
                depositMoney(accounts, accountCount);
                break;
            case 4:
                withdrawMoney(accounts, accountCount);
                break;
            case 5:
                transferMoney(accounts, accountCount);
                break;
            case 6:
                checkBalance(accounts, accountCount);
                break;
            case 7:
                viewAccountDetails(accounts, accountCount);
                break;
            case 8:
                closeAccount(accounts, accountCount);
                break;
            case 9:
                searchAccount(accounts, accountCount);
                break;
            case 10:
                calculateTotalBalance(accounts, accountCount);
                break;
            case 11:
                saveAccountsToFile(accounts, accountCount);
                cout << "Data saved successfully!" << endl;
                break;
            case 12:
                saveAccountsToFile(accounts, accountCount);
                cout << "Exiting Bank System. Data saved!" << endl;
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
    cout << "         BANK ACCOUNT MANAGEMENT SYSTEM" << endl;
    cout << "================================================" << endl;
    cout << "1.  Create New Account" << endl;
    cout << "2.  View All Accounts" << endl;
    cout << "3.  Deposit Money" << endl;
    cout << "4.  Withdraw Money" << endl;
    cout << "5.  Transfer Money" << endl;
    cout << "6.  Check Balance" << endl;
    cout << "7.  View Account Details" << endl;
    cout << "8.  Close Account" << endl;
    cout << "9.  Search Account" << endl;
    cout << "10. View Total Bank Balance" << endl;
    cout << "11. Save Data" << endl;
    cout << "12. Exit" << endl;
    cout << "================================================" << endl;
}

void createAccount(Account accounts[], int &count) {
    if(count >= MAX_ACCOUNTS) {
        cout << "Error: Maximum account limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Create New Account ---" << endl;
    
    cout << "Enter Account Number: ";
    cin >> accounts[count].accountNumber;
    cin.ignore();
    
    // Check if account number already exists
    for(int i = 0; i < count; i++) {
        if(accounts[i].accountNumber == accounts[count].accountNumber) {
            cout << "Error: Account number already exists!" << endl;
            return;
        }
    }
    
    cout << "Enter Account Holder Name: ";
    getline(cin, accounts[count].accountHolder);
    
    cout << "Enter Account Type (Savings/Current/Fixed): ";
    getline(cin, accounts[count].accountType);
    
    cout << "Enter Initial Deposit Amount: Rs. ";
    cin >> accounts[count].balance;
    cin.ignore();
    
    cout << "Set 4-digit PIN: ";
    getline(cin, accounts[count].pin);
    
    accounts[count].dateOpened = getCurrentDateTime();
    accounts[count].isActive = true;
    
    // Save transaction
    Transaction trans;
    trans.accountNumber = accounts[count].accountNumber;
    trans.type = "Initial Deposit";
    trans.amount = accounts[count].balance;
    trans.date = getCurrentDateTime();
    trans.balanceAfter = accounts[count].balance;
    saveTransaction(trans);
    
    count++;
    cout << "\nAccount created successfully!" << endl;
    cout << "Account opened on: " << accounts[count-1].dateOpened << endl;
}

void viewAllAccounts(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    cout << "\n--- All Bank Accounts ---" << endl;
    cout << left << setw(12) << "Acc No" 
         << setw(25) << "Holder Name" 
         << setw(15) << "Type" 
         << setw(15) << "Balance" 
         << setw(10) << "Status" << endl;
    cout << string(77, '-') << endl;
    
    for(int i = 0; i < count; i++) {
        cout << left << setw(12) << accounts[i].accountNumber
             << setw(25) << accounts[i].accountHolder
             << setw(15) << accounts[i].accountType
             << "Rs. " << setw(11) << fixed << setprecision(2) << accounts[i].balance
             << setw(10) << (accounts[i].isActive ? "Active" : "Closed") << endl;
    }
}

void depositMoney(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    int accNum;
    cout << "\nEnter Account Number: ";
    cin >> accNum;
    
    int index = findAccountIndex(accounts, count, accNum);
    
    if(index == -1) {
        cout << "\nAccount not found!" << endl;
        return;
    }
    
    if(!accounts[index].isActive) {
        cout << "\nThis account is closed!" << endl;
        return;
    }
    
    double amount;
    cout << "Enter amount to deposit: Rs. ";
    cin >> amount;
    
    if(amount <= 0) {
        cout << "\nInvalid amount!" << endl;
        return;
    }
    
    accounts[index].balance += amount;
    
    // Save transaction
    Transaction trans;
    trans.accountNumber = accNum;
    trans.type = "Deposit";
    trans.amount = amount;
    trans.date = getCurrentDateTime();
    trans.balanceAfter = accounts[index].balance;
    saveTransaction(trans);
    
    cout << "\nDeposit successful!" << endl;
    cout << "New Balance: Rs. " << fixed << setprecision(2) << accounts[index].balance << endl;
}

void withdrawMoney(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    int accNum;
    string pin;
    
    cout << "\nEnter Account Number: ";
    cin >> accNum;
    cin.ignore();
    
    cout << "Enter PIN: ";
    getline(cin, pin);
    
    if(!verifyPIN(accounts, count, accNum, pin)) {
        cout << "\nInvalid PIN!" << endl;
        return;
    }
    
    int index = findAccountIndex(accounts, count, accNum);
    
    if(index == -1) {
        cout << "\nAccount not found!" << endl;
        return;
    }
    
    if(!accounts[index].isActive) {
        cout << "\nThis account is closed!" << endl;
        return;
    }
    
    double amount;
    cout << "Current Balance: Rs. " << fixed << setprecision(2) << accounts[index].balance << endl;
    cout << "Enter amount to withdraw: Rs. ";
    cin >> amount;
    
    if(amount <= 0) {
        cout << "\nInvalid amount!" << endl;
        return;
    }
    
    if(amount > accounts[index].balance) {
        cout << "\nInsufficient balance!" << endl;
        return;
    }
    
    accounts[index].balance -= amount;
    
    // Save transaction
    Transaction trans;
    trans.accountNumber = accNum;
    trans.type = "Withdraw";
    trans.amount = amount;
    trans.date = getCurrentDateTime();
    trans.balanceAfter = accounts[index].balance;
    saveTransaction(trans);
    
    cout << "\nWithdrawal successful!" << endl;
    cout << "New Balance: Rs. " << fixed << setprecision(2) << accounts[index].balance << endl;
}

void transferMoney(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    int fromAcc, toAcc;
    string pin;
    
    cout << "\nEnter Your Account Number: ";
    cin >> fromAcc;
    cin.ignore();
    
    cout << "Enter PIN: ";
    getline(cin, pin);
    
    if(!verifyPIN(accounts, count, fromAcc, pin)) {
        cout << "\nInvalid PIN!" << endl;
        return;
    }
    
    int fromIndex = findAccountIndex(accounts, count, fromAcc);
    
    if(fromIndex == -1) {
        cout << "\nYour account not found!" << endl;
        return;
    }
    
    if(!accounts[fromIndex].isActive) {
        cout << "\nYour account is closed!" << endl;
        return;
    }
    
    cout << "Enter Recipient Account Number: ";
    cin >> toAcc;
    
    int toIndex = findAccountIndex(accounts, count, toAcc);
    
    if(toIndex == -1) {
        cout << "\nRecipient account not found!" << endl;
        return;
    }
    
    if(!accounts[toIndex].isActive) {
        cout << "\nRecipient account is closed!" << endl;
        return;
    }
    
    double amount;
    cout << "Your Balance: Rs. " << fixed << setprecision(2) << accounts[fromIndex].balance << endl;
    cout << "Enter amount to transfer: Rs. ";
    cin >> amount;
    
    if(amount <= 0) {
        cout << "\nInvalid amount!" << endl;
        return;
    }
    
    if(amount > accounts[fromIndex].balance) {
        cout << "\nInsufficient balance!" << endl;
        return;
    }
    
    accounts[fromIndex].balance -= amount;
    accounts[toIndex].balance += amount;
    
    // Save transactions
    Transaction trans1;
    trans1.accountNumber = fromAcc;
    trans1.type = "Transfer Out";
    trans1.amount = amount;
    trans1.date = getCurrentDateTime();
    trans1.balanceAfter = accounts[fromIndex].balance;
    saveTransaction(trans1);
    
    Transaction trans2;
    trans2.accountNumber = toAcc;
    trans2.type = "Transfer In";
    trans2.amount = amount;
    trans2.date = getCurrentDateTime();
    trans2.balanceAfter = accounts[toIndex].balance;
    saveTransaction(trans2);
    
    cout << "\nTransfer successful!" << endl;
    cout << "Your New Balance: Rs. " << fixed << setprecision(2) << accounts[fromIndex].balance << endl;
}

void checkBalance(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    int accNum;
    string pin;
    
    cout << "\nEnter Account Number: ";
    cin >> accNum;
    cin.ignore();
    
    cout << "Enter PIN: ";
    getline(cin, pin);
    
    if(!verifyPIN(accounts, count, accNum, pin)) {
        cout << "\nInvalid PIN!" << endl;
        return;
    }
    
    int index = findAccountIndex(accounts, count, accNum);
    
    if(index != -1) {
        cout << "\n--- Balance Information ---" << endl;
        cout << "Account Number: " << accounts[index].accountNumber << endl;
        cout << "Account Holder: " << accounts[index].accountHolder << endl;
        cout << "Current Balance: Rs. " << fixed << setprecision(2) << accounts[index].balance << endl;
        
        // Ask if they want to see transaction history
        char choice;
        cout << "\nView transaction history? (y/n): ";
        cin >> choice;
        if(choice == 'y' || choice == 'Y') {
            viewTransactionHistory(accNum);
        }
    }
}

void viewAccountDetails(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    int accNum;
    cout << "\nEnter Account Number: ";
    cin >> accNum;
    
    int index = findAccountIndex(accounts, count, accNum);
    
    if(index == -1) {
        cout << "\nAccount not found!" << endl;
        return;
    }
    
    cout << "\n--- Account Details ---" << endl;
    cout << "Account Number: " << accounts[index].accountNumber << endl;
    cout << "Account Holder: " << accounts[index].accountHolder << endl;
    cout << "Account Type: " << accounts[index].accountType << endl;
    cout << "Balance: Rs. " << fixed << setprecision(2) << accounts[index].balance << endl;
    cout << "Date Opened: " << accounts[index].dateOpened << endl;
    cout << "Status: " << (accounts[index].isActive ? "Active" : "Closed") << endl;
}

void closeAccount(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    int accNum;
    string pin;
    
    cout << "\nEnter Account Number to close: ";
    cin >> accNum;
    cin.ignore();
    
    cout << "Enter PIN: ";
    getline(cin, pin);
    
    if(!verifyPIN(accounts, count, accNum, pin)) {
        cout << "\nInvalid PIN!" << endl;
        return;
    }
    
    int index = findAccountIndex(accounts, count, accNum);
    
    if(index != -1) {
        if(!accounts[index].isActive) {
            cout << "\nThis account is already closed!" << endl;
            return;
        }
        
        char confirm;
        cout << "\nCurrent Balance: Rs. " << fixed << setprecision(2) << accounts[index].balance << endl;
        cout << "Are you sure you want to close this account? (y/n): ";
        cin >> confirm;
        
        if(confirm == 'y' || confirm == 'Y') {
            accounts[index].isActive = false;
            cout << "\nAccount closed successfully!" << endl;
            
            if(accounts[index].balance > 0) {
                cout << "Please collect your balance of Rs. " << fixed << setprecision(2) 
                     << accounts[index].balance << " from the counter." << endl;
            }
        }
    }
}

void searchAccount(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    string name;
    cout << "\nEnter Account Holder Name to search: ";
    getline(cin, name);
    
    cout << "\n--- Search Results ---" << endl;
    cout << left << setw(12) << "Acc No" 
         << setw(25) << "Holder Name" 
         << setw(15) << "Type" 
         << setw(15) << "Balance" << endl;
    cout << string(67, '-') << endl;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(accounts[i].accountHolder.find(name) != string::npos) {
            cout << left << setw(12) << accounts[i].accountNumber
                 << setw(25) << accounts[i].accountHolder
                 << setw(15) << accounts[i].accountType
                 << "Rs. " << fixed << setprecision(2) << accounts[i].balance << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No accounts found matching the name!" << endl;
    }
}

void calculateTotalBalance(Account accounts[], int count) {
    if(count == 0) {
        cout << "\nNo accounts found in the system!" << endl;
        return;
    }
    
    double total = 0;
    int activeCount = 0;
    
    for(int i = 0; i < count; i++) {
        if(accounts[i].isActive) {
            total += accounts[i].balance;
            activeCount++;
        }
    }
    
    cout << "\n--- Bank Statistics ---" << endl;
    cout << "Total Accounts: " << count << endl;
    cout << "Active Accounts: " << activeCount << endl;
    cout << "Total Bank Balance: Rs. " << fixed << setprecision(2) << total << endl;
}

void saveAccountsToFile(Account accounts[], int count) {
    ofstream outFile(FILENAME);
    
    if(!outFile) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }
    
    outFile << count << endl;
    for(int i = 0; i < count; i++) {
        outFile << accounts[i].accountNumber << endl;
        outFile << accounts[i].accountHolder << endl;
        outFile << accounts[i].accountType << endl;
        outFile << accounts[i].balance << endl;
        outFile << accounts[i].dateOpened << endl;
        outFile << accounts[i].pin << endl;
        outFile << accounts[i].isActive << endl;
    }
    
    outFile.close();
}

void loadAccountsFromFile(Account accounts[], int &count) {
    ifstream inFile(FILENAME);
    
    if(!inFile) {
        count = 0;
        return;
    }
    
    inFile >> count;
    inFile.ignore();
    
    for(int i = 0; i < count; i++) {
        inFile >> accounts[i].accountNumber;
        inFile.ignore();
        getline(inFile, accounts[i].accountHolder);
        getline(inFile, accounts[i].accountType);
        inFile >> accounts[i].balance;
        inFile.ignore();
        getline(inFile, accounts[i].dateOpened);
        getline(inFile, accounts[i].pin);
        inFile >> accounts[i].isActive;
        inFile.ignore();
    }
    
    inFile.close();
}

void saveTransaction(Transaction trans) {
    ofstream outFile(TRANS_FILE, ios::app);
    
    if(!outFile) {
        return;
    }
    
    outFile << trans.accountNumber << "|"
            << trans.type << "|"
            << trans.amount << "|"
            << trans.date << "|"
            << trans.balanceAfter << endl;
    
    outFile.close();
}

void viewTransactionHistory(int accountNumber) {
    ifstream inFile(TRANS_FILE);
    
    if(!inFile) {
        cout << "\nNo transaction history found!" << endl;
        return;
    }
    
    cout << "\n--- Transaction History ---" << endl;
    cout << left << setw(20) << "Type" 
         << setw(15) << "Amount" 
         << setw(25) << "Date" 
         << setw(15) << "Balance After" << endl;
    cout << string(75, '-') << endl;
    
    string line;
    bool found = false;
    
    while(getline(inFile, line)) {
        int accNum;
        string type, date;
        double amount, balanceAfter;
        
        size_t pos = 0;
        accNum = stoi(line.substr(0, line.find('|')));
        
        if(accNum == accountNumber) {
            pos = line.find('|') + 1;
            size_t nextPos = line.find('|', pos);
            type = line.substr(pos, nextPos - pos);
            
            pos = nextPos + 1;
            nextPos = line.find('|', pos);
            amount = stod(line.substr(pos, nextPos - pos));
            
            pos = nextPos + 1;
            nextPos = line.find('|', pos);
            date = line.substr(pos, nextPos - pos);
            
            pos = nextPos + 1;
            balanceAfter = stod(line.substr(pos));
            
            cout << left << setw(20) << type
                 << "Rs. " << setw(11) << fixed << setprecision(2) << amount
                 << setw(25) << date
                 << "Rs. " << fixed << setprecision(2) << balanceAfter << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No transactions found for this account!" << endl;
    }
    
    inFile.close();
}

string getCurrentDateTime() {
    time_t now = time(0);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buffer);
}

bool verifyPIN(Account accounts[], int count, int accNum, string pin) {
    int index = findAccountIndex(accounts, count, accNum);
    if(index != -1) {
        return accounts[index].pin == pin;
    }
    return false;
}

int findAccountIndex(Account accounts[], int count, int accNum) {
    for(int i = 0; i < count; i++) {
        if(accounts[i].accountNumber == accNum) {
            return i;
        }
    }
    return -1;
}
