#include "Array.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Array::Array(int size)
{
    //constructor
    if (size < 0) {
        cout << "Error: Size should be positive." << endl;
        exit(1);
    }
    else {
        data = new int[size];
        len = size;
    }
}

Array::~Array()
{
    //destructor
    delete[] data;
}

int Array::length() const {
    //Return the length of the array.
    return len;
}

int& Array::operator[](int i) {
    static int tmp;

    if (i >= 0 && i < len) {
        return data[i];
    }
    else {
        cout << "Array bound error!" << endl;
        return tmp;
    }
}

int Array::operator[](int i) const {
    if (i >= 0 && i < len) {
        return data[i];
    }
    else {
        cout << "Array bound error!" << endl;
        return 0;
    }
}

void Array::print() {
    int i;
    cout << "[";
    for (i = 0; i < len-1; i++) {
        cout << data[i] << " ";
    }
    cout << data[i];
    cout << "]" << endl;
}

