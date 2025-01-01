#include <iostream>
#include <iomanip>
using namespace std;

class square;
class rectangle{
    float l,b,a;
    public:
    void setval(){
        cout<<"Enter length and breadth of rectangle:";
        cin>>l>>b;
        a=l*b;
    }
    friend void compare(rectangle &,square &);
};
class square{
    float s,a;
    public:
    void setval(){
        cout<<endl<<"Enter side of square:";
        cin>>s;
        a=s*s;
    }
    friend void compare(rectangle &,square &);
};
void compare(rectangle &p,square &q){
    cout<<endl<<"Area of Rectangle:"<<p.a<<" sq units"<<endl<<"Area of Square:"<<q.a<<" sq units";
    if(p.a>q.a)
        cout<<"\nArea of square is larger than rectangle by "<<setprecision(2)<<p.a-q.a<<" sq. units";
    else if(p.a<q.a)
        cout<<"\nArea of rectangle is larger than square by "<<setprecision(2)<< q.a-p.a<<" sq. units";
    else
        cout<<"\nArea of rectangle is equal to Area of square";
}
int main(){
    rectangle r;
    square s;
    r.setval();
    s.setval();
    compare(r,s);
}
