## Section 14 - Operator Overloading

### What is Operator Overloading?

- using traditional operators (e.g. `+`, `=`, `*`, etc.) with user-defined types
	- traditional operators designed to be used with primitive built-in types 
-  operator overloading allows user-defined types to behave similar to built-in types (e.g. string concatenation)
-  Can make code more readable and writeable
-  Operator overloading is not done automatically (except for the asssignment operator `=`) - they must be explicitly defined
	- The compiler does not make assumptions as to what it means to add, multiply, etc. in the context of your class. 
	- in most cases it doesn't make sense to add, multiply, etc. user-defined types (e.g. what does it mean to "add" two `Player` objects?)
	- Only overload operators if it makes sense



Suppose we have a `Number` class that models any number

Assume that `a`, `b`, `c` and `d` are all `Number` objects

- If we weren't using operator overloading, we could implement functions or methods to achieve what we want. For example:
	- Using functions:
	
	```
	// assume mulitply(), add(), and divide() 
	// are all defined using primitive types
	Number result = multiply(add(a,b), divide(c,d))
	```
	
	- Using member methods:
	
	```
	// assume mulitply(), add(), and divide() 
	// are all defined using primitive types
	Number result = (a.add(b)).multiply(c.divide(d));
	```

- Alternatively, we could use overloaded operators - much cleaner and easier on the programmer

	```
	Number result = (a+b)*(c/d)
	```
	

Most operators can be overloaded, but come cannot. The operators that cannot be overloaded are: `::`, `:?`, `.*`, `.`, and `sizeof`.

Basic Rules:

