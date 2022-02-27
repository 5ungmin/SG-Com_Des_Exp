#include "Str.h"
#include <cstdlib>
#include <string.h>
#include <iostream>
using namespace std;

/* constructor */
Str::Str(int leng) //Make a string with the length of leng.
{
    if (leng < 0) {
        cout << "Error: String length should not be negative." << endl;
        exit(1);
    }
    else {
        str = new char[leng+1];
        len = leng;
    }
}

Str::Str(const char *neyong) //Make a string and initialize the string with neyong.
{
    len = strlen(neyong);
    str = new char[len+1];
    strcpy(str, neyong);
}

/* destructor */
Str::~Str()
{
    delete[] str;
}

/* Return the length of the string. */
int Str::length(void)
{
    return len;
}

/* Return the content of the string. */
char* Str::contents(void)
{
    return str;
}

/* strcmp operations */
/* If str and a are identical, return 0. */
int Str::compare(class Str& a) // strcmp with the content of a
{
    return strcmp(str, a.contents());
}

int Str::compare(char *a) // strcmp with the content of a
{
    return strcmp(str, a);
}

/* str <- a */
void Str::operator=(class Str& a)
{
    strcpy((char*) str, a.contents()); //str <- a.contents()
    len = a.length();                  //len <- a.length()
}

/* str <- a */
void Str::operator=(char *a)
{
    strcpy((char*) str, a); //str <- a
    len = strlen(str);      //len <- strlen(str)
}

