## Section 13 - Object Oriented Programming

### Object Oriented Programming Overview

#### Background - Procedural Programming

- Focus is on processes or actions that a program takes
- Programs are typically a collection of functions
- Data is declared separately and passed as arguments into functions

##### Limitations of Procedural Programming

- Functions need to know the structure of the data - if the structure of the data changes, many functions must be changed
- As programs get larger they become more difficult to: understand, maintain, extend, debug, reuse code. It also makes the code more fragile and easy to break. 

#### Understanding Object Oriented Programming

- All about modelling your progam using **classes** and **objects**
- focus is on classes that model real-world domain entities
- allows developers to think at a higher level of abstraction
	- for example: instead of thinking in terms of *first name*, *last name*, and *credit card number* you can think in terms of a *customer* object 
- used successfully in very large programs

Encapsulation - objects contain both data and operations that work on that data

- extension of the Abstract Data Type


##### Infomration Hiding

- implementation-specific logic can be hidden - allows us to provide a public interface to the class and hide everything else
	- users of class code to the interface since they don't need to know the implementation
- more abstraction
- easier to test, debug, maintain, and extend



##### Reusability

Object oriented programming improves reusability of code between programs

##### Inheritability 

Can create new classes derived from an existing class. 

- allows for 

Example: Account class that contains information like the account holder name, account number, and interest rate.

- Trust account class - contains everything an account class does but also stores the Trustee information

#### Limitations of Object Oriented Programming

- won't make bad code good
- not everything decomposes to a class
- steep learning curve
- more up-front design required
- Programs can be larger, slower, and more complex

### Classes and Objects

#### Classes

- the blueprint from which objects are created
- a user-defined data type
- has attributes (data) and methods (functions)
- can hide data and methods
- provides a public interface that the user of the class can use to solve their problem

#### Objects

- created from a class
	- represent a specific instance of that class
-  each has its own identity
-  each can use the defined class methods


### Declaring a Class and Creating Objects

#### Declaring a Class

```
class Class_Name{

	// declaration(s);
	
};
```

- It is convention to capitalize the names of user-defined classes
- Dont forget the `;` at the the `}`
- Best to define a classes on their own

Example: A Player class from a video game

```
class Player {

	// attributes
	
	string name;
	int health;
	int xp;
	
	// methods
	
	void talk(string text_to_say);
	
	bool is_dead();
};
```

Detail of how to create methods comes later

#### Creating Objects

```
Player jack; // create an object from the Player class named jack
Player hero; // create an object from the Player class named hero

Player *enemy = new Player(); // dynamically create a new instance of Player named enemy on the heap
delete enemy;
```

We can use objects like any other variable in C++. For example, you can create an array of objects:

```
Player players[] {jack, hero};
```

### Accessing Class Members

- We can access class attributes and methods
- Some class members will not be accessible (more on that later)
- We need an object to access instance variables

We can use the dot operator to access attributes and methods of a class if we have an object

```
Account jack_account;

jack_account.balance;
jack_account.deposit(100.00); // access the deposit method for the 
```

If we have a pointer to an object, we need to dereference the pointer to use the dot operator (`.`)

```
Account *jack_account = new Account(); //jack_account is not an account object but a pointer to an account object

(*jack_account).balance; //dereference the pointer jack_account before you can get the balance
(*jack_account).deposit(100.00);
```

Or we can use the member of pointer operator (arrow operator) (`->`)

```
Account *jack_account = new Account();

jack_account -> balance;
jack_account -> deposit(100.00);
```

The dot operator (`.`) cannot be overloaded nor can it refer to pointers. The the arrow operator (`->`) can be overloaded and it is meant to be applied to pointers.


### Class Member Access Modifiers (Public, Private, Protected)



- `public` - accessible everywhere
- `private` - accessible only by members or friends of the class
	- if no class modifier is specified, then everything defaults to private 
	
- `protected` - very similar to `private` but differs with inheritance, more on this later

C++ uses the class memeber access modifiers for information hiding

- `private` allows you to control access to certain aspects of the object
- It is best practice to hide certain parts of your class designations

```
class Class_Name {

class_modifier:

	// declarations

}
```

Everything you declare after the class member access modifier will have that modifier applied to it unitl you see a different modifier.


```
class Class_Name
{

public:

	// everything here is public;

private:

	// everything here is private

protected:

	// everything here is protected
	
}

```

