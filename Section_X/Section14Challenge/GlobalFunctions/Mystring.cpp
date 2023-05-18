#include <iostream>
#include <cstring>
#include "Mystring.h"

 // No-args constructor
Mystring::Mystring() 
    : str{nullptr} {
    str = new char[1];
    *str = '\0';
}

// Overloaded constructor
Mystring::Mystring(const char *s) 
    : str {nullptr} {
        if (s==nullptr) {
            str = new char[1];
            *str = '\0';
        } else {
            str = new char[strlen(s)+1];
            strcpy(str, s);
        }
}

// Copy constructor
Mystring::Mystring(const Mystring &source) 
    : str{nullptr} {
        str = new char[strlen(source.str)+ 1];
        strcpy(str, source.str);
 //       std::cout << "Copy constructor used" << std::endl;

}

// Move constructor
Mystring::Mystring( Mystring &&source) 
    :str(source.str) {
        source.str = nullptr;
//        std::cout << "Move constructor used" << std::endl;
}

 // Destructor
Mystring::~Mystring() {
    delete [] str;
}

 // Copy assignment
Mystring &Mystring::operator=(const Mystring &rhs) {
//    std::cout << "Using copy assignment" << std::endl;

    if (this == &rhs) 
        return *this;
    delete [] str;
    str = new char[strlen(rhs.str) + 1];
    strcpy(str, rhs.str);
    return *this;
}

// Move assignment
Mystring &Mystring::operator=( Mystring &&rhs) {
 //   std::cout << "Using move assignment" << std::endl;
    if (this == &rhs) 
        return *this;
    delete [] str;
    str = rhs.str;
    rhs.str = nullptr;
    return *this;
}


// Display method
void Mystring::display() const {
    std::cout << str << " : " << get_length() << std::endl;
}

 // getters
 int Mystring::get_length() const { return strlen(str); }
 const char *Mystring::get_str() const { return str; }

// overloaded insertion operator
std::ostream &operator<<(std::ostream &os, const Mystring &rhs) {
    os << rhs.str;
    return os;
}

// overloaded extraction operator
std::istream &operator>>(std::istream &in, Mystring &rhs) {
    char *buff = new char[1000];
    in >> buff;
    rhs = Mystring{buff};
    delete [] buff;
    return in;
}

// String Manipulation and Concatenation

// unary minus - returns lowercase version of object's string
Mystring operator-(const Mystring &rhs){
    char *buff = new char[std::strlen(rhs.str) + 1];
    std::strcpy(buff, rhs.str);
    for (size_t idx = 0; idx < std::strlen(buff); idx++){
        buff[idx] = tolower(buff[idx]);
    }

    Mystring temp {buff};
    delete [] buff;
    return temp;
} 

//concatenation - returns an object that concatenates the lhs and rhs
Mystring operator+(const Mystring &lhs, const Mystring &rhs){
    Mystring temp {std::strcat(lhs.str, rhs.str)};
    return temp;
}

//concatenate the rhs string to the lhs string and store the result in lhs object. a += b is equivalent to a = a+b
Mystring &operator+=(Mystring &lhs, const Mystring &rhs){
    lhs = lhs + rhs;
    return lhs;
}     

//create a string consisting of the initial string repeated n many times (e.g. "abc" * 3 = "abcabcabc")
Mystring operator*(const Mystring &rhs, int n){
    
    Mystring temp {rhs};
    for (size_t idx = 1; idx < n; idx++){
        temp += rhs;
    }

    return temp;
}

//do the same as the * operator but assign it to the lhs object
Mystring &operator*=(Mystring &lhs, int n){
    lhs = lhs * n;
    return lhs;
}


// Comparison Operator Overloading

//returns true if two strings are equal
bool operator==(Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str, rhs.str) == 0);
}

//returns false if two strings are not equal
bool operator!=(Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str, rhs.str) != 0);
}

//returns true if the lhs string is lexically less than the rhs string
bool operator<(Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str, rhs.str) < 0);
} 

// returns false if the lhs string is lexically less than the rhs string
bool operator>(Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str, rhs.str) > 0);
} 