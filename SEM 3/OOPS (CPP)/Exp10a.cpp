#include<iostream>
#include<fstream>
using namespace std;

int main(){
    ofstream f1, f2;
    f1.open("file1.txt");
    f2.open("file2.txt");
    if (!f1.is_open() || !f2.is_open()) {
        cerr << "Error opening file1 or file2." << endl;
        return 1; 
    }
    int n;
    cout << "Enter 5 elements for file1: ";
    for(int i = 0; i < 5; i++){
        cin >> n;
        f1 << n << endl;
    }
    cout << "Enter 3 elements for file2: ";
    for(int i = 0; i < 3; i++){
        cin >> n;
        f2 << n << endl;
    }
    f1.close();
    f2.close();
    ifstream file1("file1.txt");
    ifstream file2("file2.txt");
    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Error opening file1 or file2 for reading." << endl;
        return 1;
    }
    ofstream file3("file3.txt");
    if (!file3.is_open()) {
        cerr << "Error opening file3." << endl;
        return 1;
    }
    int a[8], i = 0;
    while (file1 >> n)
        a[i++] = n;
    while (file2 >> n)
        a[i++] = n;
    if (i != 8) {
        cerr << "Error: Expected 8 elements, but got " << i << " elements." << endl;
        return 1;
    }
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7 - i; j++) {
            if(a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
    for(int i = 0; i < 8; i++)
        file3 << a[i] << endl;
    file1.close();
    file2.close();
    file3.close();
    cout << "Merged and sorted contents have been written to file3.txt" << endl;
    return 0;
}