- Precedence and Associativity of the operator cannot be changed
- the 'arity' cannot be changed (i.e. can't make the division operator unary)
- Cannot overload operators for primitive types (e.g. `int`, `double`, etc.)
- Can't create new operators
- `[]`, `()`, `->`, and the assignment operator (`=`) **must** be declared as member methods
- Other operators can be declared as member methods or global functions

#### Examples of Operator Overloading

- It could be useful to define what `std::cout << p1` means for an object in the `Player` class. Do I output the name, health, XP?

#### Example Class

##### Header (`.h`) File

```
class Mystring
{
private:
    char *str; // pointer to a char[] that holds a C-style string
    
public:
    Mystring();  // No-args contstructor
    Mystring(const char *s); // Overloaded contstructor              
    Mystring(const Mystring &source); // Copy constructor
    ~Mystring(); // Destructor
    
    // Methods
    void display() const;
    
    // getters
    int get_length() const;
    const char *get_str() const;
};
```

##### `.cpp` File with Explanations

The code from the `.cpp` file is broken up into parts and explained

###### `#include` Statements

```
#include <cstring>
#include <iostream>
#include "Mystring.h"
```

###### No-args constructor


```
Mystring::Mystring() 
    : str{nullptr} {
    
    str = new char[1];
    *str = '\0';
}
```

We want to store an empty string as an array consisting of a single character with the null terminator (`\0`) in it. 

- `str = new char[1]` Creates a pointer to a new location on the heap with space for 1 character
- `*str = '\0'` puts the terminator character in the location on the heap

###### Overloaded constructor

```
Mystring::Mystring(const char *s) 
    : str {nullptr} {
    
	     // check to see if nullptr
        if (s==nullptr) {
            str = new char[1];
            *str = '\0';
        }
        

        else {
            str = new char[std::strlen(s)+1];
            std::strcpy(str, s);
        }
}
```
- First, check to see if a `nullptr` was passed in. If so, treat it the same was as the noargs constructor
- `str = new char[std::strlen(s)+1];` creates a pointer to a new location on the heap with enough space to hold the entire string being passed in.
- Then copy the input string to the newly created location on the heap (`std::strcpy(str, s)`).


###### Copy constructor

```
Mystring::Mystring(const Mystring &source) 
     : str{nullptr} {
     
        // Create a pointer to a new location on the heap with
        // enough space to hold the entire string from the source
        // being copied. Then copy the input string to that
        // location on the heap. This is a deep copy.
        str = new char[std::strlen(source.str )+ 1];
        std::strcpy(str, source.str);
}

```

- `&source` is the address of the item being copied
- `str = new char[std::strlen(source.str )+ 1];` creates a pointer to a new location on the heap with enough space to hold the entire string being copied.
- `std::strcpy(str, source.str);` copies the input string to the newly created location on the heap

####### Destructor

```
Mystring::~Mystring() {
    delete [] str;
}
```

###### Methods

```
// Display method
void Mystring::display() const {
    std::cout << str << " : " << get_length() << std::endl;
}

// length getter
 int Mystring::get_length() const { return std::strlen(str); }
 
  // string getter
 const char *Mystring::get_str() const { return str; }
```

### Overloading the Copy Assignment Operator

- C++ uses the copy assignment operator (`=`) when it assigns one object to another object. 
- Do not confuse assignment with initialization - Assignment occurs when an object has already been initialized and you want to assign another object to it. 

	```
	Mystring s1 {"Frank"}; // initialization
	Mystring s2 = s1; // NOT assignment. This is initialization
	Mystring s3 {s1}; // T the same as Mystring s2 {s1}
	
	s2 = s1; // assignment
	```	
	
	- `Mystring s2 = s1;` is initialization, not assignment. It is the equivalent of the statement `Mystring s2 {s1};`. This is because `s2` has not been created yet. 
	- `s2 = s1` is assignment because `s2` has arlaready ben created an initialized
- If you do not provide a user-defined overloaded assignment operator, then the C++ compiler will provide a computer generated one for you.
	- Very similar to default copy constructor
	- Default assignment is memberwise assignment (shallow copy). 
	- If we have a raw pointer data then we must deep copy.


Assignment Operator must be overloaded as a member function

#### Method Prototype

```
Type &Type::operator=(const Type &rhs);
```

- This goes in the `.h` file. 
- We overload methods using the keyword `operator` followed by the operator that we wish to overload. 
	- In this case the method name is `operator=` 
- This is not construction, this is assignment. The left-hand side already exists. 
- Returns a reference to a `Type` object. This is useful for avoiding extra copies if we want to return by value.
	- We want to allow chain assignments (e.g. `p1 = p2 = p3`).
- Replace `Type` with the appropriate class name. For example:

	```
	Mystring &Mystring::operator=(const Mystring &rhs);
	```
	
	- Once this code is implemented it will allow us to write code like: `s2 = s1;`. When we do so, the compiler will see `s2.operator=(s1);`. This makes the code much more readable


#### Implementing the Overloaded Copy Assignment Operator (deep copy)

```
Mystring &Mystring::operator=(const Mystring &rhs) {
    std::cout << "Copy assignment" << std::endl;
    if (this == &rhs){
        return *this;
    }
    delete [] this->str;
    str = new char[std::strlen(rhs.str) + 1];
    std::strcpy(this->str, rhs.str);
    return *this;
}
```

- Remember: the object on the left-hand side of an assignment statement is referred to by the `this` pointer. The object on the right-hand side is being passed into the method.
	- The right-hand side object has been named `rhs` for clarity 
- Since we are assigning the right-hand side to the left-hand side, we must make a deep copy of the right-hand side object's attributes and copy them over to the left-hand side object
	- The left-hand side object will be overwritten. 
- The above code is only for a single raw pointer. If your class has multiple raw pointers, then don't forget to deep copy each of them.

##### Working through the code:

- `if (this == &rhs)` - check for self-assignment. If so, return the left-hand side object
- `delete [] this->str;` - deallocate storage for `this->str` since we are overwriting it
- `str = new char[std::strlen(rhs.str) + 1];` - allocate storage for the deep copy
	- allocate space in the left-hand side object for the right-hand side object's data. 
- `std::strcpy(this->str, rhs.str);` - copy the data over to the left-hand side from the right-hand side
- `return *this;` - return the current by reference to allow chain assignment
 



### Overloading the Move Assignemnt Operator

- works with R-value references
- You can choose to overload the move assignment operator. C++ will use the copy assignment operator if necessary.

	```
	Mystring s1;
	s1 = Mystring{"Jack"}; // move assignment
	```

- if we have a raw pointer we should overload the move assignment operator for efficiency


#### Assignment Statement Syntax:

```
Type &Type::operator=(Type &&rhs);
```

- Very similar to copy assignment but a few major differences: 
	- Use the `&&` operator in the parameter list to tell the compiler that the right-side obect is an r-value
		- right-side value will be an r-value reference
	- Right-hand side object reference can't be `const` 

##### Move Assignment Operator - `Mystring` Example:

```
Mystring &Mystring::operator=(Mystring &&rhs) {
    std::cout << "Using move assignment" << std::endl;
    if (this == &rhs){ 
        return *this;
    }
    delete [] str;
    str = rhs.str;
    rhs.str = nullptr;
    return *this;
    
}
```

###### Working Through the Code

Similar to the Copy Assignment but we are not deep copying from the right-hand side object

- `if (this == &rhs)` - check for self-assignment. If so, return the left-hand side object
- `delete [] str;` - deallocate current storage pointed to by the left-hand side object since we are overwriting i
	- for example in the code below we initialize a `Mystring` object `s1` with the value `"Hello"`. We then want to assign `s1` the value `"Hola"`. The `delete [] str;` command deletes the spot on the heap where `"Hello"` is stored. This step is critical.

	```
	Mystring str1 {"Hello"};
	str1 = "Hola"
	```
	 
- `str = rhs.str;` - steal the pointer
	- this is a copy of a pointer variable, not a full deep copy  
- `rhs.str = nullptr;` - null out the rhs object (Critical)
- `return *this;` - return the current by reference to allow chain assignment

### Oveloading Operators as Member Methods

#### Unary Operators

[Unary operators](https://www.geeksforgeeks.org/unary-operators-cc/) act upon a single operand to produce a new value. These operators are `-`, `++`, `--`, `!`, `&`, and `sizeof()`.

- `-` is the unary minus, which makes an operand negative. It is not used to subtract two numbers, as that would make it a binary operator. Example: `a = -100` uses the unary minus

Basic Method Declaration

```
ReturnType Type::operatorOp()
```

- The `Op` in `operatorOp` refers to the specific operator to be overwritten. For example `operator++` overloads the increment (`++`) operator.
- In the case that we have to return a new object from the method, we'll return the new object by value.
- Unary member methods have an empty parameter list because the object we are working with is refered to by the `this` pointer. 


Example for hypothetical `Number` class:

```
Number Number::operator-() const;
Number Number::operator++(); //pre-increment
Number Number::operator++(int); //post-increment
bool Number::operator!() const;
```

```
Number n1 {100};
number n2 = -n1 // n1.operator-()
n2 = ++n1; //n1.operator++()
n2 = n1++; //n1.operator++(int)
```

Example for `Mystring` class that uses unary minus operator to make a string all lower case.

```
// Make lowercase
Mystring operator-(const Mystring &obj) {

	 // Create a buffer array 
    char *buff = new char[std::strlen(obj.str) + 1];
    std::strcpy(buff, obj.str);
    
    // make buffer lower case
    for (size_t i=0; i<std::strlen(buff); i++){ 
        buff[i] = std::tolower(buff[i]);
    }
    
    // create a new object initialized with the lower case buffer
    Mystring temp {buff};
    delete [] buff; // Delete buffer
    return temp; // return the new object
}
```

- We are returning a new object that will be a lowercase deep copy of the existing object
- `const` because we don't want to modify the current object, we want to return a new object based on the current object.
- We need to think about whether overloading the operator to perform this function makes sense. Probably better to create a method named `to_lower()` or something like that.

#### Binary Operators

Binary operators are applied to two operands. These include the basic mathmatical operators (`+`, `-`, `*`, `/`, `%`), the comparison operators (`==`, `!=`, `>`, `<`, etc.), and many more

- note that the `-` operator here is the binary difference operator for subtracting two values rather than the unary operator that turns a value negative 


```
ReturnType Type::operatorOp(const Type &rhs);
```

This is the same as the syntax for returning the unary operators except we have a single parameter in the method parameter list 

- This parameter is named `rhs` in this code to make sure that it is clear that it refers to the parameter on the right hand side of the operator
	- in `a + b`, the actual method being performed is `a.operator+(b)` because `b` is on the right hand side of the `+` operator
- The `this` pointer points to the object on the left-hand side of the operator
- The only limitation is that the object on the left-hand side must be an object of the class you are using.
	- For example, if you are using `+` for concatenation in the `Mystring` class.

	```
	Mystring larry {"Larry"};
	Mystring stooges {" is one of the three stooges"};
	Mystring result;
	
	result = larry + stooges // OK, larry.operator+(stooges)
	result = larry + " is the best stooge"; // OK, larry.(" is also a stooge")
	result = "Moe" + stooges // ERROR - "Moe".operator+(stooges)
	``` 
	
	- `result = larry + stooges` is okay because both `larry` and `stooges` are `Mystring` objects. 
	- `result = larry + " is the best stooge";` is okay because `larry` is a `Mystring` object and is on the left-hand side of the operator
	- `"Moe" + stooges` causes an error because `"Moe"` is a string literal not a `Mystring` object. Even though `stooges` is a `Mystring` object, it is on the right-hand side of the operator. The `Mystring` object needs to be on the left-hand side of the operator. `"Moe".operator+(stooges)` does not make sense.

Examples:

```
Number Number::operator+(const Number &rhs) const;
Number Number::operator-(const Number &rhs) const;
bool Number::operator==(const Number &rhs) const;
bool Number::operator<(const Number &rhs) const;
```

- notice that the overloaded addition and subtraction operators return the newly created sum or difference objects by value
- The equality operators return Booleans because they are comparing things 
- All of these take in `const` parameters because they are not modifying the initial parameter but instead returning another value based on the input


```
Number n1{100}, n2 {200};
Number n3 = n1 + n2; // n1.operator+(n2)
n3 = n1 - n2; //n1.operator-(n2)
if (n1 == n2) ... /n1.operator==(n2)
```

Possible uses in the `Mystring` class

Can use the equality operator in the `Mystring` class to check to see if the strings are equal

```
bool operator==(const Mystring &lhs, const Mystring &rhs) {
    return (std::strcmp(lhs.str, rhs.str) == 0);
}
```

Can use the `+` operator in the `Mystring` class for concatenation.

Just make sure that however your overload the operators makes sense.

### Operators as Global Functions

- These are called global functions to show the contrast between member functions. These functions are not in the class.
- Since these are not member functions, we no longer have a `this` pointer referring to the object on the left-hand side
- We often need acess to private attributes in the objects, so you see these non-member functions declared as friend functions of the class in many applications
	- this isn't absolutely necessary since you can still use getter methods to access attribute values
- you cannot have both member and non-member versions of the overloaded operator at the same time because then the compiler would not know what to use

#### Unary Operators as Global Functions

```
ReturnType OperatorOp(Type &obj);
```

Exmaples for a hypothetical `Number` class

```
Number operator-(const Number &obj);
Number operator++(Number &obj); //pre-increment
Number operator++(Number &obj, int); //post-increment
bool operator!(const Number &obj);
```


- the function takes in as a parameter the object upon which the operator is acting


```
Number n1 {100};
number n2 = -n1 // operator-(n1)
n2 = ++n1; //operator++(n1)
n2 = n1++; //operator++(n1, int)
```

#### Binary Operators as Global Functions

```
ReturnType operatorOp(const Type &lhs, const Type &rhs);
```

- The first input `&lhs` is the left-hand side object
- The second input `&rhs` is the right-hand side object
- These are constant inputs since we are not modifying the initial inputs. Instead, we are returning a new object based on the sum/difference/etc. of the two inputs.
- With global functions, you do not need to have the left-hand side be a `Mystring` object. 
	- you can have the left-hand side be a `Mystring` object, the right-hand side be a `Mystring` object, or both sides be `Mystring` objects
	- Because both inputs are supposed to be `Mystring` objects, if you input a C-style string, then the compiler implicity converts a char to a `Mystring`.
	- you cannot have neither input be a `Mystring` object because then the compiler won't know to call the overloaded operator for the `Mystring` class.
	- Because both

```
Number operator+(const Number &lhs, const Number &rhs);
Number operator-(const Number &lhs, const Number &rhs);
bool operator==(const Number &lhs, const Number &rhs);
bool operator<(const Number &lhs, const Number &rhs);
```


Exmaple: equality operator for the `Mystring` class

```
bool operator==(const Mystring &lhs, const Mystring &rhs){
	if (std::strcmp(lhs.str, rhs.str) == 0){
		return true;
	}
	else{
		return false;
	}
}
```

- if the function is declared as a friend of `Mystring`, it can access the private `str` attribute. If not, we must use getter methods.
- Code is the same as implementation in the member method except you now have the `lhs` object instead of the `this` pointer

### Overloading Stream Insertion and Extraction Operators

- makes classes look and feel more like a C++ data type

It does not make sense to implment the insertion (`<<`) and extraction (`>>`) operators as member methods. Member methods require that the left operand must be a member of a user-defined class. This is not the way we normally use these operators. We usually have the operator to the left of whatever is being inserted or extracted.

```
Mystring {"Hello World"}
cout << "Hello World" << endl;

```


#### Stream Insertion Operator (`<<`)

```
std::ostream &operator<<(std::ostream &os, const Mystring &obj){
	os << obj.str // if a friend function
	//os << obj.get_str(); // if not a friend function
	
	return os
}
```


- The first argument (`std::ostream &os`) is an output stream object by reference
- The second argument (`const Mystring &obj`) is a reference to the `Mystring` object whose data we want to insert in the output string. 
	- use `const` to prevent us from modifying the data 
- Return a reference to the `ostream` so we can keep inserting. Don't return `ostream` by value
	- `ostream` is short for output stream 


#### Stream Extraction Operator (`>>`)

```
std::ostream &operator<<(std::istream &is, Mystring &obj){
	char *buff = new char[1000];
	is >> buff;
	obj = Mystring{buff}; //If you have copy or move assignment
	delte [] buff;
	return is
}
```

- Update the object passed in
- Return a reference to the `istream` (insertion stream)


- The first argument (`std::istream &is`) is an input stream object by reference whose type is `istream`
- The second argument (`Mystring &obj`) is a reference to the `Mystring` object into which we want to extract data. 
	-  this should not be a `const` because we want to modify the object
-  We can take the data from the input stream and either store it locally or store it directly in the object
- Return a reference to the `istream` so we can keep inserting. Don't return `istream` by value


##### Working through the code

- `char *buff = new char[1000];` - allocate a large array of characters that will hold the data we want to construct a `Mystring` object. This is created dynamically on the heap.
- `is >> buff;` - insert the data into the newly created array
- `obj = Mystring{buff};` - create a `Mystring` object using `buff`. This assumes you have a copy or move assignment operator defined
- `delete [] buff;` - delete the temporary variable `buff`
- `return is` - return a reference to the istream so we can keep inserting