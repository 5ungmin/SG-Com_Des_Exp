#ifndef MTT
#define MTT
#include "Array.h"

class RangeArray : public Array {
protected:
    int base;
    int end;
public:
    RangeArray(int, int);
    ~RangeArray();

    int baseValue();
    int endValue();

    int& operator[](int);
    int operator[](int) const;
};
#endif