Example:

```
class Player
{
private:
	std::string name;
	int health;
	int xp;

public:
	void talk(std::string text_to_say);
	bool is_dead();
};


Player jack;

jack.name = "Jack"; // Compiler error (private)
jack.health = 1000; // Compiler error (private)
jack.talk("Hello"); // Okay - public

cout << jack.health << endl; // Compiler error - private prevents you to a
```

Methods in a class can access the private parts of the class:

```
class Player
{
private:
	std::string name;
	int health;
	int xp;

public:

	// The talk method is able to access the private value name
	void talk(std::string text_to_say){
		cout << name << " says " << text_to_say << endl;
	}
	bool is_dead();
};

jack.talk("Hello."); // outputs Jack says Hello.

```

### Implementing Member Methods

- Very similar to how we implemented functions
- Member methods have access to member attributes - you don't need to pass them as arguments
- Member methods can be implemented inside the class declaration 
	- implicity inline
	- typically used for smaller, simpler methods
- Member methods can be implemented outside the class declration
	- syntax: `Class_name::method_name`
	- typically used for larger and more complex methods
- Can separate specification from implementation - makes the class easier to manage
	- `.h` file for the declaration
	- `.cpp` file for the class implementation


#### Implementing Inside Class Delcaration

Example:
```
class Account{

private:
	double balance;

public:
	void set_balance(double bal) {
		balance = bal;
	}
	
	double get_balance(){
		return balance;
	}
};
```

Notice that the syntax is the same as it was for implementing functions. 

The methods have access to the private value `balance` because they are members of the same class.


#### Implementing Outside Class Delcaration

```
class Account{

private:
	double balance;

public:
	void set_balance(double bal); // Method prototype/declaration
	double get_balance(); // Method prototype/declaration
};

// Implement the methods

void Account::set_balance(double bal){
	balance = bal;
}

double Account::get_balance(){
	return balance;
}
```

Don't forget to prefix the methods with the class name (in this case `Account`) and the scope resolution operator (`::`).

#### Separating Specification from Implementation

As programs get larger, you want to separate class declaration and implementation into separate files.

##### Header Files

Create a file `Account.h` that provides the specification for the `Account` class. We will include this header file in our `.cpp` files whenever we need to include the account class.

```
class Account{

private:
	double balance;

public:
	void set_balance(double bal); // Method prototype/declaration
	double get_balance(); // Method prototype/declaration
};
```

If the `Account.h` file is included in more than one `.cpp` file, the complier will see the declaration for the `Account` class more than once and throw an error about duplicate delcarations.

To prevent this, we can use an **include guard** to ensure that the compiler only processes the header file once, no matter how many times it's included. 

###### Include Guard

The include guard is a series of pre-processor directives that guarantees the file will only be used once. 

We wrap our entire class in this include guard:

```
#ifndef _Account_H_
#define _Account_H_

// Account class declaration goes here

#endif
```

What this code is doing:

- `#ifndef _Account_H_` is checking the preprocessor to see if it has a symbol named `_Account_H_`. If the preprocessor already has a symbol named `_Account_H_`, then the program skips the entire file and goes to the `#endif` statement at the end. 
	- `#ifndef` means *if not defined* 
- If the preprocessor does not have a symbol named `_Account_H_`, then`#define _Account_H_` creates that symbol and the rest of the file is processed as usual. 

Best pratice for creating a symbol name is to use some sort of combination of the file name in uppercase with preceding and ending underscores. Any name is fine as long as it is unique in the program.


##### `#pragma once` Implementation

An alternative to the include guard is the `#pragma once` command. This is more elegant but not all compliers support it. 



###### Sample Header (`.h`) File

Using include guard

```
#ifndef _Account_H_
#define _Account_H_

class Account{

private:
	double balance;

public:
	void set_balance(double bal); // Method prototype/declaration
	double get_balance(); // Method prototype/declaration
};

#endif
```

Using `#pragma`:

```
#pragma once

class Account{

private:
	double balance;

public:
	void set_balance(double bal); // Method prototype/declaration
	double get_balance(); // Method prototype/declaration
};

```

##### Implementation (`.cpp` file)

This file implements the two methods declared in the `Account.h` header file.

```
#include "Account.h" //include the relevant header file

// Implement the methods

void Account::set_balance(double bal){
	balance = bal;
}

double Account::get_balance(){
	return balance;
}
```

