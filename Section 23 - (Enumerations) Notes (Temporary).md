## Section 23 - Enumerations

### Motivation

- an enumeration is a user-defined type that models a set of constant integral values
- Using enumerated types allows us to assign meaningful names to each of the integral values
	- an enumeration is a good way to define a type that holds a value representing a day of the week - once we create this enumeration type, that type can only be used to represent the days of the week 
	- Other examples: months of the year, states of a system
- Prior to enumerations, programs contained many unnamed numerical constants (AKA Magic Numbers) - resulted in algorithms suffing from low readability and high numbers of logic errors
	- magic numbers were often used in control statements (e.g. case/switch)
- By using enumerated types, we can impose a type restriction on variables and function return values


### Structure of an Enumeration

```
enum-key enum-name : enumerator-type {};
```

- many elements of an enumeration are optional, so you will often see enumerations without names, types, or attributes
	- we are not covering attributes
- Enumeration key (`enum-key`): defines beginning of the enumeration and the scope of the enumeration 
	- an enumeration can either be scoped or unscoped
	- enumeration always starts with the keyword `enum`
- Enumeration name (`enum-name`)
	- optional for unscoped enumeration
	- useful for imposing type restrictions of variables that you want to be an enumeration type - naming the enumeration allows you to impose type restrictions on variables
- Enumerator Type (`enumerator-type`) - serves as the fixed underlying type of the enumerations enumerators
	- optional (the compiler will try to guess) but can be used to reduce the amount of space an enumeration takes up in memory or to increase the accuracy of any calculations involving enumerator values
	- Specify type only when necessary
- Enumerator List `{ }` - where we define the names and the integral values of the enumerators belonging to the enumeration
	- this can be done explicilty or implicitly 

	
```
enum {Red, Green, Blue}
```  

- this example has no name or type
- none of the enumerators has been initialized

#### Enumeration Initialization

- The compiler can initialize the values for us (**Implicit Initialization**)
	- The compiler will assign the first enumerator a value of `0`.
	- For all other uninitialized enumerators, the compiler will assign it the value of the previous enumerator plus 1. So if the previous enumerator had a value of `10`, the compiler would assign it a value of `11`
	- In the above example `Red` is assigned `0`, `Green` is assigned `1`, and `Blue` is assigned `2`
	- If we want, we can assign values to the enumerators ourselves. This is called **explicit initializtion**

	```
	enum {Red = 1, Green = 2, Blue = 3}
	```

	- In certain cases we may only care about the values of some of the enumerators. In these cases we can explicitly assign values to certain enumerators and allow the compiler to implicilty assign values to the others. This is known as **explicit/implicit initialization**

	```
	enum {Red, Green = 3, Blue = 4}
	```
	

##### Important Note of Caution on Initialization

TL;DR: **best practice is to avoid assigning explcit values to your enumerators unless you have a compelling reason to do so**


The ability to do explicit and implicit enumeration allow for multiple enumerators to have the same value. In general, best practice is to avoid assigning explcit values to your enumerators unless you have a compelling reason to do so.  (One example of when it may be useful to explicitly assign values to an enumerator is matching a bar code number to an inventory item.)

For example, one can explicitly assign multiple enumerators the same value. The code `enum {Red = 1, Green = 1, Blue = 2` assigns both `Red` and `Green` the same value. This means the statment `Red == Green` returns `True` despite it feeling like it should be false. Assigning the same value to two enumerators should be avoided.

Remember that the compiler assigns the first enumerator a value of 0 (assuming it is not explicitly initialized) and assigns all other uninitialized enumerators a value of 1 greater than the enumerator directly prior to them in the enumerator list. In our implicit enumerator example `enum {Red, Green, Blue}`, the values were therefore `Red = 0`, `Green = 1`, `Blue = 2`. 

The combination of the rules for implicit enumeration and the ability to mix explicit and implicit enumeration can also lead to multiple enumerators having the same value without the programmer doing so explicilty.

```
enum my_enum {Red, Green = 0, Blue, Yellow = 1};
 
cout << boolalpha;
 
my_enum red = Red;
my_enum green = Green;
    
cout << "Does Red = Green?" << endl;
cout << (red == green) << endl; // returns true
    
my_enum blue = Blue;
my_enum yellow = Yellow;
 
cout << "Does Blue = Yellow?" << endl;
cout << (blue == yellow) << endl; // returns true
```

#### Eunumeration Types

