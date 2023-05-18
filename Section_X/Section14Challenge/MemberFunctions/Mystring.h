#ifndef _MYSTRING_H_
#define _MYSTRING_H_

class Mystring
{
    friend std::ostream &operator<<(std::ostream &os, const Mystring &rhs);
    friend std::istream &operator>>(std::istream &in, Mystring &rhs);

private:
    char *str;      // pointer to a char[] that holds a C-style string
public:
    Mystring();                                                         // No-args constructor
    Mystring(const char *s);                                     // Overloaded constructor
    Mystring(const Mystring &source);                    // Copy constructor
    Mystring( Mystring &&source);                         // Move constructor
    ~Mystring();                                                     // Destructor
    
    Mystring &operator=(const Mystring &rhs);     // Copy assignment
    Mystring &operator=(Mystring &&rhs);           // Move assignment

    // String Manipulation and Concatenation
    Mystring operator-(); // unary minus - returns lowercase version of object's string
    Mystring operator+(const Mystring &rhs) const; //concatenation - returns an object that concatenates the lhs and rhs
    Mystring &operator+=(const Mystring &rhs);     //concatenate the rhs string to the lhs string and store the result in lhs object. a += b is equivalent to a = a+b
    Mystring operator*(int n) const; //create a string consisting of the initial string repeated n many times (e.g. "abc" * 3 = "abcabcabc")
    Mystring &operator*=(int n); //do the same as the * operator but assign it to the lhs object


    // Comparison Operator Overloading
    bool operator==(const Mystring &rhs) const; //returns true if two strings are equal
    bool operator!=(const Mystring &rhs) const; //returns false if two strings are not equal
    bool operator<(const Mystring &rhs) const; //returns true if the lhs string is lexically less than the rhs string
    bool operator>(const Mystring &rhs) const; // returns false if the lhs string is lexically less than the rhs string


    
    
    void display() const;
    
    int get_length() const;                                      // getters
    const char *get_str() const;
};

#endif // _MYSTRING_H_