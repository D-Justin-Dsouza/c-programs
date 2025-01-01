#include <iostream>
#include <vector>
using namespace std;
template <class T>
bool palindrome(vector<T> v){
    int n = v.size();
    typename vector<T>::iterator it1 = v.begin();
    typename vector<T>::iterator it2 = v.end() - 1;
    while(it1 < it2){
        if(*it1 != *it2){
            return false;
        }
        it1++;
        it2--;
    }
    return true;
}
int main(){
    vector<int> v;
    cout << "Enter the number of elements: ";
    int n;
    cin >> n;
    cout << "Enter the elements: ";
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        v.push_back(x);
    }
    if(palindrome(v))
        cout << "Palindrome" << endl;
    else   
        cout << "Not Palindrome" << endl;
    return 0;
}