- Notice that our `#include` statment uses double quotation marks rather than angle brackets (`<>`) around the `Account.h` file name. Notice that the `Account.h` file name includes the `.h` file extension. This is in contrast to things like `#include <iostream>`.

- `#include` with angle brackets and no extensions is used to include system header files. The complier knows where these files are located.
- `#include` with double quotes (`"`) tells the compiler to include header files that are local to this project. The compiler knows where those are.

##### Using our class in the `main.cpp` File

To use our separately defined class in the `main.cpp` file, then you need to have the `#include "Class_Name.h"` statement in your `main.cpp` file. (Note: Always `#include` `.h` files, never `.cpp` files). Then you can write your `main.cpp` file as you normally would.

In our example:

```
#include <iostream>
#include "Account.h"

int main(){
	Account jack_account; // create an instance of the Account classs
	jack_account.set_balance(100.00) // use the methods of the class
	
	...
	
	return 0
}
```

When the program is complied, both the `main.cpp` and the `account.cpp` files are complied and then linked to produce the executable.

### Constructors and Destructors

#### Constructor Overview

- Special member method
- invoted during object creation
- useful for initialization
- Have the same name as the class
- No return type specified
- can be overloaded


```
class Player
{
private:
	std::string name;
	int health;
	int xp;
	
public:
	// Overloaded Constructors
	Player(); // no args
	Player(std::string name);
	Player(std:: string name, int health, int xp);
};
```

#### Destructor Overview

- special member method
- Same name ast the class proceeded with a tilde (`~`);
- Invoked automatically when an object is destroyed
	- occurs when an object goes out of scope
- Does not require any arguments and does not return a value
- Only 1 destructor is allowed per class - cannot be overloaded
- Useful to release memory and other resources


```
class Player
{
private:
	std::string name;
	int health;
	int xp;
	
public:
	// Overloaded Constructors
	Player(); // no args
	Player(std::string name);
	Player(std:: string name, int health, int xp);
	
	// Destructor
	~Player();
};
```

#### Creating and Destroying Objects

```
{
// Create objects using constructor
Player slayer; // no args constructor of Player is called
Player jack {"Jack", 100, 4}; // full constructor called
Player hero {"Hero"}; // name only constructor called
// use the objects

} // When block ends these objects go out of scope - 3 destructors called automatically

player villian {"Villian"};
delete villian;

Player *enemy = new Player("Enemy", 1000, 0);
delete enemy; // destructor called

```

If you provide no constructor and no destructor, then C++ will automatially provide a default constructor and a default destructor that are empty

Using the `delete` keyword followed by the object will call the destructor for the object

#### Default Constructors

- does not expect any arguments - also called the no-args constructor
- If you write no constructors for a class then C++ will generate a default constructor that does nothing
- This is the constructor that is called when you instantiate a new object with no arguments

Example:

```
// Class with no constructors
class Account{

private:
	std::string name;
	double balance;

public:
	bool withdraw(double amount);
	bool deposit(double amount);
};


// Using the default constructor
Account jack_account; // created on stack using default constructor

Account *mary_account = new Account; // created on heap using default constructor

delete mary_account // destroy usin default destructors
```

It is best practice to provide a user-defined no args constructor. This will preempt the C++ compiler from creating default constructor. For example:

```
class Account{

private:
	std::string name;
	double balance;

public:
	bool withdraw(double amount);
	bool deposit(double amount);
	
	// User defined no-args constructor with default values
	// C++ will not create a default constructor
	Account() {
		name = "None";
		balance = 0.0;
	}
};

Accout jack_account; //Okay since we have a no-args constrctor
```

Once the programmer defines any constructor for a class, C++ will not generate the no args default constructor automatically. The programmer must provide a separate no-args constructor if they want it.

```
class Account{

private:
	std::string name;
	double balance;

public:
	bool withdraw(double amount);
	bool deposit(double amount);
	
	// User defined constructor with default values
	// C++ will not create a default constructor
	Account(std:: string name_val, double bal) {
		name = name_val;
		balance = bal;
	}
};

Account jack_account; //Error - no default constructor and no no-args constructor defined

Account *mary_account = new Account // Same error as above

Accoung bill_account {"Bill", 1400}; //OK - provides all the arguments the constructor expects
```

#### Overloading Constructors

