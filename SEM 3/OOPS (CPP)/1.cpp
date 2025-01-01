#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class employee {
    string name, status;
    short empno;
    float sal, updated_sal;

public:
    void accept();
    void display();
    void change(int n, employee e[]);
};

void employee::accept() {
    cout << "\n\tEnter Employee Number: ";
    cin >> empno;
    cin.ignore();
    cout << "\n\tEnter Employee's Full Name: ";
    getline(cin, name);
    cout << "\n\tEnter Employee's Salary: ";
    cin >> sal;
    updated_sal = sal;
    status = "No Change";
}

void employee::display() {
    cout << setw(15) << empno<< setw(20) << name<< setw(15) << updated_sal<< setw(15) << sal << setw(15) << status << endl;
}

void employee::change(int n, employee e[]) {
    short se;
    cout << "Enter the Employee Number: ";
    cin >> se;
    for (int i = 0; i < n; i++) {
        if (e[i].empno == se) {
            cout << "\nEnter New Salary: ";
            e[i].sal = e[i].updated_sal;
            cin >> e[i].updated_sal;

            if (e[i].updated_sal > e[i].sal) {
                cout << "\nEmployee is promoted";
                e[i].status = "Promoted";
            } else if (e[i].updated_sal < e[i].sal) {
                cout << "\nEmployee is demoted";
                e[i].status = "Demoted";
            } else {
                cout << "\nNo change in employee's job";
                e[i].status = "No Change";
            }
            return;
        }
    }
    cout << "\nEmployee Not Found\n";
}

int main() {
    int n, choice;
    cout << "\nEnter Number Of Employees: ";
    cin >> n;
    employee *e=new employee[n];
    cout << "\nEnter Employee Data \n";
    for (int i = 0; i < n; i++) {
        cout << "Employee " << i + 1;
        e[i].accept();
    }

    while (1) {
        cout << "\nOperations available\n1. Display Employee Data\n2. Change Employee Salary\n3. Exit\nEnter: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << setw(15) << "employee-no"<< setw(20) << "name"<< setw(15) << "current salary"<< setw(15) << "Old salary"<< setw(15) << "Status" << endl;
                for (int i = 0; i < n; i++) {
                    e[i].display();
                }
                break;
            case 2:
                e[0].change(n, e);
                break;
            case 3:
                delete[] e;
                exit(0);
            default:
                cout << "\nInvalid Choice\n";
        }
    }

    return 0;
}
