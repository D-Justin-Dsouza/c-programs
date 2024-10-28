//Write a C++ program to implement standard library queue adapter class template
#include <iostream>
#include <queue>
using namespace std;
class Queue{
    queue<int> q;
    public:
    void push(int x){
        q.push(x);
    }
    void del(){
        q.pop();
    }
    void display(){
        queue<int> temp = q;
        while (!temp.empty()){
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};  
int main(){
    Queue q;
    int ch, x;
    while (1){
        cout << "1. Push\n2. Delete\n3. Display\n4. Exit\nEnter your choice: ";
        cin >> ch;
        switch (ch){
            case 1:
                cout << "Enter the element: ";
                cin >> x;
                q.push(x);
                break;
            case 2:
                q.del();
                break;
            case 3:
                q.display();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}