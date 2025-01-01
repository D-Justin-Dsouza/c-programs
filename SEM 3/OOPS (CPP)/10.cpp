/*Write a program that reads following text and counts number of times any entered word appears in it
    It is new. It is singular.
    It is simple. It must succeed.
*///string processing

#include<iostream>
#include<string>
#include<fstream>
#include<cctype>
using namespace std;
int main(){
    string word, s;
    int count = 0;    
    cout << "Enter the word to be searched: ";
    cin >> word;
    ifstream file("exp11d.txt");
    if (file.is_open()) {
        while (file >> s) {
            if (s.find(word) != string::npos) {
                count++;
            }
        }
        cout << "The word \"" << word << "\" appears " << count << " times in the text." << endl;
    }else 
        cout << "word not found." << endl;
    return 0;
}
