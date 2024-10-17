#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student {
    string name, roll, address, branch;
public:
    void add() {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter roll: ";
        getline(cin, roll);
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter branch: ";
        getline(cin, branch);
    }
    void display(){
        cout << "Name: " << name << endl;
        cout << "Roll: " << roll << endl;
        cout << "Address: " << address << endl;
        cout << "Branch: " << branch << endl;
    }
    string getRoll(){
        return roll;
    }
    friend istream& operator>>(istream& in, Student& s) {
        getline(in, s.name);
        getline(in, s.roll);
        getline(in, s.address);
        getline(in, s.branch);
        return in;
    }
    friend ostream& operator<<(ostream& out, const Student& s) {
        out << s.name << endl;
        out << s.roll << endl;
        out << s.address << endl;
        out << s.branch << endl;
        return out;
    }
};
void addStudent() {
    Student s;
    s.add();
    fstream file;
    file.open(s.getRoll() + ".txt", ios::out);
    if (file.is_open()) {
        file << s; 
        file.close();
        cout << "Student details added successfully!\n";
    } else {
        cout << "Error opening file for writing!\n";
    }
}
void searchStudent(const string& roll) {
    Student s;
    fstream file;
    file.open(roll + ".txt", ios::in); 
    if (file.is_open()) {
        file >> s;  
        s.display();
        file.close();
    } else {
        cout << "No student found with roll number " << roll << "!\n";
    }
}

// Function to update student details
void updateStudent(const string& roll) {
    Student s;
    fstream file;
    file.open(roll + ".txt", ios::in);  // Open the file to check if it exists
    if (file.is_open()) {
        file.close();
        cout << "Enter updated details:\n";
        s.add();  // Get new details from the user

        file.open(roll + ".txt", ios::out);  // Reopen the file in output mode to overwrite
        file << s;  // Write updated details to the file
        file.close();
        cout << "Student details updated successfully!\n";
    } else {
        cout << "No student found with roll number " << roll << "!\n";
    }
}

// Function to display a student's details
void displayStudent(const string& roll) {
    searchStudent(roll);  // Reusing the search function to display student details
}

int main() {
    int choice;
    string roll;

    while (true) {
        cout << "\n1. Add\n2. Search\n3. Update\n4. Display\n5. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter roll number to search: ";
                cin >> roll;
                searchStudent(roll);
                break;
            case 3:
                cout << "Enter roll number to update: ";
                cin >> roll;
                updateStudent(roll);
                break;
            case 4:
                cout << "Enter roll number to display: ";
                cin >> roll;
                displayStudent(roll);
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
