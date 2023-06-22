## Section 18 - Exception Handling

### Basic Concepts

Note: exceptions in C++ should only be used for synchronous code (as opposed to asynchronous code) 

[C++ Exception Handling Website](https://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm#:~:text=A%20C%2B%2B%20exception%20is%20a,try%2C%20catch%2C%20and%20throw)

- use exceptions to check error conditions that may occur at run time even if your code is correct
	- always check arguments to public functions by using exceptions 

#### Background

- Exception Handling deals with extraordinary situations
	- it indicates that an extraordinary situation has been detected or has occurred
	- it allows the program to deal with these extraordinary situations in a suitable manner
		- "suitable manner" depends on the program and application. In some cases, we can recover and continue. In other cases, we may have to terminate the program.
			- For example, if you are supposed to log data to a file but that file doesn't exist, your code can either (a) error out and end the program or (b) create a new file and start logging to that one
- Examples of what can cause an exception: insufficient resources, invalid operations, range violations, underflows and overflows, illegal data, etc.
- Exception safe - when your code handles exceptions


#### Terminology

- **Exception**: an object or primitive type that signals that an error has occured
	- this exception object often contains information about what happened 
- **Throwing/Raising an Exception**: this is the part of the code that detects that an error has occurred or will occur
	- This place where the error occured may not know how to handle the error
	- Code can throw an exception describing the error to another part of the program that knows how to handle the error
- **Catching/Handliing the Exception**: this is the part of the code that handles the exception
	- this may be the same part of the code that raised the exception but is usually a different part of the program.

#### Exception Handling Syntax

- `throw`
	- throws an exception
	- followed by an argument - the exception that we are throwing
	- best practice is to throw objects, not primitives
- `try {try block}`
	- you place code that may throw an exception in the `try block`
	- if there is no exception then the code executes as normal
	- if the code throws an exception then the try block is exited. The thrown exception is handled by a catch handler.
		- if no catch handler exists for that particular exception then the program terminates
- Catch handler `catch (Exception ex) {catch block}`
	- A catch handler handles the exception of type `Exception` and value `ex`
	- `catch block` is the block of code that handles the exception
		- only executes if an exception is thrown and the type of the thrown exception matches the parameter in the catch block 
		- may or may not cause the program to terminate  
	- can write multiple catch handlers to handle different types of exceptions

	
- Best practices is to throw by value and catch by reference
- We cannot have a catch block without a try block - the compiler needs to know where an exception might occur in order to set up the code to catch it
	- corollary: any try block must have a catch block


#### Example: Divide by Zero

```
int miles {};
int gallons {};
double miles_per_gallon {};
    
std::cout << "Enter the miles driven: ";
std::cin >> miles;
std::cout << "Enter the gallons used: ";
std::cin >> gallons;
    
try {
    if (gallons == 0){
        throw 0; // throw exception
    }
    miles_per_gallon = static_cast<double>(miles) / gallons;
    std::cout << "Result: " << miles_per_gallon << std::endl;
}

// 
catch (int &ex) {
    std::cerr << "Sorry, you can't divide by zero" << std::endl;
}
std::cout << "Bye" << std::endl;
```

### Throwing an Exception from a Function

- If you throw an execption in a function, C++ will try to find a handler that can handle that type of exception
- If that exception handler exists, it must be in one of the functions on the call stack that called this function
- The type of the exception that you throw does not have to be the same type that the function is supposed to return
#### Miles per Gallon Function Example

```
double calculate_mpg(int miles, int gallons) {
    if (gallons == 0){
        throw 0;
    }
    return static_cast<double>(miles) / gallons;
}

int main() {    
    int miles {};
    int gallons {};
    double miles_per_gallon {};   
    
    std::cout << "Enter the miles: ";
    std::cin >> miles;
    std::cout << "Enter the gallons: ";
    std::cin >> gallons;
    
    // Try block
    try {
        miles_per_gallon = calculate_mpg(miles, gallons);
        std::cout << "Result: " << miles_per_gallon << std::endl;
    }
    
    // Catch handler 
    catch (int &ex) {
        std::cerr << "Tried to divide by zero" << std::endl;
    }
    std::cout << "Bye" << std::endl;

    return 0;
}


```

### Handling Mulitple Exceptions

Many functions can fail in multiple ways. For example, the miles per gallon calculator does not return a logical result if: `gallons` is 0, `gallons` is negative, or `miles` is negative. We need to check for each of these and throw an exception if they occur.

You can have a catch all handler that fires not matter which type of exception is throw. Typically this used as the last catch block to catch any exceptions that your previous catch handlers missed. The syntax is `catch (...)` with the `...` being the parameter list for the 

- you don't have access to the exception object thrown in this case, but you can deal with the exception in the body of the catch-all block 


```
#include <iostream>
#include <string>

double calculate_mpg(int miles, int gallons) {
    if (gallons == 0)
        throw 0;
    if (miles <0 || gallons < 0)
        throw std::string{"Negative value error"};
    return static_cast<double>(miles) / gallons;
}

int main() {    
    int miles {};
    int gallons {};
    double miles_per_gallon {};   
    
    std::cout << "Enter the miles: ";
    std::cin >> miles;
    std::cout << "Enter the gallons: ";
    std::cin >> gallons;
    try {
        miles_per_gallon = calculate_mpg(miles, gallons);
        std::cout << "Result: " << miles_per_gallon << std::endl;
    }
    
    catch (int &ex) {
        std::cerr << "Tried to divide by zero" << std::endl;
    }
    catch (std::string &ex) {
        std::cerr << ex << std::endl;
    }
    std::cout << "Bye" << std::endl;

    return 0;
}
```

Notice how this code has two different catch handlers, one for each exception type. If C++ encounters an execption that we do not have a handler for, the code will terminate. We could also add a catch all handler if we want. The syntax for that would be:

```
catch (...) {
	std::cerr << "Unknown Exception Thrown" << std::endl;
}
```

### Stack Unwinding

- If an exception is thrown but not caught in the current scope (e.g. function, loop), C++ tries to find a handler for the exception by unwinding the stack
- For example: an exception is thrown in a function but not caught in that function
	- the function terminates (does not return) and is removed from the call stack
	- If a try block was used (i.e. if the function was called in a try block) then the catch blocks are checked for a match
	- If no try block was used OR if the catch handler doesn't match, then the stack unwinding occurs again
	- If the stack is unwound back to main and no catch handler handles the execption then the program terminates

- Remember that when a function is removed from (or popped off) the stack, all of its local variables are destroyed. 
	- This means that destructors are called for local objects
	- If we have free memory to delete then these `delete` statements may not execute and we will leak memory
	- This makes it critical that you implement classes that require resources as RAII classes (see smart pointers section)
	- Make sure to clean up your resources and destructors since you never know when they may be called

### Creating User-Defined Exception Classes

- We can create exception classes and throw instances of those classes
- Best practices for exceptions:
	- throw an object, not a primitive type
	- throw an (exception) object by value
	- catch an (exception) object by reference (or `const` reference)


#### Miles per Gallon Example:

##### Create the exception classes
```
class DivideByZeroException {
};

class NegativeValueException {
};
```

For this example, we are not putting any information about the exceptions in these classes. 

##### Throw those exceptions when needed in `calculate_mpg`

```
double calculate_mpg(int miles, int gallons) {
    if (gallons == 0)
        throw DivideByZeroException();
    else if (miles < 0 || gallons < 0)
        throw NegativeValueException();
    return static_cast<double>(miles) / gallons;
}
```

This code throws a `DivideByZeroException` if you attempt to divide by zero and throws a `NegativeValueException` if either miles or gallons are negative.

##### Catch those exepctions in `main`

###### Set up the program
```
int main() {    
    int miles {};
    int gallons {};
    double miles_per_gallon {};   
    
    std::cout << "Enter the miles: ";
    std::cin >> miles;
    std::cout << "Enter the gallons: ";
    std::cin >> gallons;
```

###### Call `miles_per_gallon` in a try block
```    
    try {
        miles_per_gallon = calculate_mpg(miles, gallons);
        std::cout << "Result: " << miles_per_gallon << std::endl;
    }
```

###### Two catch handlers - one for each exception type
```    
    catch (const DivideByZeroException &ex) {
        std::cerr << "Sorry, you can't divide by zero" << std::endl;
    }
    catch (const NegativeValueException &ex) {
        std::cerr << "Sorry, one of your parameters is negative" << std::endl;
    }
```

Notice that we are catching the exceptions by `const` reference


###### Terminate Function

```
    std::cout << "Bye" << std::endl;

    return 0;
}
```

### Class Level Exceptions

- Exceptions can be thrown from within a class in its methods, constructor, or destructor

#### Methods

Exceptions called in class methods work the same way as they do for functions

#### Constructors 
	
- constructors may fail and because constructors do not return values, we cannot return a Boolean or an error code
	- constructors may fail for many reasons (e.g. a constructor may try to open a file that does not exist)
- When a constructor fails and you cannot initialize an object, the constructor should throw an exception 

##### Constructor Exception Example

- Assume we have an `Account` class and we do not allow accounts with negative balances.
- Assume we have created an `IllegalBalanceException` class

```
Account::Account(std::string name, double balance) : name{name}, balance{balance} {

	if (balance < 0.0){
		throw IllegalBalanceException{};
	}
}
```

This constructor throws an `IllegalBalanceException` if we try to create an account with a negative balance

```
try {
	std::unique_ptr<Account> moes_account = std::make_unique<Checking_Account>("Moe", -10.0);
	std::cout << *moes_account << std::endl;
    }
    
catch (const IllegalBalanceException &ex){
	std::cerr << "Couldn't create account - negative balance" << std::endl;
}
```


#### Destructor

- Do **NOT** throw exceptions from your destructor
	- a destructor in C++ is marked by default as *no except* (it does not throw exceptions) 
	- If a destructor is called as the result of an exception and then the destructor itself throws an exception, then the original catch block (for the first exception) will never be reached - this is bad
	- The only time a destructor may throw an exception is if it also handles the exception, but this is very unlikely

### C++ Standard Exception Class Hierarchy

- C++ provides a class hierarchy of exception classes
- `std::exception` is the base class ([Documentation](https://en.cppreference.com/w/cpp/error/exception))
	- has a virtual function `what()` 
- all subclasses implement the `what()` virtual function
	- `what` returns a C-style string with a description of the exception that occured
	-  each subclass implements `what()` so that it displays whatever exception message we want
- We can create our own user-defined subclasses of `std::exception` 

```
virtual const char *what() const noexcept
```

The `noexcept` keyword tells the compiler that this method will not throw an exception.

- in case it isn't obvious, this means that you should not throw exceptions from any methods with the `noexcept` keyword
- If you do throw an exception from a `noexcept` method, the program will terminate and the exception will not be handled
- The destructor is `noexcept` by default. 


#### MPG Example 

```
class DivideByZeroException : public std::runtime_error  {
public:
    DivideByZeroException() : std::runtime_error {"Cannot divide by zero"}
    {}
};


class NegativeValueException : public std::runtime_error {
public:
    NegativeValueException() : std::runtime_error {"one of your parameters is negative"}
    {}
};
```

