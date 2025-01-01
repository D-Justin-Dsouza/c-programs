#include <iostream>
#include <iomanip>
using namespace std;

class Employee {
protected:
    int id;
    string name;
    string designation;
public:
    void setEmployee(int i, string n, string d) {
        id = i;
        name = n;
        designation = d;
    }
};

class Components : public Employee {
protected:
    float basicPay;
    float hra;
    float da;
    float pf;
public:
    void setComponents(float b, float h, float d, float p) {
        basicPay = b;
        hra = h;
        da = d;
        pf = p;
    }
};

class NetSalary : public Components {
protected:
    float netSalary;
public:
    void setNetSalary() {
        cout << "Enter the Employee ID: ";
        cin >> id;
        cout << "Enter the Employee Name: ";
        cin >> name;
        cout << "Enter the Employee Designation: ";
        cin >> designation;
        cout << "Enter the Employee Basic Pay: ";
        cin >> basicPay;
        cout << "Enter the Employee HRA: ";
        cin >> hra;
        cout << "Enter the Employee DA: ";
        cin >> da;
        cout << "Enter the Employee PF: ";
        cin >> pf;
        setEmployee(id, name, designation);
        setComponents(basicPay, hra, da, pf);
        netSalary = basicPay + hra + da - pf;
    }
    float getNetSalary() {
        return netSalary;
    }
    void display() {
        cout <<setw(20)<< id<< setw(10) << name << setw(15) << designation << setw(10) << basicPay << setw(10) << hra << setw(10) << da << setw(10) << pf << setw(12) << netSalary << endl;
    }
};

int main() {
    cout << "Enter number of records: ";
    int n;
    cin >> n;
    NetSalary *e=new NetSalary[n];

    for (int i = 0; i < n; ++i) {
        e[i].setNetSalary();
        cout<<endl;
    }
    int index = 0;
    float maxSalary = e[0].getNetSalary();
    for (int i = 1; i < n; ++i) {
        if (e[i].getNetSalary() > maxSalary) {
            maxSalary = e[i].getNetSalary();
            index = i;
        }
    }
    cout.setf(ios::left,ios::adjustfield);
    cout<<setw(20)<<"EmpID"<< setw(10) << "EmpName" << setw(15) << "Designation" << setw(10) << "Basic Pay" << setw(10) << "HRA" << setw(10) << "DA" << setw(10) << "PF" << setw(12) << "Net Salary" << endl;
    for(int i=0;i<n;i++){
        e[i].display();
    }
    cout << "\nEmployee with the highest net salary:\n";
    cout<<setw(20)<<"EmpID"<< setw(10) << "EmpName" << setw(15) << "Designation" << setw(10) << "Basic Pay" << setw(10) << "HRA" << setw(10) << "DA" << setw(10) << "PF" << setw(12) << "Net Salary" << endl;
    e[index].display();

    return 0;
}