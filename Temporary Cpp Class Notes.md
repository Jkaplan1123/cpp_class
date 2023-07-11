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
	[](intx) {std::cout << x * x << " "; })

//1 4 9 16
```

- this code uses the lambda expression directly in the `for_each` function call
	- no other code except the vector initialization and the `for_each` function call 	
- one of the benefits of lambda expressions is that you can define them right where they are being used