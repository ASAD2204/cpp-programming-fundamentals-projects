#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 100;
const string FILENAME = "students.txt";

struct Student {
    int id;
    string name;
    int age;
    string course;
    float gpa;
};

// Function prototypes
void displayMenu();
void addStudent(Student students[], int &count);
void viewAllStudents(Student students[], int count);
void searchStudent(Student students[], int count);
void updateStudent(Student students[], int count);
void deleteStudent(Student students[], int &count);
void calculateAverageGPA(Student students[], int count);
void sortStudentsByGPA(Student students[], int count);
void saveToFile(Student students[], int count);
void loadFromFile(Student students[], int &count);

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;
    
    // Load existing data from file
    loadFromFile(students, studentCount);
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch(choice) {
            case 1:
                addStudent(students, studentCount);
                break;
            case 2:
                viewAllStudents(students, studentCount);
                break;
            case 3:
                searchStudent(students, studentCount);
                break;
            case 4:
                updateStudent(students, studentCount);
                break;
            case 5:
                deleteStudent(students, studentCount);
                break;
            case 6:
                calculateAverageGPA(students, studentCount);
                break;
            case 7:
                sortStudentsByGPA(students, studentCount);
                break;
            case 8:
                saveToFile(students, studentCount);
                cout << "Data saved successfully!" << endl;
                break;
            case 9:
                saveToFile(students, studentCount);
                cout << "Exiting program. Data saved!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
        if(choice != 9) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while(choice != 9);
    
    return 0;
}

void displayMenu() {
    system("cls");
    cout << "\n========================================" << endl;
    cout << "   STUDENT MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Add New Student" << endl;
    cout << "2. View All Students" << endl;
    cout << "3. Search Student" << endl;
    cout << "4. Update Student Information" << endl;
    cout << "5. Delete Student" << endl;
    cout << "6. Calculate Average GPA" << endl;
    cout << "7. Sort Students by GPA" << endl;
    cout << "8. Save Data to File" << endl;
    cout << "9. Exit" << endl;
    cout << "========================================" << endl;
}

void addStudent(Student students[], int &count) {
    if(count >= MAX_STUDENTS) {
        cout << "Error: Maximum student limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Add New Student ---" << endl;
    
    cout << "Enter Student ID: ";
    cin >> students[count].id;
    cin.ignore();
    
    cout << "Enter Student Name: ";
    getline(cin, students[count].name);
    
    cout << "Enter Age: ";
    cin >> students[count].age;
    cin.ignore();
    
    cout << "Enter Course: ";
    getline(cin, students[count].course);
    
    cout << "Enter GPA (0.0 - 4.0): ";
    cin >> students[count].gpa;
    
    count++;
    cout << "\nStudent added successfully!" << endl;
}

void viewAllStudents(Student students[], int count) {
    if(count == 0) {
        cout << "\nNo students found in the system!" << endl;
        return;
    }
    
    cout << "\n--- All Students ---" << endl;
    cout << left << setw(10) << "ID" 
         << setw(25) << "Name" 
         << setw(8) << "Age" 
         << setw(20) << "Course" 
         << setw(8) << "GPA" << endl;
    cout << string(71, '-') << endl;
    
    for(int i = 0; i < count; i++) {
        cout << left << setw(10) << students[i].id
             << setw(25) << students[i].name
             << setw(8) << students[i].age
             << setw(20) << students[i].course
             << setw(8) << fixed << setprecision(2) << students[i].gpa << endl;
    }
}

void searchStudent(Student students[], int count) {
    if(count == 0) {
        cout << "\nNo students found in the system!" << endl;
        return;
    }
    
    int searchId;
    cout << "\nEnter Student ID to search: ";
    cin >> searchId;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(students[i].id == searchId) {
            cout << "\n--- Student Found ---" << endl;
            cout << "ID: " << students[i].id << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Age: " << students[i].age << endl;
            cout << "Course: " << students[i].course << endl;
            cout << "GPA: " << fixed << setprecision(2) << students[i].gpa << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nStudent with ID " << searchId << " not found!" << endl;
    }
}

void updateStudent(Student students[], int count) {
    if(count == 0) {
        cout << "\nNo students found in the system!" << endl;
        return;
    }
    
    int searchId;
    cout << "\nEnter Student ID to update: ";
    cin >> searchId;
    cin.ignore();
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(students[i].id == searchId) {
            cout << "\n--- Current Information ---" << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Age: " << students[i].age << endl;
            cout << "Course: " << students[i].course << endl;
            cout << "GPA: " << students[i].gpa << endl;
            
            cout << "\n--- Enter New Information ---" << endl;
            cout << "Enter Student Name: ";
            getline(cin, students[i].name);
            
            cout << "Enter Age: ";
            cin >> students[i].age;
            cin.ignore();
            
            cout << "Enter Course: ";
            getline(cin, students[i].course);
            
            cout << "Enter GPA (0.0 - 4.0): ";
            cin >> students[i].gpa;
            
            cout << "\nStudent information updated successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nStudent with ID " << searchId << " not found!" << endl;
    }
}

void deleteStudent(Student students[], int &count) {
    if(count == 0) {
        cout << "\nNo students found in the system!" << endl;
        return;
    }
    
    int searchId;
    cout << "\nEnter Student ID to delete: ";
    cin >> searchId;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(students[i].id == searchId) {
            // Shift all elements after this index
            for(int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            cout << "\nStudent deleted successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nStudent with ID " << searchId << " not found!" << endl;
    }
}

void calculateAverageGPA(Student students[], int count) {
    if(count == 0) {
        cout << "\nNo students found in the system!" << endl;
        return;
    }
    
    float sum = 0;
    for(int i = 0; i < count; i++) {
        sum += students[i].gpa;
    }
    
    float average = sum / count;
    cout << "\nTotal Students: " << count << endl;
    cout << "Average GPA: " << fixed << setprecision(2) << average << endl;
}

void sortStudentsByGPA(Student students[], int count) {
    if(count == 0) {
        cout << "\nNo students found in the system!" << endl;
        return;
    }
    
    // Bubble sort - descending order
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(students[j].gpa < students[j + 1].gpa) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    cout << "\nStudents sorted by GPA (highest to lowest)!" << endl;
    viewAllStudents(students, count);
}

void saveToFile(Student students[], int count) {
    ofstream outFile(FILENAME);
    
    if(!outFile) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }
    
    outFile << count << endl;
    for(int i = 0; i < count; i++) {
        outFile << students[i].id << endl;
        outFile << students[i].name << endl;
        outFile << students[i].age << endl;
        outFile << students[i].course << endl;
        outFile << students[i].gpa << endl;
    }
    
    outFile.close();
}

void loadFromFile(Student students[], int &count) {
    ifstream inFile(FILENAME);
    
    if(!inFile) {
        // File doesn't exist yet, start with empty data
        count = 0;
        return;
    }
    
    inFile >> count;
    inFile.ignore();
    
    for(int i = 0; i < count; i++) {
        inFile >> students[i].id;
        inFile.ignore();
        getline(inFile, students[i].name);
        inFile >> students[i].age;
        inFile.ignore();
        getline(inFile, students[i].course);
        inFile >> students[i].gpa;
        inFile.ignore();
    }
    
    inFile.close();
}
