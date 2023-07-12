## Section 20 - Fundamentals of the Standard Template Libary (STL)

### What is the STL

- a (huge) library of powerful, reusable, adaptable, and generic classes and functions
- Implemented using C++ templates
- Implements common data structures and alogorithms
	- algorithms have well known time and size complexity
- Tried and tested - resuable
- consistent, fast, type-safe

#### Main Components of the STL

- [Containers](https://cplusplus.com/reference/stl/) - collections of objects or primitive types
	- ex: array, vector, stack, queue, etc. 
	- Types of containers: 
		- **Sequence containers**: containers that maintain the order of inserted elements
			- array, vector, list, forward_list, deque 
		- **Associative Containers**: insert elements in a predefined order or no order at all
			- set, multi set, map, multi map
		- **Container adapters**: variations of the other containers. Do not support iterators (cannot be used with the STL algorithms)
			- stack, queue, priority queue
- Algorithms - functions for processing sequences of elements from containers
	- ex: find, max, count, sort, etc.
	- Types of algorithms: modifying and non-modifying - depends on if the algorithm modifies the sequence that it acts upon 
- Iterators - generate sequences of elements from containers that algorithms use
	- ex: forward, reverse, by value, by reference, constant, etc.
	- Types of iterators:
		- **[Input iterators](https://www.geeksforgeeks.org/input-iterators-in-cpp/)**: from the container ot the program
		- **[Output iterators](https://www.geeksforgeeks.org/output-iterators-cpp/)**: from the program to the container
		- **[Forward Iterators](https://www.geeksforgeeks.org/forward-iterators-in-cpp/)**: navigate one item at a time in one direction
		- **[Bi-directional iterators](https://www.geeksforgeeks.org/bidirectional-iterators-in-cpp/)**: navigate one item at a time in either direction
		- **[Random access iterators](https://www.geeksforgeeks.org/random-access-iterators-in-cpp/)**: directly access a container item

### Generic Progamming and Templates
  
- Generic Programming is "writing code that works with a variety of types as arguments, as long as those argument types meet specific syntactic and semantic requirements"
	- if you have code that is generic, you should be able to use any type that makes sense with that code and it should work
		- ex: if you have a program that takes in a number and returns the square of that number, the program should work with any numerical type (`int`, `double`, `long`, etc.)
	- The C++ is statically typed, so how can we get generic programing in C++? - Macros (**beware**), Function Templates, Class Templates

#### Example for This Section

We want to wrtie a max function that returns the maximum of two numbers that are passed into it.

```
int max(int a, int b) {
	return (a>b) ? a : b;
}
```

- We want this functino to also work for doubles, longs, characters, etc. 
- The code is the same for all of them, it is only the types of the parameters that change.

Note: [? conditional statement in C++](https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm) 

#### Macros

Be very careful when using macros. Often there are better ways to do what you are trying to do.

**Do not use macros with arguments in your code**. Legacy code may have this so it is important to understand how it works.

- macros begin with a `#`, which means that it is a preprocessor directive
	- `#include <xxx>` is a macro  
- No type information
- Preprocessor is just doing simple substitution
	- When using `#define` the preprocessor will remove the `#define` statements from the code. It then goes through the program and replaces any defined names with what we defined them to be. - A better way to do this is by using constants 
	- We can use macros with parameters to create a function with generic programming. This allows us to write the function once rather than having to write it multiple times with each type as an input.

	```
	#include <iostream>
	
	//int min(int a, int b) {
	//    return (a < b) ? a : b;
	//}
	//
	//char min(char a, char b) {
	//    return (a < b) ? a :  b;
	//}
	//
	//double min(double a, double b) {
	//    return (a < b) ? a : b;
	//}
	
	#define min(a, b)  (((a)<(b)) ? (a) : (b))
	
	#define max(a,b) ((a>b) ? a : b)
	int main() {
	
	    std::cout << min(2,3) << std::endl;
	    std::cout << min('A', 'B') << std::endl;
	    std::cout << min(12.5, 9.2) << std::endl;
	    std::cout << min(5+2*2, 7+40) << std::endl;
	
	    std::cout << max(10,20) << std::endl;
	    return 0;
	}
	```
	
	- When the preprocessor sees any function `max` with two arguments, it will replace it with what we defined in the macro. It will also replace arguments a and b
	- We have no functions defined, just a single macro called `max`
- Remember, the preprocessor is simply substituting. It does not know C++. Lots of problems can occur once you try to compile and run this code. 
	- for example, take `#define square(a) a*a`
	- if you write `result = square(5)`, you expect it to output 25. The compiler replaces `square(5)` with `5*5` so you get `result = 5*5` which does get you a value of 25
	- if you write `result = 100/square(5)`, you may expect it to output a value of 4. The compiler replaces `square(5)` with `5*5` so you get `result = 100/5*5` which outputs a value of 100.
- when we use Macros, we should wrap up all the arguments in parenthesis
	- if we have `#define square(a) = ((a)*(a))`
	- `result = square(5)` becomes `result = ((5)*(5))`. Note the parenthessis. 
	- These parenthesis meen that when you do `result = 100/square(5)`, the preprocessor substitutes in `result = 100/((5)*(5))` which gets you 4.
	- Note that there are parenthesis around each argument (`(a)`) and the whole expression(`((a)*(a)`). This allows for things like `result = 100/square(2+3)`. The preprocessor substitutes in `result = 100/((2+3)*(2+3))`, which also gets you 4

A better way to do this generic programming is using templates


#### Generic Programming with Templates

- A C++ template is a generic blueprint that the compiler uses to generate specialized functions and classes
- We define a template with a placeholder type. We then plug in the actual type we want when we need it. 
- The compiler generates the appropriate function/class from the blueprint
	- This happens at compile time
- Supports generic programmming/meta-programming
- Templates are powerful, but can be very complex 

##### Function Templates

- We want to wrtie a max function that returns the maximum of two numbers that are passed into it.

	```
	int max(int a, int b) {
		return (a>b) ? a : b;
	}
	``` 

Note: [? conditional statement in C++](https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm) 

- We want this function to also work for doubles, longs, characters, etc. 
- The code is the same for all of them, it is only the types of the parameters that change.
- We can write just one blueprint for this function using templates


- we can replace any type we want to generalize with a name (e.g. `T`).

	```
	T max(T a, T b){
		return (a>b) ? a : b
	}
	```

- but this won't compile. We need to tell the compiler that this is a template function

	```
	template <typename T>
	T max(T a, T b){
		return (a>b) ? a : b
	}
	```

	- notice the line `template <typename T>`, this is the template parameter line that tells the computer that `T` is the type name that will be replaced with whatever the user needs. 
	- This will compile but it will not generate any code. The compiler does not generate any code until the user uses a specialized version of the template
	- We can also use `class` instead of `typename`. They are essentially equivalent

	```
	template <class T>
	T max(T a, T b){
		return (a>b) ? a : b
	}
	```
	
- with the template, the compiler can generate the appropriate function from the template. This happens at compile time.

	```
	int a {10};
	int b {20};
	std::cout << max<int>(a,b); // displays 20
	
	double c {15.5};
	double d {14.4};
	std::cout << max<double>(c,d); //displays 15.5
	```
	
	- the `<int>` and `<double>` gives the compiler all the information it needs to generate a specialized function from the template we created by using those types in place of `T`
		- we used this syntax when creating vectors in smart pointers (they are implemented as template classes)
	- often the compiler can deduce the type of the template parameter and we do not need to provide it in angle brackets

		```
		double c {15.5};
		double d {14.4};
		std::cout << max(c,d); //displays 15.5
		```
		
- We can use this code to generate a function for **almost** any type we need. The only constraint is that the `>` must be supported for that type either nativley or as an overloaded operator
- We can have multiople template parameters and their types can be different
	
	```
	template <typename T1, typename T2>
	void func (T1 a, T2 b){
		std::cout << a << " " << b;
	}
	```
	
	- when we use the function we provide the template parameters, but oftentimes the function can deduce them
	- You can pass by reference, value, pointer, with const modifers, etc.
	- All the function parameters do not have to be generic


##### Class Templates

- A class template is similar to a function template but at the class level - a generic blueprint that th ecompiler uses to create specialized classes
	- Allows for plugging in any data type and the compiler generates the appropriate class from the blueprint
- Class templates can be very complex, especially once you start considering all the other elements of classes (e.g. operator overloading, dynamic polymorphism, inheritance, etc.)


- Let's say taht we want a class to hold Items where the item has a name and an integer

```
class Item {
private:
    std::string name;
    int value;
public:
    Item(std::string name, int value) : name{name}, value{value} 
    {}
    std::string get_name() const {return name; }
    int get_value() const { return value; }
};
```

- Let's say we want another class similar to Item but that takes a double (instead of an int) and a string
	- We cannot overload class names
	- we do not want to use dynamic polymorphism
	- We can use class templates to write the blueprint for the class

```
template <typename T>
class Item {
private:
    std::string name;
    T   value;
public:
    Item(std::string name, T value) : name{name}, value{value} 
    {}
    std::string get_name() const {return name; }
    T get_value() const { return value; }
};
```

- we can replace the type of the value attribute from `int` to `T` in this case, but this can be any name
	- note that only the `int` type was replaced, the template still requires a `string` type 
- We can now create instances of Item

	```
	Item<int> item1 {"Frank", 100};
	
	Item  <std::string> item2 {"Frank", "Professor"};
	
	Item <Item<std::string>> item3 {"Frank",  {"C++", "Professor"}};
    ```
    
- we can have multiple different template parameters and their types can be different. We can also create a `struct` template rather than a class

	```
	template <typename T1, typename T2>
	struct My_Pair {
	    T1 first;
	    T2 second;
	};
	
	
	My_Pair <std::string, int> p1 {"Frank", 100};
   My_Pair <int, double> p2 {124, 13.6};
	```
	
	- The `My_Pair` class associates any two pieces of data together. This is very useful an so is already defined for us in the STD library as `std::pair`
		- We need to have `#include <utility>` in our to use it
		
		```
		#include <utility>
		std::pair<std::string, int> p1 {"Jack", 100};
		std:: cout << p1.first; // Jack
		std::cout << p1.second; // 100
		```  
	- The STD library also has a tuple template class

- Put all template classes in their own `.h` file (no `.cpp` file)
	- This exmaple would have the template class in `Item.h` and no `Item                                                                                                                                                                                                                             .cpp` file would be used
	- Because you are not actually compiling the blueprint, having a `.cpp` file can create all sorts of issues

##### Creating a Generic Array Template Class

- It is possible to have non-type template parameters
- This is just to learn, if you need a fixed size array use `std::array`
- See the source code


### Intro to STL Containers

- Containers are data structures that can store objects of *almost* any type
	- they are implemented as template-based classes
- Each container has a set of member functions that we can use
	- some are contianer-specific, but others are availiable to all containers
	- for example: every container has a default constructor that initializes an empty container
- Each container has an associated header file that must be included in order to use the container `#include <container_type>` 

#### Container Elements

- What types of elements can we store in containers?
- We can store all of the primitive types in containers
- When we store an element in a container, the container makes a copy of that element
	- we must make sure that our objects are copyable and assignable
	- This means they must have copy constructors as well as copy assignment
	- We can also provide move semantics for efficiency
- Ordered associative containers must be able to compare elements using the `<` and `==` operators
	- objects must support these operators via operator overloading   


#### Helpful Websites

- [Geeks for Geeks STL Containers](https://www.geeksforgeeks.org/containers-cpp-stl/)
- [C++ Documentation on STL Containers](https://cplusplus.com/reference/stl/)
- [List of member functions common to all STL container types](https://cs.smu.ca/~porter/csc/ref/stl/containers_mem_fun_dist.html)


### Intro to STL Iterators

- Iterators allow us to thing of a container as a sequence of elements, no matter what the container is
	- For exmaple, we could have a vector, a set, or a map. They are all very different containers but iterators allow us to process the sequence of elements from these containers without worrying how the container is implemented behind the scenes
- Implemented as template classes - we create iterator objects and use them to iterate through out containers
- The syntax with iterators is similar to that of pointers
	- we can use the dereference operator, the increment and decrement operators, and so forth 
- Most STL container classes can be traversed with iterators
	- some exceptions: stack and queue
- [Geeks for Geeks Intro to Iterators in C++](https://www.geeksforgeeks.org/introduction-iterators-c/)

#### Declaring Iterators

- an iterator must be declared based on the container type they will iterate over
- Syntax: `container_type::iterator_type iterator_name` 
- Examples:
	- `std::vector<int>::iterator it1` - iterator that traverses a vector of integers
	- `std::list<std::string>::iterator it2;` - iterator that traverses a list of strings
	- `std::set<char>::iterator it4;` - iterator that traverses a set of `char`
- An STL container has a begninning and an end
	- the beginning is the first element in the container
	- the end is the location one **after** the last element in the container (**not** the last element)
	- Almost all of the STL containers have `begin` and `end` methods


##### `.begin()` and `.end()` iterator methods

- `std::vector<int> vec {1,2,3}`: We create a vector of integers `vec` whose elements are 1, 2, and 3 in that order
	- `vec.begin()` returns an iterator pointing to the the element `1`
	- `vec.end()` will return an iterator pointing to one **past** the element `3`
		- when we write code we use `vec.end()` as the sentinal so that we know we are at the end of a list
- `std::set<char> suits {'C', 'H', 'S', 'D'};`
	- a set may or may not be implemented in contiguous memory, but it does not matter - we do not need to know
		- `suits.begin()` still returns an iterator to the first element in the set and `suits.end()` still returns an iterator 1 past the last element in a set
- The upshot is that `XXX.begin()` will always point to the first element in the set and `XXX.end()` will always point to 1 past the last element in the set
- We can use this information to initialize our iterators
	- `std::vector<int> vec {1, 2, 3};`: Create a vector of integers `vec` whose elements are 1, 2, and 3 in that order
	- `std::vector<int>::iterator it = vec.begin();` or `auto it = vec.begin();`: call `vec.begin()` to point to the first element in the vector, in this case it is the value `1`
		- if the vector had been empty then `vec.begin()` would have pointeded to `vec.end()`
		- note that we can use the **auto** keyword to have the compiler deduce the type of iterator

##### Operations with iterators

- There are a bunch of operations that we can use on iterators
- most feel very similar to using pointers
- Some key operations:
	- assignment (`it = it1`)
	- Pre/post increment/decrement 
	- Dereference (`*`) - when we dereference an iterator we get the element in the container that it is pointing to
	- Arrow (`->`) operator - we can use the arrow operator when we are pointing toobjects and we want to access their attributes and methods


##### Iterator Example
```
std::vector<int> vec {1, 2, 3};
auto iter = vec.begin();
while (iter != vec.end()){
	std::cout << *iter << " ";
	++iter;
};

// 1 2 3
```

- The code above creates a vector `vec` of integers. 
- It then creates an iterator `iter` and initializes it using `vec.begin()` so that it is pointing at the first element in `vec`.
- The `while` loop is set up to run as long as `iter` does not point to `vec.end()`. 
	- It then uses the derefernece operator to print out whatever element of the container that `iter` is currently pointing to.
	- It then increments `iter` by 1. 
	- The cycle continues until `iter` points at the same place as `vec.end()`
- The `while` loop could have been written as a `for` loop:

```
for (iter = vec.begin(); iter != vec.end(); iter++){
	std::cout << *iter << " ";
}
```

- the iterator does not even need to be declared prior to the loop

```
std::vector<int> vec {1, 2, 3};
for (auto iter = vec.begin(); iter != vec.end(); iter++){
	std::cout << *iter << " ";
}
```

- we could do this via a range-based for loop, but not all containers allow us to randomly access elements like a vector does. - for those containers, iterators are necessary

##### Reverse Iterator 

- Works in reverse. The last element is the first and the first is the last
- `++` moves backward/in reverse, `--` moves forward

```
std::vector<int> vec {1, 2, 3};
std::vector<int>::reverse_iterator rit = vec.rbegin();
while (rit != vec.rend()){
	std::cout << *rit << " ";
	++rit;
}

// 3 2 1
```

- Since this is a reverse iterator
	- `vec.rbegin()` points to the last element in the container rather than the first
	- `vec.rend()` points to the element 1 before the first element in the container

##### Const Iterators

- `const` iterators are read-only iterators - it cannot change what it is pointing to 
- There methods in the appropriate container class that return specific types of iterators
	- `begin()` and `end()` - regular iterators (`iterator`)
	- `cbegin()` and `cend()` - constant regular iterator `const_iterator`
	- `rbegin()` and `rend()` - reverse iterator (`reverse_iterator`)
	- `crbegin()` and `crend()` - constant reverse iterator (`const_reverse_iterator`)


Constant forward iterator

```
std::vector<int> vec {1, 2, 3};
for (auto citer = vec.cbegin(); citer != vec.cend(); citer++){
	std::cout << *citer << " ";
}
```

Constant reverse iterator

```
std::vector<int> vec {1, 2, 3};
std::vector<int>::const_reverse_iterator crit = vec.crbegin();
while (crit != vec.crend()){
	std::cout << *crit << " ";
	++crit;
}

// 3 2 1
```

### Introduction to STL Algorithms

- STL algorithms work on sequences of elements that are obtained from STL containers using STL iterators
- STL has many common and useful algorithms ([C++ STL Algorithms Libarary](https://en.cppreference.com/w/cpp/algorithm))
- Many algorithms require extra information in order to do their work. These could be function objects (functors), function pointers, or lambda expressions
	- modern C++ uses lambda expressions

- In order to use the STL algorithms, we must include the algorithms header file (`#include <algorithm>`)
- Different containers support different types of algorithms
	- since algorithms depend on iterators, this determines the types of algorithms we can use with certain containers
- Many algorithms take a [predicate](https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-functions.html) as an input
	- a predicate is any unary C++ function that returns a boolean (`true` or `false`). 
	- These are used for algorithms that check the elements to see if they meet some conditional (the predicate).
	- One example of this is the `find_if` alogirhtm, which returns an iterator pointing to the first value in the range satisfying some condition (e.g. if the number is even). 
	
#### Iterator Invalidation

- Iterators point to container elements
- It is possible for iterators to become invalid during processing
- Suppose we are iterating over a vector of 10 elements and we use the vector's `clear()` method, empyting the vector. What happens?
	- the iterator will continue iterating until it sees the end of the vector, but this is no longer valid 
	- the behavior is undefined.
	- Every STL container has documentation about whe iterators become invalid


#### Example: `find` with primitive types

- the `find` algorithm tries to locate the first occurrence of an element in a container
	- there are lots of variations on this algorithm, but we are going to keep it simple
- If the function finds the element it returns an iterator that points to the element it just found. If the function does not find the elment, it will return an iterator pointing to the end of the container. 

```
std::vector<int> vec {1,2,3,4,5};

// run the find algorithm on all the elements in vec 
// starting at vec.begin() up to (but not including) vec.end()
auto loc = std::find(vec.begin(), vec.end(), 5);
    
if (loc != std::end(vec)) // if found
    std::cout << "Found the number: " << *loc <<  std::endl; 
else 
    std::cout << "Couldn't find the number" << std::endl;
```

- `find` needs to compare two elements in order to see if they are the same
	- we don't have to do anything if we are using primitive types because the compiler knows how to compare them
	- if we are using our own user-defined objects in containers, then we must provide the overloaded equality operator for our objects so that `find` can compare them

#### Example: `for_each` algorithm

- `for_each` algorithm applies a function to each element in the iterator sequence
- the function must be provided to the algorithm as either a function (function object), a function pointer, or a lambda expression

##### `for_each` using a functor

```
struct Square_Functor {
	void operator() (int x) { //overload () operator
		std::cout << x*x << " ";
	}
};

Square_Functor square; //Function object

std::vector<int> vec {1, 2, 3, 4};

std::for_each(vec.begin(), vec.end(), square);

//1 4 9 16
```

- `square` is a function object (functor) of type `Square_Functor`
- `Square_Functor` is a structure, but it can also be a class that has a single public method
- `void operator() (int x)` is overloading the `()` operator. It expects the same type as the elements in the container we are processing
- We are going to iterate starting at `vec.begin()` until we reach (but not including) `vec.end()`. 
	- In each iteration, the overloaded function call operation `()` for the square object will be called and the current container element will be passed into it. 
	- Note that the original container elements are not modified

##### `for_each` using a function pointer


```
void square(int x) {
	std::cout << x*x << " ";
}

std::vector<int> vec {1, 2, 3, 4};

std::for_each(vec.begin(), vec.end(), square);

//1 4 9 16
```

- notice that the code to call the `for_each` algorithm is the exact same as when using a function
- This case, the `square` parameter is the name of a regular function, not a function object
	- what is being passed into the `for_each` function is a pointer to the `square` function, which is really just the address of `square` itself
	- At each iteration of the `for_each` loop, `square` will be called and the current container lement passed into it


##### `for_each` using a lambda expression  

```
std::vector<int> vec {1, 2, 3, 4};

std::for_each(vec.begin(), vec.end(), 
	[](int x) {std::cout << x * x << " "; });

//1 4 9 16
```

- this code uses the lambda expression directly in the `for_each` function call
	- no other code except the vector initialization and the `for_each` function call 	
- one of the benefits of lambda expressions is that you can define them right where they are being used


### STL Sequence Containers Overview

#### Array (`std::array`)

- must include the array header file (`#include <array>`)
- Fixed size of any type - size must be known at compile time
- Different from a raw array
	- object type
	- always has size associated with it
	- not just a pointer to the first element 
- Allows for direct element access
	- very efficient - element access happens in constant time ($\mathcal{O}(1)$)
- we can get access to the raw array address if we need to
	- allows us to use it with libraries that use raw pointers
- All STL iterators available and do not invalidate (fixed size)


##### Initialization and assignment

```
std::array <type, num_elements> { a, b, c, ... }
``` 

- since the size of the array must be known at compiler time, we have to provide both the type we want to store in it as well as the size. This is what is found in the angle brackets `<type, num_elements>`
- the elements of the array are entered in the curly braces `{ }`.
	- if you enter more elements than the size of the array, you get an error
	- if you enter fewer elements than the size of the array, then the omitted will have some 0 value
		- for an array of numerical types, the omitted value will be 0
		- for an array of strings or similar, the omitted value will be empty 
	- Will convert c-style string literals to `std::string` types if necessary
	- In c++11 you need to provide double curly braces (`{ { } }`). Staring in C++14, you just need to provide single curly braces 
	
- we can use an assignemnt statement and an initializer list to assign multiple variables to an existing `std::array`


	```
	std::array <int, 5> arry {1, 2, 3, 4, 5};
	
	arry = {2, 3, 4, 5, 6}; // [2, 3, 4, 5, 6]
	
	arry = {3, 5, 7}; // [3, 5, 7, 0, 0]
	```
	
	- the same rules apply regarinding uninitialized elements apply when doing assignments
- Remember: unititialized arrays (e.g. with no `{ }`) have garbage values for their elements
- Both the array's size and its type **must** be included in the function definition when passing a `std::array` to a function.
	- you can generalize this somewhat by using function templates, but you still have to provide the information somehow


```
#include <iostream>
#include <array>

int main()
{
    
    std::cout << std::endl;
    std::cout << "std::array of std::string types" << std::endl;
    std::cout << "std::array <std::string, 3> array_test { std::string(\"hello\"), \"goodbye\"};" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::array<std::string, 3> string_test { std::string("hello"), "goodbye"};
    for (auto entry : string_test){
        std::cout << "\"" << entry << "\"" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "std::array of doubles" << std::endl;
    std::cout << "std::array<double, 3> double_test { 1.4, 2};" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::array<double, 3> double_test { 1.4, 2};
    for (auto entry : double_test){
        std::cout << entry << std::endl;
    }
    
    return 0;
}
```

##### `std::array` - Common Methods

```
std::array <int, 5> arr {1, 2, 3, 4, 5};

std::cout << arr.size(); // 5

std::cout << arr.at(0); // 1
std::cout << arr[1]; // 2

std::cout << arr.front(); // 1
std::cout << arr.back(); // 5

std::array <int, 0> empty_arr;
std::cout << arr.empty(); // 0 (false)
std::cout << empty_arr.empty(); //1 (true)


std::cout << arr.max_size(); // 5

std::array <int, 5> swap_arr {6, 7, 8, 9, 10};
arr.swap(swap_arr); // swaps the 2 arrays so that 

std::cout << arr.fill(1); // [1, 1, 1, 1, 1]

int *data = arr.data(); //get raw array addresss
``` 

- We can get the size of the array using the `.size()` method.
- We can access a particular element of an array using either the `.at()` method or the subscript `[]` method
	- the subscript operator does no bounds checking but the `.at()`. method does throw an exception if we are out of bounds 
- The `.front()` and `.back()` methods return references to the elements at the front and the back of the array, respectively
- The `.empty()` returns `true` if the array is empty and `false` if it is not
	- note that an array initialized will all 0 values will not be empty. The size of the array must be 0
- The `max_size()` method basically means the size of the array
	- rarely used with `std::array` but is used with other `stl` containers 
- The `.swap()` method swaps the values of two arrays
	- both arrays must be of the same size and type 
	- in the example code, after `arr.swap(swap_arr);`, `arr` is `[6, 7, 8, 9, 10]` and `swap_arr` is `[1, 2, 3, 4, 5]`. 
- To `.fill()` method assigns the given value to all elements in the array 
- The `.data()` method gets access to the underlying raw array
	- `.data()` returns the address of the raw array which we store in a pointer variable 

##### Documentation and Helpful Links

- [C++ std::array Documentation](https://en.cppreference.com/w/cpp/container/array)


#### Vectors (`std::vector`)

- need to include the vector header file (`#include <vector>`)
- main workhorse of the STL - used to create dynamically sized arrays 
	- handled behind the scenes
	- stored in continguous memory 
- direct element access in constant $ \left( \text{i.e. } \mathcal{O}(1) \right) $ time
- rapid insertion and deletion at the back of the vector in constant time
- Insertion or removal of elements (not at the back) done in linear $\left( \text{i.e. } \mathcal{O}(n) \right)$ time
- all iterators available and they may invalidate (due to changing size)

##### `std::vector` Common Methods

- add elements to the back of the vector using the `push_back` method
- `.size()` method returns the number of elements in the vector
- `.capacity()` method returns the current capacity of the vector. When this capacity is exceeeded, the vector will expand dynamically
- `.max_size()` method returns the maximum size of a vector in our system (this will be a very large number)
- We can access individual elements using the `.at()` method or the subscript method (`[]`). The `.at()` method has bounds checking while the subscript method (`[]`) does not;
- Use `.push_back()` to add an element to the end of the vector.
	- remember that all container classes make copies of the elements they store 
- Use `.pop_back()` to remove an element from the end of the vector.
- The `.emplace_back()` method is used to add object types to the end of a vector
	- takes in the parameters that would normally be passed to the object's constructor then places that object at the end of the vector. 
	- This is super efficient
- `.empty()` returns `true` if the vector is empty and `false` if it is not
- `.swap()` is used to swap to vectors. The vectors must be of the same type but can have different sizes
- `.insert()` allows us to insert a value anywhere in a vector
	- we must pass it an iterator that points to the location of the vector where we want to insert the data and the element to be inserted
	- The element will be inserted just before the element that the iterator is pointing to. That iterator now points at the newly inserted element

	```
	std::vector<int> vec {1, 2, 3, 4, 5};
	auto it = std::find(vec.begin(), vec.end(), 3);
	vec.insert (it, 10); 
	
	// [1, 2, 10, 3, 4, 5]
	``` 
	
	- in the code above, we want to insert a `10` before the first `3` in the vector
	- We can also use the `insert` method to insert a whole sequence of elements

	```
	std::vector<int> vec2 {10, 20, 30, 40, 50};
	it = std::find(vec.begin(), vec.end(), 4);
	vec.insert (it, vec2.begin(), vec2.end()); 
	
	// [1, 2, 10, 3, 10, 20, 30, 40, 50, 4, 5]
	```
	
	- in the code above we insert all of `vec2` into `vec` right before the `4`

- we can use `std::sort()` or any other algorithm on vectors 


#### Sequence Container Dequeue 

- must `#include <deque>`
- Acts like a double-ended queue
- Dynamic size and handled by STL so similart to a vector - unlike a vector, the memory is not stored contiguously
	- think of a dequeue as a [linked list](https://www.geeksforgeeks.org/data-structures/linked-list/) of vectors
- Efficiency
	- direct element access in constant time
	- insertion and deletion at the front and back in constant time
	- insertion or removal of elements in linear time
- All iterators available and may invalidate


##### Initialization and Assignment

- `std::deque<int> d0 {1,2,3,4,5}` - standard initialization
- `std::deque<int> d1 (10,100)` - use an overloaded constructor to declare a deque consisting of `10` integers each initilized to the value `100`
- supports copy and move semantics for initialization and assignment
- the front of the deque is the first element and the back is the last element


##### `std::deque` Common Methods

- `.push_back()` method adds an element to the end of the deque 
- `.push_front()` method adds an element to the front of the deque
- `.pop_back()` method removes an element from the end of the deque
- `.pop_front()` method removes an element from the front of the deque
- The `.emplace_front()` and `.emplace_back()` methods are used to add object types to the front or back of a deque, respectively. These methods take in the parameters that would normally be passed to the object's constructor then places that object at the end of the vector. 
	- these methods are much more efficient than creating an object and then adding it to the deque 
- Many of the other elements are the same as for vectors and arrays

```
std::deque<int> d0 {1,2,3,4,5}; // [1, 2, 3, 4, 5]
d0.push_back(6); // [1, 2, 3, 4, 5, 6]
d0.push_front(0); // [0, 1, 2, 3, 4, 5, 6]

d0.pop_front; // [0, 1, 2, 3, 4, 5]
d0.pop_back; // [1, 2, 3, 4, 5]


std::deque<Person> people;
Person p1 ("Alice", 15);

people.push_back(p1);
people.push_front(Person("Bob", 29);

people.emplace_back("Charlie", 8);
people.emplace_front("David", 45);
```

#### List (`std::list`) and Forward List (`std::forward_list`)

- both are sequence containers
- store their elements in non-contiguous memory
- No direct access to elements - no `.at()` method or subscript operator (`[]`).
- very efficient for inserting and deleting elements once an element is found

##### `std::list`

- need header file `#include <list>`
- Dynamic size

- doubly linked list [^20.1] of elements - allows us to go from element to element in either direction 
	- direct element access is not supported 
	- [doubly linked list](https://www.geeksforgeeks.org/data-structures/linked-list/doubly-linked-list/): each element has a reference to the element immediately before and after it
- List has a front and a back
- Rapid insertion and deletion of elements anywhere in the container (constant time)
	- requires that we have an iterator to the element that we want to remove or insert before - usualy done using the `find` method
- We can use all the iterators, but they may become invalid when the corresponding element is deleted
- List is a good choice for when you need a container where you will have lots of insertions and removals but where you don't need direct access to the elements

###### `std::list` Initialization

- `std::list<int> l0 {1,2,3,4,5}` - standard initialization
- `std::list<int> l1 (10,100)` - use an overloaded constructor to declare a deque consisting of `10` integers each initilized to the value `100`

###### `std::list` Methods to add/remove elements

Accessing Elements:
- remember that we do not have access to the `.at()` method or the subscript operator (`[]`)



- a list uses the `.push_back()`, `.push_front()`, `.emplace_back()` and `.emplace_front()` methods to efficiently add elements to the front or the back in the same way the deque does
- a list uses the `.pop_back()` and `.pop_front()`, methods to efficiently remove elements from front or the back in the same way the deque does
- `.insert()` method requires the new element we want to insert and an iterator to the element that we want to insert new element before
- `.erase()` method requires an iterator pointing to the element that we want to erase

	```
	std::list<int> l {1, 2, 3, 4, 5};
	auto iter = std::find(l.begin(), l.end(), 3);
	
	l.insert(iter, 10); // [1 2 10 3 4 5]
	l.erase(it); // erases the 3: [1, 2, 10, 4, 5]
	```


- `.resize()` allows us to resize the list (of length $m$) to a desired length $\left( n \right)$
	- if the list is longer than the resized length $n$ (i.e. if $m > n$), than the first $n$ elements will be kept and the $\left( n+1 \right) ^{\text{th}}$ and greater elements will be deleted

		```
		l = {1, 2, 3, 4, 5};
		l.resize(2); // [1, 2]
		```
	
	- if the current list length $\left( m \right)$ is shorter than the resized list length $\left( n \right)$, then $n - m$  elements will be created (using the default initilizer for that type) and appended on to the end of the list

		```
		std::list<int> l {1, 2};
		l.resize(5); // [1, 2, 0, 0, 0]
		```

###### Traversing an `std::list` 

- use a range based for loop or use iterators

##### Forward List (`std::forward_list`)

- must include the forward list header file (`#include <forward_list>`)
- The forward list is like the regular `std::list`, except it is only singly linked. This means that it can only be traversed in one direction. 
	- advantage: less overhead because you only need one pointer per element (rather than two in a doubly linked list)
	- generally we only want to traverse a list in one direction
- The forward list has no concept of back, only front
	- it does not make sense to go to the back of a list and then not be able to traverse backwards 
	- this means that there is no `.back()` method
	- reverse iterators not availiable   

###### `std::forward_list` methods

- because there is no concept of a back, there is no `.back()` method
- the forward list has `.push_front()`, `.pop_front()`, and `.emplace_front()`, but not their "back" equivalents
- The `.size()` method is not supported (for performance reasons)
	- if you need to track the size of a forward list, you need to do it outside the list


- Since the forward list is singly-linked, it makes sense to insert and delete elements **after** the iterator reference

	```
	std::forward_list<int> l {1, 2, 3, 4, 5};
	auto iter = std::find(l.begin(), l.end(), 3);
	
	l.insert_after(iter, 10); // [1 2 3 10 4 5]
	l.emplace_after(iter, 100); //[1 2 3 100 10 4 5]
	l.erase_after(it); // erases the 100: [1, 2, 3, 10, 4, 5]
	```

- `.resize()` works the same as for the `std::list`

[^20.1]: A [linked list](https://www.geeksforgeeks.org/data-structures/linked-list/?ref=lbp) is a data structure where each element contains its data and a pointer to the next element in the list. An [doubly linked list](https://www.geeksforgeeks.org/data-structures/linked-list/doubly-linked-list/) has a pointer to the next element in the list and the previous element. 

### Associative Containers

- a collection of stored objects that allow fast retreival using a key
- STL provides sets and maps

#### Sets

- STL has four types of set containers: `std::set`, `std::unordered_set`, `std::multiset`, and `std::unordered_multiset`

##### Regular set (`std::set`)

- `#include <set>` header file
- similar to a mathematical set
- all iterators allowed

- No duplicate elements allowed: When initializing a set with duplicates, no error is thrown but the duplicates are ignored

	```
	std::set<int> s {1, 2, 3, 4, 5, 4, 3, 2, 1};
	// 1, 2, 3, 4, 5
	```

- Sets are sorted (ordered by key)
	  

	```
	std::set<int> s {2, 10, 8, 1, 11};
	// 1, 2, 8, 10, 11
	```
	
	- because sets are sorted, you need to make sure that you overload the `<`operator for any custom classes that you want to add to a set

- Inserting Elements - use `.insert()` method and `.emplace()` method
	- No concept of front and back - no `push_back()`/`push_front()`, `pop_back()`/`pop_front()`, etc. methods 
	- new elements are added in order

	```
	std::set<int> s {1,2, 3, 4, 5}
	
	s.insert(7); // 1, 2, 3, 4, 5, 7
	```
	
	- if you try to insert a duplicate then it will not be added, but no error will be thrown.
	- The set class uses the overloaded `<` operator for ordering and for determining if an element is already in a set
		- This is key, it does **not** use the equality (`==`) operator 
	- The `.insert()` method returns a `std::pair`
		-  first attribute is an iterator to either the element that we just inserted or an iterator to the duplicate element already in the set
		-  the second attribute is a boolean that indicates whether the insertion operation was successful or not.

	- Using the `.insert()` method:
	
	
		```
		person jack {"Jack", 27};
		person jena {"Jena", 28};
		std::set<Person> family;
		
		family.insert(jack); // adds jack to the set
		
		// adds jena to the set and 
		// assigns an iterator, boolean pair to result
		auto result = family.insert(jena);
		```

- the `.erase()` method can either be passed a key (the specific element) or an iterator to the element that we wante deleted. If that element exists, then it will erase it
	
	```
	std::set <int> s {1, 2, 3, 4, 5};
	s.erase(3); // erase the 3: 1, 2, 4, 5
	
	auto it = s.find(5);
	if (it != s.end()){
		s.erase(it); // erase the 5: 1 2 4
	}
	```

- The set's `.find()` method is different from the `find()` function in the STL library. It is best to use the set's `.find()` method because it is going to be the best/most efficienct implementation

- we can use the `.count()` method to tell how many times an element is in the set. Even though there can be no duplicates in a set, it is useful for determining if an item is in a set at all.

##### Multi-set (`std::multi_set`)

- also defined in `set` header file
- like a set except for it allows duplicates

##### Unordered Set (`std::unordered_set`)

- defined in `unordered_set` header file
- elements are unordered
- no duplicate elements allowed
- elements cannot be modified - they must be erased and a new element inserted
- no reverse iterators are allowed (unordered)

##### Unordered Multi-set (`std::unordered_multiset`)

- also defined in `unordered_set` header file
- elements are unordered
- allows duplicate elements
- no reverse iterators allowed (unordered)

#### Maps

- types of maps: `std::map`, `std::unordered_map`, `std::multimap`, and `std::unordered_multimap`
- - similar to a python dictionary: elements are stored as (key, value) pairs using `std::pair` objects


##### Regular Map (`std::map`)

- defined in the `map` header file (`#include <map>`)
- elements are ordered by key
- No duplicate elements (i.e. no duplicate keys)
- Direct element access using the key


- Initialization syntax: 

	```
	std::map <key_type, value_type> map_name {
		{key0, value0},
		{key1, value1},
		etc...,
	};
	```
	
- no concept of front or back

###### Inserting Elements

Inserting objects into an `std::map` 

- Option 1: use the `.insert()` method with a key, value pair stored in an `std::pair` data structure

	```
	std::map<std::string, int> m {
	        {"Larry", 3},
	        {"Moe", 1},
	        {"Curly", 2}
	    }; 
	
	std::pair<std::string, int> bob ("Bob", 25);
	m.insert(bob);
	
	m.insert(std::pair<std::string, int>("Anne", 10));
	    
	m.insert(std::make_pair("Joe", 5));
	```

- Option 2: privde the key in square brackets `[]` and assign the value to it.
		
	```
	m["Frank"] = 22; // inserts Frank
	```

###### Accessing and Modifying Elements

- Option 1: use the subscript operator. This will add the element if the key is not already in the map (see insertion section above)

	```
	m["Frank"] = 80; // updates Frank's value
	```

- Option 2: use the `.at()` method. This will throw an exception if the key is not in the map.

	```
	m.at("Frank") = 55; // updates Frank's value
	```
	
##### Erasing Elements

To erase an element from a map use the `.erase()` method. The erase method can either take in the key of the key-value pair that you want to remove or it can take in an iterator to that key-value pair.

```
m.erase("Anne"); // erase Anne

auto iter = m.find("Bob");
if (iter != m.end()){
	m.erase(iter); // erase Bob
}
```

##### Multimap `std::multimap`

- also included in the `<map>` header file
- ordered by key
- allows duplicate elements

##### Unordered Map `std::multi_map`

- included in the `<unordered_map>` header file
- elements are unordered
- No duplicate elements allowed
- No reverse iterators

##### Unordered Multiap `std::unordered_multimap`

- also included in the `<unordered_map>` header file
- elements are ordered by key
- No duplicate elements allowed
- No reverse iterators
	