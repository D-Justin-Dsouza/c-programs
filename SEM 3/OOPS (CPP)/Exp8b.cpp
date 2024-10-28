/*Write a C++ program to create a class template to represent a generic vector. Include the

member functions to perform the following tasks
1. Create the vector
2. To modify the value of a given element
3. To display the vector elements*///make it menu driven if possible

#include <iostream>
using namespace std;

template <class T>
class Vector {
    T *arr;
    int size;
public:

