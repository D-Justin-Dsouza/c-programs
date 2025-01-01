/*write a function template palindrome that takes a vector parameter and returns true or false according to whether the vector does or doesn't read the same forward as backward(like  1,2,3,2,1 is a vector palindrome, but 1,2,3,1 is not )*/
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
    vector<int> v1 = {1, 2, 3, 2, 1};
    vector<int> v2 = {1, 2, 3, 1};
    cout << "v1 is " << (palindrome(v1) ? "palindrome" : "not palindrome") << endl;
    cout << "v2 is " << (palindrome(v2) ? "palindrome" : "not palindrome") << endl;
    return 0;
}