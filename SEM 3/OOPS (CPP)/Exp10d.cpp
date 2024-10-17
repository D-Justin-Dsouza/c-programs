#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Employee {
public:
    int empNo;
    float basicPay;
    float da;
    float cca;
    float hra;
    float grossSalary;
    void calculateSalary() {
        da = 0.51 * basicPay;      
        cca = 100;                 
        hra = 0.15 * basicPay;     
        if (hra > 800) hra = 800;  
        grossSalary = basicPay + da + cca + hra;
    }
    void display() const {
        cout << setw(10) << empNo 
             << setw(15) << fixed << setprecision(2) << basicPay 
             << setw(10) << fixed << setprecision(2) << da
             << setw(10) << fixed << setprecision(2) << cca 
             << setw(10) << fixed << setprecision(2) << hra 
             << setw(15) << fixed << setprecision(2) << grossSalary 
             << endl;
    }
    void writeToFile(ostream &outFile) const {
        outFile << setw(10) << empNo
                << setw(15) << fixed << setprecision(2) << basicPay
                << setw(15) << fixed << setprecision(2) << da
                << setw(10) << fixed << setprecision(2) << cca
                << setw(10) << fixed << setprecision(2) << hra
                << setw(15) << fixed << setprecision(2) << grossSalary 
                << endl;
    }
    void modifyBasicPay(float newPay) {
        basicPay = newPay;
        calculateSalary();
    }
};
void addEmployeeData() {
    ifstream inFile("employee.txt");
    ofstream outFile("salaries.txt", ios::app);
    if (!inFile || !outFile) {
        cout << "Error opening file for reading/writing.\n";
        return;
    }
    outFile.seekp(0, ios::end); 
    if (outFile.tellp() == 0) { 
        outFile << setw(10) << "Emp No." << setw(15) << "Basic Pay" << setw(15) << "DA"
                << setw(10) << "CCA" << setw(10) << "HRA" << setw(15) << "Gross Salary" << endl;
    }
    Employee emp;
    while (inFile >> emp.empNo >> emp.basicPay) {
        emp.calculateSalary();
        emp.writeToFile(outFile);
    }
    inFile.close();
    outFile.close();
    cout << "\nEmployee data has been added to the salaries file.\n";
}
void displayEmployeeData() {
    ifstream inFile("salaries.txt");
    if (!inFile) {
        cout << "Error opening salaries file for reading.\n";
        return;
    }
    Employee emp;
    string title;
    
    getline(inFile, title);
    cout << title << endl;

    while (inFile >> emp.empNo >> emp.basicPay >> emp.da >> emp.cca >> emp.hra >> emp.grossSalary) {
        cout << setw(10) << emp.empNo 
             << setw(15) << fixed << setprecision(2) << emp.basicPay 
             << setw(15) << fixed << setprecision(2) << emp.da
             << setw(10) << fixed << setprecision(2) << emp.cca 
             << setw(10) << fixed << setprecision(2) << emp.hra 
             << setw(15) << fixed << setprecision(2) << emp.grossSalary 
             << endl;
    }
    inFile.close();
}


void modifyEmployeeBasicPay(int empNo, float newPay) {
    ifstream inFile("salaries.txt");
    ofstream tempFile("temp.txt"); 

    if (!inFile || !tempFile) {
        cout << "Error opening file for modification.\n";
        return;
    }

    Employee emp;
    bool found = false;
    string title;
    getline(inFile, title);
    tempFile << title << endl;
    while (inFile >> emp.empNo >> emp.basicPay >> emp.da >> emp.cca >> emp.hra >> emp.grossSalary) {
        if (emp.empNo == empNo) {
            emp.basicPay = newPay;
            emp.calculateSalary(); 
            found = true;
        }
        emp.writeToFile(tempFile); 
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("salaries.txt");     
        rename("temp.txt", "salaries.txt"); 
        cout << "Employee's basic salary has been modified.\n";
    } else {
        cout << "Employee not found.\n";
        remove("temp.txt");
    }
}

int main() {
    int choice;
    int empNo;
    float newPay;
    do {
        cout << "\n1. Add Employee Data\n2. Display Employee Data\n3. Modify Employee Basic Pay\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addEmployeeData();
                break;
            case 2:
                displayEmployeeData();
                break;
            case 3:
                cout << "Enter Employee Number to modify: ";
                cin >> empNo;
                cout << "Enter new Basic Pay: ";
                cin >> newPay;
                modifyEmployeeBasicPay(empNo, newPay);
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}
