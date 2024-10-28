//Write a C++ program to implement standard library deque sequence container
#include <iostream>
#include <deque>
using namespace std;

class Deque{
    deque<int> d;
    public:
    void push_front(int x){
        d.push_front(x);
    }
    void push_back(int x){
        d.push_back(x);
    }
    void pop_front(){
        d.pop_front();
    }
    void pop_back(){
        d.pop_back();
    }
    void display(){
        deque<int> temp = d;
        while (!temp.empty()){
            cout << temp.front() << " ";
            temp.pop_front();
        }
        cout << endl;
    }
};
int main(){
    Deque d;
    int ch, x;
    while (1){
        cout << "1. Push Front\n2. Push Back\n3. Pop Front\n4. Pop Back\n5. Display\n6. Exit\nEnter your choice: ";
        cin >> ch;
        switch (ch){
            case 1:
                cout << "Enter the element: ";
                cin >> x;
                d.push_front(x);
                break;
            case 2:
                cout << "Enter the element: ";
                cin >> x;
                d.push_back(x);
                break;
            case 3:
                d.pop_front();
                break;
            case 4:
                d.pop_back();
                break;
            case 5:
                d.display();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}