//Write a C++ program to implement standard library list sequence container
//use real world simple application
#include <iostream>
#include <list>
using namespace std;

int main(){
    list<int> l;
    int n, x;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++){
        cin >> x;
        l.push_back(x);
    }
    cout << "The elements are: ";
    for (list<int>::iterator it = l.begin(); it != l.end(); it++){
        cout << *it << " ";
    }
    cout << "\nEnter the element to search: ";
    cin >> x;
    list<int>::iterator it;
    for (it = l.begin(); it != l.end(); it++){
        if (*it == x){
            cout << "Element found at position " << distance(l.begin(), it) + 1<< endl;
            break;
        }
    }
    if (it == l.end())
        cout << "Element not found\n";
    cout << endl;
    return 0;
}