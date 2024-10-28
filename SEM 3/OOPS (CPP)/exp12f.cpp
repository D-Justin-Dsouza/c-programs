/*write a function template palindrome that takes a vector parameter and returns true or false according to whether the vector does or doesn't read the same forward as backward(like  1,2,3,2,1 is a vector palindrome, but 1,2,3,1 is not )*/
#include <iostream>
#include <vector>
using namespace std;

template <class T>
bool palindrome(vector<T> v){
    int n = v.size();
    for (int i = 0; i < n/2; i++){
        if (v[i] != v[n-i-1])
            return false;
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