- If the underlying type of the enumeration is not fixed, then the compiler assigns the first integral type that is able to hold the enumerations entire value range
	- If we try to fix an underlying type that cannot hold the enumerations entire range then the compiler will throw an error

#### Enumeration Names 

- nameless enumerations are often called **anonymous enumerations**
	- because anonymous enumerations have no name, it is not possible to declare variables of that enumeration type
	- The best we can do is declare a variable as the underlying type of the enumeration
	- While the variable can be assigned to the enumerators, it can also be assigned to any variable belonging to the underlying type. For example:
		
		```
		enum {Red, Green, Blue};
		
		int my_color;
		
		my_color = Green; // Valid
		
		my_color = 4; // also valid
		```

	- because of this, we say that anonymous enumerations provide no type safety

- Giving the enumeration a meaningful name that represents its enumerators allows us to restric variable assignment only to the enumerators of an enumeration 
- by providing a name, we are defining the enumeration as a unique type that can only assume its enumerated values

```
enum Color {Red, Green, Blue}
```

- in this code the name of the enumeration is `Color`
- naming the enumeration provides type safety

```
enum Color {Red, Green, Blue};

Color my_color;

my_color = Green; // Valid

my_color = 4; // not valid
```

- the name given to an enumeration should form an ***is a*** relationship with its enumerators
	- in our example: `Green` ***is a*** `Color` and so are `Red` and `Blue`

### Unscoped Enumerations

- an enumeration's key defines its scope
- The `enum` key implements an unscoped enumeration
	- Syntax for an unscoped enumeration: `enum enum_name : enumeratory_type {};`
- An unscoped enumeration means that the enumeration's enumerators are unqualified and they are visible throughout the entire scope in which the enumeration was declared
	- If we want to use an enumeration's enumerators, it is not necessary to specify which enumeration the enumerators belong to
	-  This can sometimes cause issues - you cannot have muleipole unscope enumerations that use the same variable name
	
	```
	enum Direction {North =1, South=10, East, West };
	
	enum Street {Main, North, Elm};   // Error, can't use North again
	```


#### Common use of unscoped enumerations 

- conditionals and control structures such as if and switch statements 

	```
	State state = get_state();
	
	switch (state) {
		case Engine_Failure: // Abort if Engine Failure
		case Unknown:  // or Unknown!
			initiate(Abort); 
			break;
		case Inclement_Weather:    
			initiate(Hold); 
			break;
		case Nominal:              
			initiate(Launch); 
			break;
		}    
	```
	
	- We can only implement switch statements with enumerations as long as the enumerators we use as switch cases have unique values

#### Using `cin` and `cout` with unscoped enumerations