- classes can have as many constructors as necessary
- Each must have a unique signature

```
class Player
{
private:
	std::string name;
	int health;
	int xp;
	
public:
	// Overloaded Constructors
	Player(); // no args
	Player(std::string name_val);
	Player(std:: string name_val, int health_val, int xp_val);
};
```

Implementing constructors:

```
//No-args constructor
Player::Player(){
	name = "None";
	health = 0;
	xp = 0;
}

// Name-only constructor
Player::Player(std::string name_val){
	name = name_val;
	health = 0;
	xp = 0;
}

// Full constructor
Player::Player(std:: string name_val, int health_val, int xp_val){
	name = name_val;
	health = health_val;
	xp = xp_val;
}
```

Creating objects using the constructors:

```
Player empty; //None, 0, 0 

Player hero {"Hero"}; //Hero, 0, 0

Player jack {"Jack", 100, 4}; //Jack, 100, 4

Player *enemy = new Player("Enemy", 1000, 0); // Enemy, 1000, 0
delete enemy;
```

It is important to initialize all class attributes so created objects do not have garbage data.

#### Constructor Initialization Lists

Constructor initialziation lists are very useful for efficiently initializing an object's data members.


* So far, we have written code so that we initialize our data member values in the constructor body by assigning values to them. This works, but isn't technically initialization because by the time the constructor body is executed, these member attributes have already been created. Really, we are just assigning values to already created attributes. 
* We want to have the member data values initialized to our values before the constructor body executes. This is much more efficient. To do this, we use constructor initialization lists.
* Constructor initialization lists are basically just a list of initializers immediately following the constructor parameter list.


```
class Player
{
private:
	std::string name;
	int health;
	int xp;
	
public:
	// Overloaded Constructors
	Player(); // no args
	Player(std::string name_val);
	Player(std:: string name_val, int health_val, int xp_val);
};
```

Assignment, not initialization

```
Player::Player(){
	name = "None";
	health = 0;
	xp = 0;
}
```

Using initialization constructor lists
```
Player::Player() : name{"None"}, health{0}, xp{0} {
}
```

The order in which the members are initialized is not necessarily the order we provide in the initializaion list - data members will be initialized in the order that they were declared in the class declaration.

Notice there is no code in the constructor body. There could be code in the constructor body but now we can be sure that our data members have been initialized to our own values.

```
Player::Player(std::string name_val) : 
	name{name_val}, health{0}, xp{0}{
}


Player::Player(std:: string name_val, int health_val, int xp_val)
	 : name{name_val}, health{health_val}, xp{xp_val}{
}
```

#### Delgating Constructors

- often the code for constructors is very similar
- Duplicated code can lead to errors
- C++ allows for delegating constructors - we can call another constructor in the same class in the initialization list.
	- this avoids duplicating code

Syntax: After the parameter list, write a colon and then follow it with the call to the constructor we wish to call.


```
class Player
{
private:
	std::string name;
	int health;
	int xp;
	
public:
	// Overloaded Constructors
	Player(); // no args
	Player(std::string name_val);
	Player(std:: string name_val, int health_val, int xp_val);
};

// Initialization List Constructors

Player::Player() : name{"None"}, health{0}, xp{0} {
}

Player::Player(std::string name_val) : 
	name{name_val}, health{0}, xp{0}{
}

Player::Player(std:: string name_val, int health_val, int xp_val)
	 : name{name_val}, health{health_val}, xp{xp_val}{
}
```

In the above example, the only difference between the initialization lists are the values used for initialization

Another way: Start with the full three-args constructor with a normal initialization list

```
Player::Player(std:: string name_val, int health_val, int xp_val)
	 : name{name_val}, health{health_val}, xp{xp_val}{
}
```

When we write the no-args constructor and the name-only constructor, we simply call the three-args constructor with the initialization data we need. These are called delegating constructors because they are delegating the initialization to another construction (in this case, the three-args constructor).

```
Player::Player() : Player {"None", 0, 0} {
}

Player::Player(std::string name_val) : Player {name_val, 0, 0}{
}
```

This only works in the initialization list. You can't call the other constructors from the body in the delgating constructors. You also can't delegate to another constructor and provide initialization values to class members.

#### Default Constructor Parameters

