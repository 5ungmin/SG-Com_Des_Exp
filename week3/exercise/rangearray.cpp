#include "RangeArray.h"
#include <iostream>
using namespace std;

RangeArray::RangeArray(int i, int j) : Array(j-i+1)
{
    base = i;
    end = j;
}

RangeArray::~RangeArray()
{

}

int RangeArray::baseValue()
{
    return base;
}

int RangeArray::endValue()
{
    return end;
}

int& RangeArray::operator [](int i)
{
    static int tmp;
    if (i >= base && i <= end) {
        return data[i-base];
    }
    else {
        cout << "Array bound error!" << endl;
        return tmp;
    }
}

int RangeArray::operator [](int i) const
{
    if (i >= base && i <= end) {
        return data[i-base];
    }
    else {
        cout << "Array bound error!" << endl;
        return 0;
    }
}

