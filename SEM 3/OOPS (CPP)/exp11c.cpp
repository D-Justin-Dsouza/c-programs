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
    string input = "John 25 5.8";
    stringstream ss(input);
    ss >> name >> age >> height;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << endl;
    return 0;
}