- We can reduce the number of overloaded constructors by using default constructor parameters
- Same rules apply as for default parameters for non-member functions
- Since a single constructor is doing the role of multiple constructors, you need to be careful not to have ambiguous constructors
	- if, in the example below, you also created a no-args constructor, the complier wouldn't know which constructor to call.

```
class Player
{
private:
	std::string name;
	int health;
	int xp;
	
public:
	// Constructor with default parameter values
	Player(std:: string name_val= "None",
			int health_val = 0,
			int xp_val = 0);
};

// implement constructor
Player::Player(std:: string name_val, int health_val, int xp_val)
	 : name{name_val}, health{health_val}, xp{xp_val}{
}


// Create class objects
player empty; // None, 0, 0
player jack {"Jack"}; // Jack, 0, 0
player hero {"Hero", 100, 55}; // Hero, 100, 55

```

#### Copy Constructor

When objects are copied, C++ must create a new object from an existing object.

A copy is made when:

- passing an object by value as a parameter
- returning an object from a function by value
- constructing one object based on another of the same class

C++ must have a way of accomplishing this - 


Pass by Value

```
Player hero {"Hero", 100, 20};

void display_player(Player p){
	// p is a copy of whatever Player object is passed in
	// in this example, that is hero
	
	// use p
	
	// Destructor for p will be called
}

display_player(hero)
```

Return a copy

```
// Return a copy
Player create_super_enemy(){
	Player an_enemy{"Super Enemy", 1000, 1000};
	return an_enemy; // a COPY of an_enemy is returned
}

Player enemy = create_super_enemy();
```

Construct one object based off another:

```
player hero {"Hero", 100, 100};
Player another_hero {hero}; //a copy of hero is made
```

C++ provides a default compiler-defined copy constructor if you don't provide one. 

- copies the values of each data member to the new object - default memberwise copy
	- this is perfectly fine in many cases

Beware if you have a pointer data member - the pointer will be copied, not what it is pointing to 

- this is called a shallow copy (more on this later)


##### Best Pratcies with Copy Constructors

- provide a copy constructor when your class has raw pointer members
- provide the copy constructor with a **const reference** parameter
- Use STL classes as they already provide copy constructors
- Avoid using raw pointer data members if possible

##### Declaring a Copy Constructor

```
Type::Type (const Type &source);
```

- It is a constructor, so it has the same name as the class
- The parameter list has a single object passed in of the same type
	- we pass that object in as a reference and as a constant
	- If we passed the object in by value, we would have to make a copy of it which defeats the whole point of creating a copy constructor
	- We pass it in as a `const` because we're copying the source, not modifying it

Example:
```
Player::Player(const Player &source);
```

##### Implementing the Copy Constructor

We can either write assignment statements in the constructor body or we can use initialization list

```
Type::Type (const Type &source){
	// code or initialization list to copy the object
}
```

```
Player::Player(const Player &source)
	: name{source.name},
	health {source.health},
	xp {source.xp} {
}
```

##### Shallow Copying with the Copy Construtor

- Assume the object we are copying has a raw pointer.
- When the object is constructed, we'll allocated storage for the data that the pointer is pointing to. When we are done with the data, we will release the memory using the destructor.

Shallow Copy is the default behavior provided by the compiler-generated copy constructor.

- Shallow copies do member-wise copying of all the object attributes
	- If one of your data types is a pointer, a shallow copy means the pointer is copied, **not** what it points to.
	- newly created object and the object being copied both point to the same area of storage in the heap  
- This creates issues when one of those objects is destroyed and its destructor is called. 
	- When this happens, the object's destructor releases the memory allocated on the heap.
	- The other object is still pointing to this released area and thinks the area is still valid
- We can use a shallow copy if all the class attribures are "copyable"

Example

```
class Shallow{
private:
	int *data; // Pointer

public:
	Shallow(int d); // Constructor
	Shallow(const Shallow &source); //Copy Constructor
	~Shallow(); // Destructor
};


// Shallow Constructor Implementation
Shallow::Shallow(int d){
	data = new int; // storage allocated dynamically
	*data = d;
}

// Shallow Destructor Implementation
Shallow::~Shallow(){
	delte data; // free storage
	cout << "Destructor freeing data" << endl;
}

// Copy Constructor
Shallow::Shallow(const Shallow &source) : data(source.data){
	cout << "Copy constructor - shallow" << endl;
}
```

This copy constructor provides the same semantics as the default copy constructor.

