#include <iostream>

using namespace std;

void temperatureConverter() {
    double temp;
    char unit;

    cout << "Enter temperature with unit (C for Celsius, F for Fahrenheit): ";
    cin >> temp >> unit;

    if (unit == 'C' || unit == 'c') {
        cout << "Temperature in Fahrenheit: " << (temp * 9.0 / 5.0) + 32.0 << endl;
    } else if (unit == 'F' || unit == 'f') {
        cout << "Temperature in Celsius: " << (temp - 32.0) * 5.0 / 9.0 << endl;
    } else {
        cout << "Invalid unit." << endl;
    }
}

void lengthConverter() {
    double length;
    string unit;

    cout << "Enter length with unit (m for meters, ft for feet): ";
    cin >> length >> unit;

    if (unit == "m") {
        cout << "Length in feet: " << length * 3.28084 << endl;
    } else if (unit == "ft") {
        cout << "Length in meters: " << length / 3.28084 << endl;
    } else {
        cout << "Invalid unit." << endl;
    }
}

int main() {
    int choice;

    cout << "Select a converter:" << endl;
    cout << "1. Temperature Converter" << endl;
    cout << "2. Length Converter" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            temperatureConverter();
            break;
        case 2:
            lengthConverter();
            break;
        default:
            cout << "Invalid choice." << endl;
    }

    return 0;
}
