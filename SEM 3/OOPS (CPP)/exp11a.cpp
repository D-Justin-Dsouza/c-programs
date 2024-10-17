/* Write a C++ program to create string & perform the following:
i. String assignment & concatenation
ii. Compare strings
iii. Find substrings & characters in a string
iv. Swapping strings*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s1 = "This is";
    string s2 = " a string";
    string s3 = s1 + s2;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;
    if (s1 == s2)
        cout << "s1 is equal to s2" << endl;
    else
        cout << "s1 is not equal to s2" << endl;

    if (s1 < s2)
        cout << "s1 is less than s2" << endl;
    else
        cout << "s1 is not less than s2" << endl;
    
    if (s1 > s2)
        cout << "s1 is greater than s2" << endl;
    else
        cout << "s1 is not greater than s2" << endl;
    
    string s4 = "A dog and a cat play together";
    string s5 = "cat play";
    if (s4.find(s5) != string::npos)
        cout << "Substring found" << endl;
    else
        cout << "Substring not found" << endl;

    string s6 = "Hello";
    string s7 = "World";
    cout << "Before swapping:" << endl;
    cout << "s6: " << s6 << endl;
    cout << "s7: " << s7 << endl;
    s6.swap(s7);
    cout << "After swapping:" << endl;
    cout << "s6: " << s6 << endl;
    cout << "s7: " << s7 << endl;
    return 0;
}