//Write a C++ program to understand string stream processing concept
//use a real world application
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string name;
    int age;
    float height;
    cout << "Enter name, age and height: ";
    cin >>name>> age >> height;
    stringstream ss;
    ss << name << " " << age << " " << height;
    cout << "Input: " << ss.str() << endl;
    return 0;
}
