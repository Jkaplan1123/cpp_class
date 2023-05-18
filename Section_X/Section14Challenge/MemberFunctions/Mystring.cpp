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

// String Manipulation and Concatenation
// unary minus - returns lowercase version of object's string
Mystring Mystring::operator-(){
    char *buff = new char[std::strlen(str) + 1];
    std::strcpy(buff, str);
    for (size_t idx = 0; idx < std::strlen(buff); idx++){
        buff[idx] = tolower(buff[idx]);
    }

    Mystring temp {buff};
    delete [] buff;
    return temp;

}

//concatenation - returns an object that concatenates the lhs and rhs
Mystring Mystring::operator+(const Mystring &rhs) const{
    Mystring temp {std::strcat(str, rhs.str)};
    return temp;
} 

//concatenate the rhs string to the lhs string and store the result in lhs object. a += b is equivalent to a = a+b
Mystring &Mystring::operator+=(const Mystring &rhs){
    *this = *this + rhs;
    return *this;
}   

//create a string consisting of the initial string repeated n many times (e.g. "abc" * 3 = "abcabcabc")
Mystring Mystring::operator*(int n) const{

    //implementation using + operator defined above
    Mystring temp {str};
    for (size_t idx = 0; idx < (n-1); idx++){
        temp += str;
    }

    // // Ground-up implementation
    // int input_len = std::strlen(str);
    // char *buff = new char [(input_len*n)+1];
    // for (size_t i = 0; i < n; i++){
    //     for (size_t j = 0; j < input_len; j++){
    //         buff[j + (i*input_len)] = str[j];
    //     }
    // }
    // Mystring temp {buff};
    // delete [] buff;


    return temp;
}

//do the same as the * operator but assign it to the lhs object
Mystring &Mystring::operator*=(int n){
    *this = (*this) * n;
    return *this;
}


// Comparison Operator Overloading

//returns true if two strings are equal
bool Mystring::operator==(const Mystring &rhs) const{
    return (std::strcmp(str, rhs.str) == 0);
}

//returns false if two strings are not equal
bool Mystring::operator!=(const Mystring &rhs) const{
    return (std::strcmp(str, rhs.str) != 0);
}

//returns true if the lhs string is lexically less than the rhs string
bool Mystring::operator<(const Mystring &rhs) const{
    return (std::strcmp(str, rhs.str) < 0);
} 

// returns false if the lhs string is lexically less than the rhs string
bool Mystring::operator>(const Mystring &rhs) const{
    return (std::strcmp(str, rhs.str) > 0);
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

