# C++ Class Notes

## Section 5 - Structure of a C++ Program

### Syntax Terms

- keywords are reserved (programmer cannot redefine their meaning)
	- [list of c++ keywords](https://en.cppreference.com/w/cpp/keyword)
	- examples of keywords: `int`, `return`
- Identifiers: something that the programmer names that represents something meaningful to them. Examples of identifiers include function names and variables.
- Operators: An operator in a programming language is a symbol that tells the compiler or interpreter to perform specific mathematical, relational or logical operation and produce final result.
 
 
 ### Preprocessor
- C++ preprocessor is a program that processes your source code before the compiler sees it. The preprocessor
	- strips all comments from the code
	- Executes **preprocessor directives** then removes them from the source code
- Preprocessor directives are lines in source code that begin with a `#`, examples include `#include`
	- Preprocessor directives are often used to include certain libraries or to conditionally compile code. (E.g. you only want to compile certain piles of code
	- **The C++ preprocessor does not understand C++**

### Comments
Comments are programmer-readable notes in the source code. They are often used to explain or annotate code.

- Note: comments never make it to the complier. They are stripped out by the preprocessor.

Styles of comment:

- single line comment. Indicated by `//`
- multi-line comment. Multi-line comments are started with `/*` and ended with `*/`.
	- multi-line comments are typically used to create a header at the top of the code 

Commenting best practices:

- your code should be "self-documenting". Your code should make sense. Use comments to explain code that aren't obvious
- Keep the style of the comments consistent 
- Good commenting doesn't justify bad code
- Don't use comments as version control

### main() function

- Every C++ program must have one `main()` function somewhere.
- When the C++ program executes, the operating system runs `main()`
- If the return value is 0, then the program terminated successfully. If the return value is not 0, then the OS can check the return value and use it to determine what went wrong.
	- `main` must always return an integer
- Two versions of a `main` function. One takes no arguments and the other takes arguments
	- If ```main``` takes in no arguments, then it doesn't expect any information from the operating system.
	- If `main` has arguments, that means it expects arguments from the OS when it is called. `main` will  be in the format `main(int argc, char *argv[])` where
		- `argc` is the number of arguments that `main` expects.
		- `*argv[]` is the argument vector that are the values of the 
		- a program that expects arguments will be called from the command line using the syntax `program.exe arg1 arg2 ...`

### Namespaces

- Namespaces help avoid naming conflicts between functions of the same name. 
- `std` is the name for the C++ 'standard' namespace
- `::` is the scope resolution argument. It is used to specify a namespace. For example to use command `xyz` from namespace `abc`, you would write `abc::xyz`. 
	- It is the equivalent of python's `abc.xyz`.
- `use namespace abc` calls the entire abc namespace. This means that you don't have to type `abc::` before calling any method from that namespace. This is the equivalent of python's `from abc import *`.
	- This can be risky because it increases the risk of naming conflicts
- `using abc::xyz` only brings in the `xyz` method from `abc`. It is the equivalent to Python's `from abc import xyz`.

### Basic I/O using `cin` and `cout`

- `cout` - standard output stream, defaults to console
- `cin` - standard input stream, defaults to keyboard
- `<<` - insertion operator, used with output streams
- `>>` - extraction operator, used with input streams

#### output: `cout` and `<<`
- `<<` inserts the value of the operand to its right into the `cout` output stream

Example: `cout << data` inserts the variable `data` into the `cout` stream

- can chain multiple insertions in the same statement

Example: 
`cout << "data 1 is " << data1;` pushes "data 1 is [value of data 1]" to the console

- insertion operator does not automatically add line breaks. 
	- need to add new line operator (`endl`) or add new line character (`"\n"`)
	- new line operator will also flush the stream


#### input: `cin` and `>>`
- extraction operator (`>>`) extracts information from the `cin` input stream and stores the information in the variable to the right of the operator

Example: `cin >> data'` assigns the value of the (keyboard) input to the variable `data`. The way that the information is interpreted is based on the type of the variable.

- extraction operators can be chained

Example: `cin >> data1 >> data2` assigns the value of the input to the variables `data1` and `data2` basd on their respective types. If, for example, the input from they keyboard is `1` and `data1` is an integer but `data2` is a string, then `data1` will store the integer 1 but `data2` will store the string `"1"`.

- Can fail if the entered data cannot be interpreted
- trailing white space is interpreted as meaning the input is done, but it doesn't clear the buffer. Need to be careful

**Note:** I am confused on how `cin` and white space interact

- white space is ignored (?)
<!--I am unclear if the following is true: - Characters entered using the keyboard will only be processed when the *enter* key is pressed. `cin` also treats white space like hitting *enter*.-->

## Section 6 - Variables and Constants

### Variables

#### Computer Structure
- A computer has memory, a CPU, and a bus that allows the movement of data between them
- RAM is a contiguous block of storage, can be thought of as having memory cells where each cell has an associated location
- Most programming languages allow you to associate a name with a memory location

#### Variable Overview
A variable is an abstraction for a memory language that allow programmers to use meaningful names and not memory addresses.

- Variables have a type (e.g. integer, string, etc.) and a value (e.g. 10, "Text", etc.).
	- The type of the variable must be declared before they are used. 
		- you can use object-oriented programming to create your own variable types
	- The value of a variable may change

#### Naming Rules
- can contain letters, numbers, underscores
- must begin with a letter or an underscore.
	- can **never** begin with a number
- cannot use C++ reserved keywords
- Cannot redeclare a name in the same scope.
- be consistent with your naming conventions
	- your organization may have a style guide
	- use either Camel Case or underscores to separate words. Choose one and stick with it
- avoid beginning names with underscores
- Use meaningful names - not too long or too short
	- make sure your variable names are very descriptive 

[C++ Variable Naming Conventions](https://www.geeksforgeeks.org/naming-convention-in-c/) 

#### Declaring and Initializing Variables

- Best practice to declare a variable near where you first use is.
- Don't use a variable before initializing it. This will cause problems.

`int age;` - uninitialized

Multiple ways to initialize a variable that are all valid:

- `int age = 21;` - C-like initialization
- `int age (21);` - Constructor initialization
- `int age {21};` - C++11 list initialization syntax
	- This is probably the best way to start
	- List initialization helps catch overflow errors

Note: remember that C++ is case sensitive

#### Global Variables
- global variables are automatically initialized to `0`.
- gloabl variables can be accessed by any part of the program
- if there is a local variable with the same name as the global variable, the compiler will use the local variable
- best practice is to avoid global variables when possible

#### C++ Fundamental Data Types

[C++ Variable Types](https://cplusplus.com/doc/tutorial/variables/)

- the size and precision of C++'s primitive data types are largely dependent on the platform you're working on and the complier you are using
- `# include <climits>` should have the size and precision of the data types for your specific compiler
- The more bits allocated to a type, the more values that can be represented and the more storage required
	- need to be careful about overflow 

###### Character
- used to represnt single characters
- Basic `char` data type is 8 bit, but can be bigger if necessary
- C++ uses single quotes (not double quotes) for the single `char` type
	- double quotes makes it a string

###### Integer
- used to represent whole numbers
- both signed and unsigned integers are supported
- different types depending on size/precision needed and if signed or unsigned is need
- by default, all integers are signed

###### Float
- `double`

###### Boolean
- `0` is False
- Anything non-zero is True

#### `sizeof` operator
- the `sizeof` operator tells you the size in bytes of a type or a variabs


### Constants
- constants cannot have their value changed once declaired
	- useful for 
- Like C++ variables, constants have names, occupy storage, are (usually) typed

#### Types of Constants
- literal constants
	- do not refer to variables, they are the values themselves

in the expresion: `const int z {5};`, `z` is a constant and `5` is in integer literal

- declared constants (`const` keyword)
	- `const int months_in_year {12};` 
- constant expressions (`constexpr` keyword)
- enumerated constants (`enum` keyword)
- Defined constants (`#define`)
	- used in legacy C++ code. Don't use in Modern C++ 

## Section 7 - Arrays and Vectors

### Arrays

* An array is a compound data type or data struture - a collection of elements
* All elements must be of the same time (`int`, `double`, etc.)
* Each element can be accessed directly

#### How Arrays Work
- the name of the array represents the location of the first element in the array

```
int numbers [10] {0};
cout << numbers << endl;
```

will output a hexidecimal number corresponding to the memory address.


- The index represents the offset from the beginning of the array
- C++ performs a calculation to find the correct element. Remeber, no bounds checking. 

#### Characteristics of an Array

* Fixed Size
	* if you do not know how many elements you will need to have in your array, then you can make the array large enough that you are not likley to exceed the size
* Ordered
* Elements are all the same type (`int`, `double`, etc.)
* Stored contiguously in memory
* Individual elements can be accessed by their position or index
	* First element at index 0
	* Last  element at index $n-1$
*  Arrays do not check to see if you are out of bounds - if you go over bounds, 
*  Arrays are very efficient
*  Arrays are not commonly used in modern C++

#### Declaring and initializing arrays

Best practices it to initialize arrays when you declare them

##### Declaring: 
###### Format
```
Element_Type array_name [constant integer number of elements]
```

The complier must know the number of items in the array at compile time. The array cannot be sized based off a changing value in the program. 

###### Examples
`int test_scores [5]` creates an array of five elements with the name *test_scores*

```
const int days_in_year {365};  // Creates a constant with the value 365

double hi_temp [days_in_year]; // Creates an array of doubles with the number of elements equal to days_in_year
```

##### Initializing: 
###### Format
```
Element_Type array_name [constant integer number of elements] {init list}
```

This creates an array named *array_name* made up of $n$ elements of type `Element_Type` and that have the values found in the initialization list `{init list}`.

The complier must know the number of items in the array at compile time. The array cannot be sized based off a changing value in the program.

If you have an array of size $n$ and `{init list}` has $m$ elements (where $m < n$), then the first $m$ elements of the array will correspond to the values in `{init list}` and the $m + 1$ to $n$ elements will be initialized to $0$. 

###### Examples
`int test_scores [5] {100, 95, 99, 87, 88};` creates an array of five elements with the name *test_scores* whose elements are the integers *100, 95, 99, 87*, and *88* in that order. 

`int high_score_per_level [10] {3, 5};` creates an array of **10** integers with the name *high_score_per_level*. The first two elements of the array are *3* and *5* and the remaining elements are *0*.

`double hi_temp [days_in_year] {0};` Initializes all the values in the array to 0

`double hi_temp [days_in_year] {};` Initializes all the values in the array to 0

`int another_array [] {1, 2, 3, 4, 5};` If all the elements of the array are provided when compiling, then the size of the array can be automatically calculated  

#### Array Elements

##### Accessing 

```
array_name [element_index]
```

For example, `my_array [4]` would access the fifth (don't forget we are indexing from 0) element in the array *my_array*

##### Reassigning

```
array_name [element_index] = new_value
```

This assigns the chosen element in the array a new value. Note the new value must be of the same `type` as the array.

#### Multi-Dimensional Arrays

##### Initializing and Declaring
```
Element_Type array_name [dim1_size][dim2_size]{init list}
```

For multi-dimensional arrays, the `{init list}` is a list of lists

###### Example

```
int movie_rating [3][4] {
	{0, 4, 3, 5},
	{2, 3, 3, 5},
	{1, 4, 4, 5}
};
```

##### Accessing
To access the nth row and mth column of a 2x2 array, the syntax is: `array_name [n][m]`. This syntax can be extended to arrays of arbitrarily many dimensions




### Vectors

#### Characteristics of Vectors

- Vectors are dynamic arrays meaning they can grow and shrink in size at execution time
- Very efficient
- Vector elements are indivdually accessable
	- Index starting from 0
- No built-in out of bounds checking, but their are functions to do bounds check
- Can use functions like sort, reverse, find, and more
- Vectors are objects 
	- similar syntax to arrays, but slightly different



#### Declaring and Initializing

- Must include the `<vector>` library using the `#include <vector>` preprocessor directive
	- vector types are part of the standard (`std`) library - must use the `std` namespace or the scope resolution operator (`::`). 

##### Syntax

```
vector <type> vector_name;
```

- Do not need to declare the number of elements in the vector
- For vectors containing `integer` and `float`/`double` types, the vector will auto-initialize all elements to 0 if there is not an initialization list 
- There are many other ways to declare vectors


###### Examples

`vector <char> vowels {'a', 'e', 'i', 'o', 'u'};` creates a vector whose initial elements are *a*, *e*, *i*, *o*, and *u*.

`vector <double> hi_temperatures (365, 80.0);` creates a vector that initially has 365 entires all with a value of 80.0.


#### Accessing vectory elements and vector methods

- When you add elements to a vector, you make a copy of what you are inserting

##### Array Syntax

`vector_name [element_index]`

##### `at` method: `vector_name.at(element_index)`

- this is a method in the `vector` object
- the `at` method does provide bounds checking during runtime
 
##### `push_back` method

`vector_name.push_back(new_element)`: appends *new_element* to the end of the vector
- remember: `type(element)` must be the same as all the elements already in the vector

##### `size` method

`vector_name.size()`: tells you how many elements are in the vector

#### Multi-Dimensional Vectors

- a mult-dimensional vector is a vector of vectors

```
vector <vector <int>> movie_ratings {
	{0, 4, 3, 5},
	{2, 3, 3, 5},
	{1, 4, 4, 5}
};
```

- can use array syntax, or the `at` method to access an element

`movie_ratings[2][3]` and `movie_ratings.at(2).at(3)` both access the element in the 3rd row and 4th column of *movie_ratings*.

[Initializing Vectors](https://www.freecodecamp.org/news/cpp-vector-how-to-initialize-a-vector-in-a-constructor/)

## Section 8 - Expressions, Statements, and Operators 

### Expressions

- most basic building blocks in programming
- a sequence of operators and operands that compute a value

### Statements and Block Statements

- a complete line of code that performs some action
- usually terminated with a semi-colon


Examples: declaration, assignment, expression, if statement

### Operators

- assignment operator `=`: assigning the right hand side of an expression to the left hand side of an expression. 
	- the statement `a = 10;` assigns the value of 10 to the variable `a`.
	- Do not confuse assignment with initialization. Assignment changes the value of an existing variable.
		- l-value - the contents of a value
		- r-value - the location of that variable
	- can chain expressions together: `a = b = 10;` assigns 10 to `b` and returns `10`, it then assigns 10 to `a`
		- assignment operators and expressions return the value that was assigned
		- assignment operators and expressions associate right to left 
		- chaining is generally not a good idea
- arrethmatic operators (`+`, `-`, `*`, `/`, `%`)
	- no built-in exponential operator
	- Modular operator (`%`) only works with integers
	- be careful when doing division with integers - C++ will always truncate off any decimal that occurs in operations between two integers. 
	- For example:


	```
	5/10 // Ouputs 0
	
	5.0 / 10.0 // Outputs 0.5
	```
	 
	- Order of operations is still PEMDAS

#### Increment and Decrement Operator

##### Increment Operator (`++`)

- means: increase value by 1
- can be used with integers, floating point numbers, or pointers
- Prefix notation: `++num` - increment variable before you use it
	- Example 1:

		```
		counter = 10		
		result = ++counter
		
		cout << counter << endl; // outputs 11
		cout << result << endl; // outputs 11
		``` 	 
	- Example 2:
		
		```
		result = ++counter + 10;
		```
		
		Is the equivalent of saying
		
		```
		counter = counter + 1;
		result = counter + 10;
		```
		
		Meaning, in the example:
		
		```
		counter = 10		
		result = ++counter + 10
		
		cout << counter << endl; // outputs 11
		cout << result << endl; // outputs 21
		``` 	
		
- Postfix notation: `num++` - increment variable after you use it
	- Example 1: 	

		```
		counter = 10		
		result = counter++
		
		cout << counter << endl; // outputs 11
		cout << result << endl; // outputs 10
		``` 	
		
	- Example 2:
		
		```
		result = counter++ + 10;
		```
		
		Is the equivalent of saying
		
		```
		result = counter + 10;
		counter = counter + 1;
		```
		
		Meaning, in the example:
		
		```
		counter = 10		
		result = counter++ + 10
		
		cout << counter << endl; // outputs 11
		cout << result << endl; // outputs 20
		``` 	
		
		
		--
	
- Be careful with this operator. 
- Don't use twice with the same variable in the same statement


#### Decrement Operator (`--`):

same as the increment operator except it decreases value by 1

### Mixed Type Expressions
- C++ operations occur on the same type operands - if operands are of different types, C++ will convert one
	- Be careful of this. It could affect calculation results
	- C++ will attempt to automatically convert types. If it can't, a complier error will occur

#### Conversions
- Higher vs. lower types are based on the size of the values the type can hold
	- `long double` > `double` > `float` > `unsigned long` > `long` > `unsigned int` > `int`
	- `short` and `char` types are always converted to int
- Type Coercion : conversion of one operand to another data type
	- promotion: conversion to a higher type (the lower types value should fit into the higher types value)
		- used in mathematical expressions
		- Example: doing math with a double (`beta`) and an integer (`alpha`)

		```
		int alpha {5};
		double beta {10};
		
		cout << alpha / beta << endl; \\ outputs the double 0.5
		cout << alpha + beta << endl; \\ outputs the double 15
		```
			
	- Demotion: conversion to a lower type
		- Used with assignment to a lower type   

		Example: assigning a double literal (`1.5`) to integer variable (`alpha`).

		```
		int alpha {0};
		
		alpha = 1.5;
		
		cout << alpha << endl \\ outputs the integer 1
		```
		
	- Explicit Type Casting - static_cast<type>

		```
		int total_amount {100};
		int total_number {8};
		double average {0.0};
		```
		
		```
		average = total_amount / total_number;
		cout << average << endl;  // displays 12
		```
		
		Even though `average` is a double, it only displays 12 because `total_amount / total_number` is dividing two integers division, leading to the truncated result 12. This code could be rewritten as:
		
		```
		int temp {0};
		temp = total_amount / total_number
		
		cout << temp << endl; // outputs 12
		
		average = temp;
		cout << average << endl; // outputs 12
		```
		
		You can use `static_cast<type>(variable)` to convert one data type to another.
		
		```
		average = static_cast<double>(total_amount) / total_number;
		cout << average << endl;  // displays 12.5
		```
		
		In this case, `static_cast<double>(total_amount)` converts `total_amount` from an `int` into a `double`. This means that the subsequent division `total_amount / total_number` is not dividing to integers but rather dividing a double by an integer. This causes `total_number` to get promoted to a double as well. The resulting output is therefore a double. `static_cast<type>` is a cleaner way of doing:
		
		```
		int total_amount {100};
		int total_number {8};
		double average {0.0};
		
		double total_amount_double = total_amount; // create a double type variable with the same value as total_amount
		
		average = total_amount_double / total_number;
		
		cout << average << endl;  // displays 12.5		
		```

### Comparison Operators

| Operator | Meaning                  |
|----------|--------------------------|
|    ==    | Equal To                 |
|    !=    | Not Equal To             |
|     >    | Greater Than             |
|     <    | Less Than                |
|    >=    | Greater Than or Equal To |
|    <=    | Less Than or Equal To    |

These operators compare the left side of the expression to the right side of the expression and see if the comparison is true or false. The result is the corresponding boolean.

For example: `a == b;` outputs true (`1`) if `a` and `b` have the same value and outputs false (`0`) if `a` and `b` do not have the same value.

- you can compare two values of different types (e.g. a `double` and an `int`). This is because the `int` gets promoted to a `double`
- when comparing doubles, be careful about approximations of numbers:`12.0 == 11.999999999999999999` may return `true` because of how computer approximate floating point numbers
- You can use `boolalpha` command to convert the ouput from `0` and `1` to `false` and `true`. The `noboolalpha` command converts the output from `false` and `true` to `0` and `1`. These commands are located in the `std` namespace. 

```
cout << (num1 == num2) << endl; // displays 0 or 1

cout << std::boolalpha; 
cout << (num1 == num2) << endl; // displays true or false

cout << std::noboolalpha;
cout << (num1 == num2) << endl; // displays 0 or 1
```

- `<=>` is a three-way comparison operator that was introduced in C++20. `a <=> b` outputs:
	- a value less than zero if `a` is less than `b` 
	- a zero (0) if `a` is equal to `b` 
	- a value greater than zero if `a` is greater than `b` 

### Logical Operators

NOT, AND and OR

- Operate on boolean expressions and evaluate to a boolean operator themselves
- each operator can be written by its keyword syntax or using the operator symbol syntax 
	- most code uses the operator syntax

| Operator    | Keyword Syntax | Operator Syntax |
|-------------|----------------|-----------------|
| Logical NOT | not            | !               |
| Logical AND | and            | &&              |
| Logical OR  | or             | \|\|            |


Precedence (Order of Operations)
- `not` has higher precedence than `and`, which has higher precedence than `or` (`not` > `and` > `or`)
	- to be safe, use parenthesis to make sure that your meaning is clear 
- `not` is a unitary operator
- `and` and `or` are binary operators

```
alpha >= 10 && alpha < 20 // returns true if 10 <= alpha < 20
```

**Short-Circuit Evaluation:** when evaluating a logical expression C++ stops as soon as the result is known

Examples:

```
// expr1, expr2, expr3 are expressions that evaluate to booleans
expr1 = false
expr2 = true
expr3 = true

expr1 && expr2 && expr3 

```

In the above example, `expr1` evaluates to `false` which means that `expr1 && expr2 && expr3` can never be true. C++ will therefore only evalue `expr1` (note, `expr1`, `expr2`, and `expr3` are stand-ins for expressions that will evaluate to a boolean.

```
expr1 || expr2 || expr3
```

In the above example, C++ will only evaluate `expr1 || expr2` because `expr1 || expr2` evaluates to `true` which means that `expr1 || expr2 || expr3` can never be true.

### Compount Assignment Operators

Compound assignment operators combine performing some operation and assignment into one step. The format `op=`, where *op* is the stand in for an operator.

| Operator | Example  | Meaning     |
|----------|----------|-------------|
| `+=`     | `a += b` | `a = a + (b)` |
| `-=`     | `a -= b` | `a = a - (b)` |
| `*=`     | `a *= b` | `a = a * (b)` |
| `/=`     | `a /= b` | `a = a / (b)` |
| `%=`     | `a %= b` | `a = a % (b)` |

In the above table, `b` refers to the entirety of the right hand side. Treat it as if it were in parentheses

Note: this is not all the operators that can work as compound operators. 

### Operator Precedence

- Operator precedence is which operators are higher in the list of order of operation (e.g. multiply before you add)
- *associativity* is the "left to right" or "right to left" aspect of the order of operations for operators with the same precedence
	- e.g. you always do multiplication and division left to right
- Best bet is to use parenthesis to remove any confusion

Please see [this link](https://en.cppreference.com/w/cpp/language/operator_precedence) for a table documenting operator precedence and associativity in C++.

[This link](https://www.programiz.com/cpp-programming/operators-precedence-associativity) also has the table as well as a bit of an explanation.

## Markdown Help
 
 [link](www.google.com)
 
 
### Code
#### Multi-line code
```
code goes here
```

#### In-line code

`code goes here`