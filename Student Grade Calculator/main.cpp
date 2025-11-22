#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

struct Student {
    string name;
    vector<double> grades;
};

char calculateLetterGrade(double average) {
    if (average >= 90) {
        return 'A';
    } else if (average >= 80) {
        return 'B';
    } else if (average >= 70) {
        return 'C';
    } else if (average >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

int main() {
    vector<Student> students;
    int numStudents, numGrades;

    cout << "Enter the number of students: ";
    cin >> numStudents;

    cout << "Enter the number of grades per student: ";
    cin >> numGrades;

    for (int i = 0; i < numStudents; i++) {
        Student newStudent;
        cout << "Enter student name: ";
        cin >> newStudent.name;

        cout << "Enter " << numGrades << " grades for " << newStudent.name << ": ";
        for (int j = 0; j < numGrades; j++) {
            double grade;
            cin >> grade;
            newStudent.grades.push_back(grade);
        }
        students.push_back(newStudent);
    }

    cout << "\n--- Student Grades ---" << endl;

    for (const auto& student : students) {
        double sum = accumulate(student.grades.begin(), student.grades.end(), 0.0);
        double average = sum / student.grades.size();
        char letterGrade = calculateLetterGrade(average);

        cout << "Student: " << student.name << endl;
        cout << "  Average: " << average << endl;
        cout << "  Letter Grade: " << letterGrade << endl;
    }

    return 0;
}
