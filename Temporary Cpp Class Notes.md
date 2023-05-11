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

If we have a pointer to an object, we need to dereference the pointer to use the dot operator

```
Account *jack_account = new Account(); //jack_account is not an account object but a pointer to an account object

(*jack_account).balance; //dereference the pointer jack_account before you can get the balance
(*jack_account).deposit(100.00);
```

Or we can use the member of pointer operator (arrow operator)

```
Account *jack_account = new Account();

jack_account -> balance;
jack_account -> deposit(100.00);
```

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
Player::Player(const Playe &source);
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

