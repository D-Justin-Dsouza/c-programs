//Write a C++ program to implement a multi catch exception handling mechanism
#include<iostream>
using namespace std;

int main(){
    int a, b;
    do{
        cout<<"Enter two numbers: ";
        cin>>a>>b;
        try{
            if(a!=0 && b==0)
                throw b;
            else if (a==0 || b==0)
                throw 3.5;
            else
                cout<<"Result: "<<a/b<<endl;
        }
        catch(int x){
            cout<<"Exception: Division by zero"<<endl;
        }
        catch(...){
            cout<<"Exception: Invalid input"<<endl;
        }
        cout<<"Enter 1 to continue, 0 to exit: ";
        int ch;
        cin>>ch;
        if(ch==0)
            break;
    }while(1);
    return 0;
}