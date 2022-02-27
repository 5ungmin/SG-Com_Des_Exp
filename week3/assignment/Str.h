#ifndef Str_h
#define Str_h

class Str {
private:
    char *str; //what's in the string
    int len; //length of the string
    
public:
    /* constructor */
    Str(int leng); //Make a string with the length of leng.
    Str(const char *neyong); //Make a string and initialize the string with neyong.
    
    /* destructor */
    ~Str();
    
    /* Operations with the string. */
    int length(void); //Return the length of the string.
    char *contents(void); //Return the content of the string.
    
    int compare(class Str& a); //strcmp with the content of a
    int compare(char *a); //strcmp with the content of a
    
    void operator=(class Str& a); //String <- a
    void operator=(char *a); //String <- a
};

#endif /* Str_h */