- In this copy constructor, only the pointer is copied - not what it is pointing to
- This creates a **problem**: `source` and the newly created object **both** point to the same `data` area

Example that will likely crash:

```
void display_shallow(Shallow obj); //Prototype

int main(){
	Shallow obj1 {100};
	
	// Pass obj1 to the function display_shallow(Shallow obj)
	// A copy of obj1 will be created inside that function
	display_shallow(obj1);
	// After display_shallow executes, obj1's data is released
	
	obj1.set_data_value)(1000);
	Shallow obj2 {obj1};
	
}
```

When the `Shallow` object `obj1` is passed to the function `display_shallow(Shallow obj)`, a copy of `obj1` will be created inside that function. When the function completes, the destructor is called on the copy of `obj1`. This releases the data for `obj1` as well as for the copy because both pointers are pointing to the same location in the heap. When we try to access that now-invalid memory, the program will probably crash. Also, when the destructor for `obj1` eventually is called, it will try to release memory that is no longer valid and probably will crash if it hasn't already.



##### Deep Copying with the Copy Construtor

- deep copy creates a copy of the pointed-to data itself
	- this is in comparison to a shallow copy, which copies the pointer to the data
- Each copy will have a pointer to unique storage in the heap 
- Deep copy when you have a raw pointer as a class data member


Example Class

```
class Deep{
private:
	int *data; // Pointer

public:
	Deep(int d); // Constructor
	Deep(const Deep &source); //Copy Constructor
	~Deep(); // Destructor
};


// Constructor Implementation
Deep::Deep(int d){
	data = new int; // storage allocated dynamically
	*data = d;
}

// Destructor Implementation
Deep::~Deep(){
	delte data; // free storage
	cout << "Destructor freeing data" << endl;
}

// Copy Constructor
Deep::Deep(const Deep &source){
	data = new int; // allocate storage
	*data = *source.data; // copy the data itself using dereferencing
	cout << "Copy constructor - deep" << endl;
}
```

The above `Deep` class is the same as the `Shallow` class until we get to the copy constructor. Where the copy constructor differs is that in `Deep`, it creates a unique copy of the original heap storage in each object.

Deep copy constructor - delegating constructor

```
Deep::Deep(const Deep &source) : Deep{*source.data}{
		cout << "Copy constructor - deep" << endl;
}
```

Delegate the copy to the constructor for `Deep`. That constructor (`Deep(int)`) expects an `int` value. The copy constructor passes the `int` `(*source.data)`, which is the data pointed to by `data`.


Example using deep copying - will not crash

```
void display_shallow(Deep s); //Prototype

int main(){
	Deep obj1 {100};
	
	// Pass obj1 to the function display_deep(Shallow obj)
	// A copy of obj1 will be created inside that function
	display_deep(obj1);
	// After display_deep executes, 	
	obj1.set_data_value)(1000);
	Shallow obj2 {obj1};
	
}
```

When the `Deep` object `obj1` is passed to the function `display_deep(Shallow s)`, a new object `s` that is a copy of `obj1` will be created inside that function. When the function completes, the destructor is called on `s`. `obj1` is not impacted because even though the data to which the pointers `s` point is the same as `ojb1`, the `s`'s data is located at a different spot on the heap. The storage being released is therefore unique to `s`. This means that even after `s` is destroyed, the data for the origional `obj1` is still there.

#### Move Constructors[^1]

[^1]: Feature was introduced in C++11.

- sometimes when we execute code the compiler creates unnamed temporary values.
	- In the example: `int total {100+200};` the steps the complier goes through is the following:

1. `100+200` is evaluated and `300` is stored in an unnamed temporary value
2. the `300` is then stored in the variable `total`
3. The temporary value is discarded


- The same happens with objects as well. 


When is it useful

- copy constructors are called whenver the compiler needs to make a copy of an object
	- sometimes copy constructors ace called many times automatically due to the copy semantics of C++ - there is often a lot of copying going on behind the scenes that you don't notice.
	- copy constructors doing deep copying can have a significant performance bottleneck
- The move constructor moves an object rather than copy it
	- this is much more efficient than copying 
	- This is optional but recommended 
- copy illusion - a complier optimization technique that eliminates unnecessary copying

##### Background: R-value and L-Value references

r-value references

- used in moving semantics and perfect forwarding
- move semantics is all about r-value references
	- think of it as references to the temporary values discussed previously 
