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


 
 ## Markdown Format Examples
 
 [link](www.google.com)
 
```
code goes here
```