- [Learn CPP on Unscoped Enumeration Input and Output](https://www.learncpp.com/cpp-tutorial/unscoped-enumeration-input-and-output/)


##### Using `cin`

- we cannot use the standard `cin` command with the extraction operator (`>>`) because the extraction operator has no knowledge of what a `State` type variable is or how to deal with it
- We have 2 methods to deal with this:
	- extract the user input value into a type that the extraction operator does know about and then cast it to a `State`-type
		- For example, `enum State {Failure, Weather, Nominal}` has an underying type `int`.  
		- We can have the user input an `int` and then cast it to a `State`-type variable

		```
		std::underlying_type_T<State> user_input;
		std::cin >> user_input
		State state = State(user_input);
		```
		
		- using the class template `underlying_type_T` deduces the underlying type of the enumeration for us
		- When we cast enumeration types, the value of the variable does not change - you are responsible for ensuring that a variable cast to an enumeration type will have a valid enumerator value.
	
		
	- Overload the extraction operator to deal with `State`-type variables 
		- take as parameters: (1) a refernce to the input stream (`std::istream & is` in the code below) and (2) a reference to the state variable that the user input will be read into (`State &state` in the code below)

		```
		std::istream &operator>>(std::istream &is, State &state) 
		```
		
		```
		enum State {Engine_Failure, Inclement_Weather, Nominal};
		
		std::istream &operator>>(std::istream &is, State &state) 
		{
		    // int user_input;   // Will also work
		    std::underlying_type_t<State> user_input;
		    is >> user_input;
			
		    switch (user_input) {
		        case Engine_Failure:       
		        case Inclement_Weather:
		        case Nominal:
		            state = State(user_input);
		            break;
		        default:                   
		            std::cout << "User input is not a valid launch state." << std::endl;
		    }
			
		    return is;
		}
		```
	
		- It is important that we declare the enumeration in the same scope as any function referencing the enumeration or its enumerators. This is to ensure that the enumeration type and the enumerators can be accessed from within the function
		- In this case, we have declared the state enumeration in the same global namespace that contains the overloaded extraction operator function
		- Within the function: 
			- we have declared a temporary user input variable as with the same type as the underlying type of the enumeration (`std::underlying_type_t<State> user_input`)
			- The user's input is extracted from the input stream and assigned to the temporary variable
			- The variable is then checked to ensure that its value corresponds to a valid state enumerator
				- If so, the temporary variable is cast to the reference state varaible 
				- If not, a message is displayed to the user informing them that they have not entered a valid state
			- The input stream `is` is returned to the calling function
	- Both these methods are identical, but overloading the extraction operator makes for much cleaner code


##### Using `cout` with enumerations

- To display enumeration type variables, we can use the standard `cout` and the insertion operation (`<<`).
	- When we do so, the enumeration type variable is implicilty converted to its underlying type and its value is displayed
	- This means that when we display the neumeration type variables, it is their value that is displayed, not their name.
		- Remember: an enumerator's name is not a string, but is simply a namne used to identify its value within the code 

	```
	enum State {Failure, Weather, Nominal};
	
	State state = Failure;
	std::cout << state; // Displays 0
	``` 

- Sometimes it may be useful to display the name of the enumeration type variable
	- to accomplish this we an implement a switch statement using the variable as the condition and its cases being the enumerations enumerators
	- We can also implement this functionality by overloading the insertion operator

	```
	enum Grocery_Item {Milk, Bread, Apple, Orange};

	std::ostream &operator<<(std::ostream &os, const Grocery_Item &grocery_item)
	{
		switch (grocery_item) {
		    case Milk:      
	            os << "Milk"; 
	            break;
			case Bread:     
	            os << "Bread"; 
	            break;
			case Apple:     
	            os << "Apple"; 
	            break;
			case Orange:    
	            os << "Orange"; 
	            break;
			default:        
	            os << "Invalid item"; 
		}
		return os;
	}
	``` 
	
	- `std::ostream &os` is a reference to the output stream
	- `Grocery_Item &grocery_item` is a reference to the `Grocery_Item` variable whose name will be displayed


### Scoped Enumerations

- scoped enumerators are qualified and they are only visible by using the scope resolution operator (`::`)
- If we want to access an enumeration's enumerators, we must specify the specific enumeration to which the enumerator belongs
- Syntax for declaring a scoped enumeration:
	- `enum class enum_name : enumerator_type { };`
	- `enum struct enum_name : enumerator_type { };`
	- Both `enum class ...` and `enum struct ...` are semantically equivalent

#### Motivation

##### Keep types distinct

Scoped enumerations are useful for when you have distinct types that you want to keep separate.

Unscoped enumerations can compare things that are not alike. 
```
enum Whale {Blue, Beluga, Gray};
enum Shark {Greatwhite, Hammerhead, Bull};

if (Beluga == Hammerhead){
	std::cout << "A beluga whale is equivalent to a hammerhead shark.";
}
```

##### Prevent Name Clashes

Scoped enumerations are useful for preventing name clashes

```
enum Whale {Blue, Beluga, Gray};
enum Shark {Greatwhite, Hammerhead, Bull, Blue};
```

Because both enumerators are unscoped, you cannot have two enumerators with the name `Blue`. This code will not compile because it thinks we are trying to redeclare the name `Blue`.

#### Using Scoped Enumerations

- Using if and switch statements with scoped enumerations is idential to that of unscoped, ut with the additional requirment of specifying enumerator scopes. 

- Everything you do with unscoped enumeration, you can also do with scoped enumeration so long as you specify the scope of its enumerators

```
enum class Mode {Attack, Defense, Idle};

Mode mode = Attack

switch (mode) {
    case Mode::Attack
        result = "Attack"; 
        break;
    case Mode::Defense:
        result = "Defense";
        break;
    case Mode::Idle:
        result = "Idle";
        break;
};

```


##### Using Scoped Enumerator Values

```
enum class Grocery_Item {Milk=350, Bread=250, Apple=132, Orange=100}; //underlying type: int
```

- With unscoped enumerations, if we wanted to use the enumerator values, we simply stated the name of the enumerator and the compiler would implicitly convert its value to the underlying type. 
- With scope enumerations, this implicit conversion is not possible and will generate a ompiler error
- Scoped enumeration type variables are not implicilty convertable and we must instead be explicitly cast the variable to its underlying type 
	- only then can we use the value of a scoped enumeration type variable 