//[D] Write a C++ program to implement standard library stack adapter class, menu driven

#include <iostream>
#include <stack>
using namespace std;
class Stack{
    stack<int> s;
public:
    void push(int x){
        s.push(x);
    }
    void pop(){
        s.pop();
    }
    void display(){
        stack<int> temp = s;
        while (!temp.empty()){
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }
};
int main(){
    Stack s;
    int ch, x;
    while (1){
        cout << "1. Push\n2. Pop\n3. Display\n4. Exit\nEnter your choice: ";
        cin >> ch;
        switch (ch){
            case 1:
                cout << "Enter the element: ";
                cin >> x;
                s.push(x);
                break;
            case 2:
                s.pop();
                break;
            case 3:
                s.display();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}