/*write a program to do the following
a. a function to read two double type numbers from keyboard
b. a function to calculate the division of these two numbers
c.a try block to throw an exception when a wrong type of data is keyed in(like invalid)
d. a try block to detect and throw an exception if the condition " divide-by-zero" occurs*/
#include <iostream>
using namespace std;

class Division{
    double a, b;
    public:
        void read(){
            cout << "Enter two double type numbers: ";
            cin >> a >> b;
        }
        void divide(){
            if(b == 0)
                throw b;
            cout << "Division: " << a/b << endl;
        }
};
int main(){
    Division d;
    do{
        try{
            d.read();
            d.divide();
            
            cout<<"Enter 1 to continue, 0 to exit: ";
            int ch;
            cin>>ch;
            if(ch==0)
                break;
        }
        catch(double b){
            cerr << "Divide by Zero error" << endl;
        }
    }while(1);
    return 0;
}