- used by move constructor and move assignment operator to efficiently move an object rather than copy it
- R-value reference operator (`&&`)


```
int x {100}; // x is an l-value
int &l_ref = x; // l-value reference
l_ref = 10; // change x to 10

int &&r_ref = 200; //r-value ref
r)ref = 300; // change r_ref to 300 (change the temporary variable)

int &&x_ref = x; //compiler error - trying to assign an l-value to an r-value reference
```

L-value reference parameters

```
int x {100}; // x is an l-value

void func (int &num); // expects an l-value reference

func(x); // OK - x is an l-value
func(200) // Error - 200 is an r-value 

```

R-value reference parameters

```
int x {100}; // x is an l-value

void func (int &&num); // expects an R-value reference

func(x); // Error - x is an l-value
func(200) // OK - 200 is an r-value 
```

Can overload functions to accept both L-values and R-values

```
int x {100}; //L-value

void func(int &num);// A - expects an L-value
void func(int &&num); // B - expects an R-value

func(x); //calls A - x is an L-value
func(200); //calls B - 200 is an R-value

```

Move Class

```
class Move{
private:
	int *data; // Pointer

public:

	// Methods
	void set_data_value(int d) {
		*data = d;
	}	
	int get_data_value(){
		return *data;
	}
	
	// Constructors
	Move(int d); // Constructor
	Move(const Move &source); //Copy Constructor
	~Move(); // Destructor
};


// Copy Constructor Implementation - standard deep copy
Move::Move(const Move &source){
	data = new int; // allocate storage
	*data = *source.data; // copy the data itself using dereferencing
	cout << "Copy constructor - deep" << endl;
}
```

Inefficient copying:

```
Vector<Move> vec; // create a vector of Move objects

vec.push_back(Move{10});
vec.push_back(Move{20});
```

`Move{10}` and `Move{20}` are creating temporary, unnamed objects so they are going to be R-values. The compiler is going to use the copy constructor to make copies of these. 

##### How the Move Constructor Works

Instead of making a deep copy, the move constructor "moves" the resource. It does this by copying the address of the resource from `source` to the current object and nulls our the pointer in the source pointer. 

We now have an object who owns the data on the heap and then the original object with a null pointer to that data. Thi sis very efficient because we are not doing a copy at all.

##### Move Constructor Syntax

Very similar to the syntax for a shallow copy constructor but it has two differences.

1. no `const` qualifier for the paramter `source` - we need to be able to modify the source to null out its pointer
2. The paramter is an R-value reference (notice the `&&`).

```
Type::Type(Type &&source);
```

##### Implementing the Move Constructor

```
class Move{
private:
	int *data; // Pointer

public:

	// Methods
	void set_data_value(int d) {
		*data = d;
	}	
	int get_data_value(){
		return *data;
	}
	
	// Constructors
	Move(int d); // Constructor
	Move(const Move &source); //Copy Constructor
	Move(Move &&source); //Move Constructor
	~Move(); // Destructor
};
```

The move constructor "steals" the data and then nulls out the source pointer

```
// Move Constructor Implementation
Move::Move(Move &&source) 
	: data{source.data} {
		source.data = nullptr; // super important
}
```

##### Using the Move Constructor

```
Vector<Move> vec;

vec.push_back(Move{10});
vec.push_back(Move{20});

```

Move constructors will be called for the temporary R-values.

### The `this` pointer

- `this` is a reserved keyword
	- Contains the address of the object - so it's a pointer to the object currently being used by the class member methods
-  Can only be used in the class cope
- Python uses `self` keyword for the same thing
- All member access is done via the `this` pointer.
	- C++ allows you to use member names directly, but behind the scenes it's actuall using the `this` pointer 
- Can be used by the programmer 
	- to access data member and methods
	- to determine if two objects are the same
	- Can be dereferenced (`*this`) to yield the current object 


```
void Account::set_balance(double bal){
	balance = bal; // this->balance is implied
}
```

Use to disambiguate identifier use

```
// Bad
void Account::set_balance(double balance){
	balance = balance; // which balance? Ambiguous
}

// Good
void Account::set_balance(double balance){
	this->balance = balance; //Unambigous
}
```

Sometimes it is useful to know if two objects are the same object:

```
int Account::compare_balance(const Account &other) {
	if (this == &other){
		std::cout << "Same Objects" << std::endl;
		...
	}
}

jack_account.compare_balance(jack_account);
```

