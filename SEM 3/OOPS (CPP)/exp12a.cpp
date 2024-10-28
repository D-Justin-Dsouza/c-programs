//Write a C++ program to implement standard library vector sequence container
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    int n, x;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++){
        cin >> x;
        v.push_back(x);
    }
    cout << "The elements are: ";
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    cout << "Enter the index to access: ";
    cin >> x;
    cout << "\nElement at index " << x << " is " << v.at(x) << endl;
    return 0;
}