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
