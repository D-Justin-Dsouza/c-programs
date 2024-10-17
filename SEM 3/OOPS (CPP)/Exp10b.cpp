#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

class TelephoneDirectory {
    string name, number;
public:
    void add() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter number: ";
        cin >> number;
    }
    void display() const {
        cout<<setw(10)<<name<<setw(15)<<number<<endl;
    }
    string getName() const {
        return name;
    }
    string getNumber() const {
        return number;
    }
    friend istream& operator>>(istream& in, TelephoneDirectory& td) {
        in >> td.name >> td.number;
        return in;
    }
    friend ostream& operator<<(ostream& out, const TelephoneDirectory& td) {
        out << td.name << " " << td.number << endl;
        return out;
    }
};
void addEntry(fstream& file) {
    TelephoneDirectory td;
    td.add();
    file.clear();  
    file.seekp(0, ios::end); 
    file << td;  
    cout << "Entry added to the directory.\n";
}
void searchEntry(fstream& file, const string& name) {
    TelephoneDirectory td;
    file.clear();
    file.seekg(0, ios::beg); 
    bool found = false;

    while (file >> td) {
        if (td.getName() == name) {
            cout << "Entry found:\n";
            td.display();
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Entry not found.\n";
}

void updateEntry(fstream& file, const string& name) {
    fstream tempFile("temp.txt", ios::out);  
    TelephoneDirectory td;
    bool found = false;

    file.clear();  
    file.seekg(0, ios::beg);

    while (file >> td) {
        if (td.getName() == name) {
            cout << "Updating entry for " << name << "...\n";
            td.add(); 
            found = true;
        }
        tempFile << td;
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("telephone_directory.txt");
        rename("temp.txt", "telephone_directory.txt");
        cout << "Entry updated.\n";
        file.open("telephone_directory.txt", ios::in | ios::out | ios::app); 
    } else {
        cout << "Entry not found.\n";
        remove("temp.txt");  
    }
}

void displayAllEntries(fstream& file) {
    TelephoneDirectory td;
    file.clear();  
    file.seekg(0, ios::beg); 

    cout << "Telephone Directory Entries:\n";
    while (file >> td) {
        td.display();
    }
}

int main() {
    fstream file("telephone_directory.txt", ios::in | ios::out | ios::app);
    if (!file) {
        cout << "Error opening file.\n";
        return 1;
    }

    int choice;
    string name;

    do {
        cout << "\n1. Add\n2. Search\n3. Update\n4. Display All\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEntry(file);
                break;
            case 2:
                cout << "Enter name to search: ";
                cin >> name;
                searchEntry(file, name);
                break;
            case 3:
                cout << "Enter name to update: ";
                cin >> name;
                updateEntry(file, name);
                break;
            case 4:
                cout<<"Displaying all entries"<<endl;
                cout<<setw(10)<<"Name"<<setw(15)<<"Number"<<endl;
                displayAllEntries(file);
                break;
            case 5:
                file.close();
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