We will use the `this` when we oveload the assignment operator.


### Using `const` with Classes

- pass arguments to class methods as `const`
- We can also create `const` objects


Example: `*villain` is a const object so it's attributes cannot change

```
const Player villain {"Villain", 100, 55};
```

What happens is we call member methods on a const object?

```
villain.set_name("Nice guy"); //Error - trying to use a setter method to modify the object

std::cout << villain.get_name() << std::endl; //Error - compiler assumes that the method could change the object
```

```
void display_player_name(const Player &p){
	cout << p.get_name() << endl;
}

display_player_name(villain); //Error - get_name() method not expecting a const object. 
// Even if the object you pass in isn't a const, because the function makes it const then the error continues
```

Solution: we need to tell the compiler that certain methods will not modify the object. To do that, all we have to do is put the `cost` modifier before the `;` in the method prototype. 

example:

```
Class Player{
	private: 
		...
	public:
		std::string get_name() const;
		...
};
```

- compiler will allow this method to be called on `const` objects
	- can still call this method on non-`cost` objects 
- compiler will produce a compiler error if you try to modify any of the attributes in the method
- `const` methods having `const` qualifiers is referred to as const correctness
- Rule of thumb is that any method you have in your class that don't modify an object (such as any getter methods) should be `const`.


### Static Class Members

- class data members can be declared as `static`
	- tells compiler that this data membe belongs to the class, not the objects
	- useful for storying class-wide information
		- example: want to keep track of how many `Player` objects exist 
- Class functions can be declared as static
	- independent of any objects
	- can be called using the class name  

Example: Want to keep track of how many `Player` objects exist

Player.h

```
class Player{
private:
	static int num_players;
	...

public:
	static int get_num_players(); //static function prototype
	...
};
```

Player.cpp

```
#include "Player.h"

// initialize static variable. Must happen once and only once
int Player::num_players {0};

int Player::get_num_players(){
	return num_players;
}

// Update the Constructor - assume declared with default values

Player::Player(std::string name_val, int health_val, int xp_val}
	: name{name_val},
	health{health_val},
	xp{xp_val}
	{
		++num_players;
}


// Decrement in the Destructor

Player::~Player(){
	--num_players;
}

```

In the Player.cpp file

- Initialize the static variable in Player.cpp file. This must happen once and only once. 

- The function `get_num_players()` is static. This means it only has access to static data class members. 
- Best place to increment the player count is in the constructor
	- be careful if you have overloaded constructors. You may have to increment the static variable `num_players` in more than once place.
- Best place to decrement the player count is in the destructor


Using the static methods in main.cpp:

```
void display_active_players() {
    cout << "Active players: " << Player::get_num_players() << endl;
}

int main() {
    display_active_players(); // 2
    Player hero{"Hero"};
    display_active_players(); // 1
    return 0;
}

```

### Structs vs Classes

- In addition to defining a `class` we can declare a `struct`
- `struct` comes from the C programming language
- `struct`s are essentially the same as a `class` except its members are public by default


```
struct Name{
	...
}
```

General Guidelines:

- `struct` - holds data and is passive
	- use `struct` for passive objects with public access
	- don't declare methods in a `struct`
- `class`
	- use `class` for active objects with private access
		- have all data be private and implement getter/setters as needed 
	- implement member methods as needed   


### Friends of a Class

- Friend - a function or class that has access to a private class member, but is not a member of the class it is accessing
	- Functions can be regular, non-member functions or they can be member methods of another class
	- The class is another class that has access to private class members of the first class (the one granting friendship)
- Friendship must be granted explicitly
	- Friendship must be granted not taken - class must explicitly declare its friends in its class declaration using the `friend` keyword.
	- Friendship is not symetric - A being a friend of B does **not** require that B be a friend of A
	- Friendship is not transitive
		- if A is a friend of B and B is a friend of C, that does not make A a friend of C 
	- Friendship is not inherited
- Friendships should only be granted when it makes sense in the design of the system. Even then, only the minimal necessary friendship should be granted.


```
class Player{

	// make a stand-alone function a friend
	friend void display_player(Player &p) 	
	// make a method in another class a friend
	friend void Other_class::display_player(Player &p);
	
	// declare an entire separate class as a friend
	friend class Other_class;
}

```