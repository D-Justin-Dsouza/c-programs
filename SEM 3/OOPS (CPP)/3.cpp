#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int acount=0;

class Article{
    string name;
    int price;
    public:
    Article(){
        name="\0";
        price=0;
    }
    Article(int p, string n){
        acount++;
        name=n;
        if(p<=0)
            price=0;
        else
            price=p;
        cout<<endl<<"Object a"<<acount<<" created"<<endl;
    }
    ~Article(){
        cout<<endl<<"Object a"<<acount<<" destroyed"<<endl;
        acount--;
    }
    void print(){
        cout<<left<<setw(20)<<name<<left<<setw(15)<<price<<endl;
    }
    void modify(string n){
        name=n;
        cout<<"\nItem modified,Updated data is as follows\n";
        cout<<endl<<left<<setw(20)<<"Article-Name"<<left<<setw(15)<<"Price(in Rs.)"<<endl;
        print();
    }
    void modify(int p){
        price=p;
        cout<<"\nItem modified,Updated data is as follows\n";
        cout<<endl<<left<<setw(20)<<"Article-Name"<<left<<setw(15)<<"Price(in Rs.)"<<endl;
        print();
    }
};
void test(){
    static Article a3(150,"Cup");
    Article a4(400,"Plate");
    cout<<endl<<left<<setw(20)<<"Article-Name"<<left<<setw(15)<<"Price(in Rs.)"<<endl;
    a3.print();
    a4.print();
}
Article a1(50.,"Pen");
int main(){
    Article a2(200,"Book");
    test();
    a1.print();
    a2.print();
    a1.modify(80);
    a2.modify("TextBook");
    cout<<endl;
    return 0;
}
