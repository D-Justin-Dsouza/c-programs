/*Write a C++ program to implement exceptional handling concept (Divide by zero) using
exception rethrow mechanism*/
#include<iostream>
using namespace std;

int main(){
    do{
        int a, b,c;
        cout<<"Enter two numbers: ";
        cin>>a>>b;
        try{
            if(b==0)
                throw b;
            cout<<"Result: "<<a/b<<endl;
        }
        catch(int x){
            cout<<"Exception: Division by zero"<<endl;
        }
        cout<<"Enter 1 to continue, 0 to exit: ";
        int ch;
        cin>>ch;
        if(ch==0)
            break;
    }while(1);
    return 0;
}