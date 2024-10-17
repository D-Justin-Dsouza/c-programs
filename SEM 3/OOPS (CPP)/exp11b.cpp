//Write a C++ program to understand how to use iteratiors to output a string
#include <iostream>
#include <string>
using namespace std;

int main(){
    string str = "Hello World!";
    string::iterator it;
    for(it = str.begin(); it != str.end(); it++){
        cout << *it;
    }
    cout << endl;
    return 0;
}