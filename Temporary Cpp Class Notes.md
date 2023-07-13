## Section 21 - Lambda Expressions

### Motivation

- we often write many short functions that control algorithms
- prior to lambda expressions these short functions would be encapsulated in small classes to produce function objects
	- This worked, but many times classes and functions are far removed from where they are used - led to modification, maintenance, and testing issues
	-  compilers could not effectivley inline these functions for efficiency

Function Object Example

- these would have an overloaded `operator()` function. Whenever this operator is used, the function associated with it is called for any object of the particular type.
- These are objects but we are using them as functions (hence: function objects)

```
class Multiplier{
	private:
		int num{};
	public:
		Multiplier(int n) : num{n} {}
		int operator() (int n) const{
			return num * n;
		}
};


std::vector<int> vec {1,2,3,4};
Multiplier mult{10};
std::transform(vec.begin(), vec.end(), vec.begin(), mult);

// vec now contains {10, 20, 30, 40}
```

Another example using function objects

```
template <typename T>
struct Displayer {
    void operator() (const T &data) {
        std::cout << data << " ";
    }
};

std::vector<std::string> vec2 {"Larry", "Moe", "Curly"};

std::for_each(vec2.begin(), vec2.end(), Displayer<std::string>()); // Larry Moe Curly
```

Same Examples using Lambda Expressions

```
std::vector<int> vec1 {1,2,3,4,5};
std::vector<std::string> vec2 {"Larry", "Moe", "Curly"};

std::for_each(vec1.begin(), vec1.end(), [](int x) {std::cout << x << " ";});    // 1 2 3 4 5

    
std::for_each(vec2.begin(), vec2.end(), [](std::string  s) {std::cout << s  << " "; }); // Larry Moe Curly
```

- All the behavior we want is exactly where we want it - in line with the for_each call
- This makes the code easier to test, debug, and maintain
- The compiler can optimize this code more easily


- best practice with lambda expressions is to use them when the code is no more than a few statments
	- if you have more complex code you should use function objects
- FYI: the compiler generates behind the scenes function objects from the lambda expressions

### Structure of a Lambda Expression

```
[] () -> return_type specifiers {};
``` 

#### Capture List
- capture list (`[]`) - defines the start of a lambda expression. Captures the context or the closure in which a Lambda Expression executes


#### Parameters

- `()` contains the parameter list, which is a comma separated list of parameters that will be passed into the lambda
	- works very much like a parameter list in a function call
	- you can pass either by reference or by value, just like with a function. Same goes with pointer parameters
- we can use the `auto` keyword to tell the compiler to deduce the type of the parameters. This is very powerful and is frequently used with lambda expression to increase robustness, performance, and usability
	- this could, for example, allow you to pass both integers and floating point numbers to the same lambda expression 

#### Returning a Value from a Lambda Expression

- `-> return_type` is the type that the lambda expression will return. This can be omitted and the compiler will try to deduce it. 
	- like the return type of a function

If we want to return a value from the lambda expression, we can either do it explicitly using the `->` and entering the `return_type`:

```
auto lam = [] (int x, int y) -> int {return x+y}
```

or we can have the compiler deduce the return type itself:

```
auto lam = [] (int x, int y) {return x+y}
```

Having the compiler deduce the type is much more common


#### Specifiers
- `specifiers` - these are optional. They are utable and context poor.

#### Lambda Body
- The body of the lambda expression is contained in the `{}`. This is where you write the code you want to execute


#### Using a Simple Lambda expression

```
[] () {std::cout << "Hi";}(); // Displays Hi
```  

- this expression has no capture list, no parameters
- The `()` at the end of the lambda expression instantiate a function object from the lambda expression and call it using the overloaded function operator
- Lambda expressions are not typically used this way but this example demonstrates how lambda expressions work


#### Assigning Lambda Expressions to Variables

```
auto lam = [] () {std::cout << "Hi";}

lam(); // Displays Hi
```

- we can assign lambda expressions to variables and then use the variables to call the function object created from the lambda expression. `l()`.
- use the `auto` keyword to have the compiler deduce the type. This is required because we do not know the type of the lambda expression before compile time (see **How Lambda Expressions Work** below).  


```
auto lam = [] (int x) {std::cout << x;}

lam(10); // displays 10
lam(100); // displays 100
```

#### Returning a Value from a Lambda Expression

If we want to return a value from the lambda expression, we can either do it explicitly using the `->` and entering the `return_type`:

```
auto lam = [] (int x, int y) -> int {return x+y}
```

or we can have the compiler deduce the return type itself:

```
auto lam = [] (int x, int y) {return x+y}
```

Having the compiler deduce the type is much more common


### Passing a Lambda Expression to a Function

- lambda expressions can be passed to functions as parameters
- In C++14, you do this 2 ways
	- by passing the lambda expression as a function object using the standard library's `functional` header:

		```
		std::function<return_type(parameter_type)>
		```
		
		```
		#include <functional>
		
		lam = [] (int x) {std::cout << x;}
		void foo(std::function<void(int)>lam){
			lam(10);
		}
		```
	- by passing the lambda expression as a function pointer

	```
	lam = [] (int x) {std::cout << x;}
	void foo(void (*lam)(int)){
			lam(10);
	}
	```
- In C++20, you can use the `auto` keyword:

	```
	auto lam = [] (int x) {std::cout << x;}
	void foo(auto lam){
			lam(10);
	}
	```

- If you are only using the lambda expression once (common), then it makes sense to define the lambda expression in the function call

```
foo([] (int x) {std::cout << x;});
```

- If you are going to use the lambda expression more than once, it may be beneficial to assign it to a variable so that it can be passed to multiple functions without having to duplicate code

```
auto lam = [] (int x) {std::cout << x;};
foo(lam);
```

#### Predicate Lambda

- A predicate is a C++ function that takes in any number of arguments and returns a boolean (true/false) value
- A predicate lambda is a lambda expression that implements this functionality
- This is where the true power of lambda expression lies
	- useful for algorithms that have some sort of *do if* logic (e.g. `print_if`, `sum_if`, etc.)
	- A lot of STL algorithms require a pedicate lambda 

### Having Functions Return Lambda Expressions

- we can have a function return a lambda expression either as 
	- a function object: `std::function<return_type(parameter_type)>`
	- a function pointer (uncommon)
	- or by using the `auto` keyword
- no matter how you return the function, you use it the same way
	- assign the return expression to a variable 
	- then pass in any parameters that it needs

	```
	auto foo() {
		return [] (int x) {std::cout << x;};
	}
	
	auto lam = foo();
	lam(10); // displays 10
	
	```



### Stateless Lambda Expressions


- An empty capture list means that the expression captures no information from its environment and only knows about the information passed to it via the function parameter list
- a lambda expression with an empty capture list `[]` is said to be *stateless*

```
int x {10};
[] (int x) {std::cout << x;} (100); // Displays 100
```

- The lambda expression takes in no information from its enviornment - it does not know about the variable `x` instantiated above. This means that even though `x` was defined prior to the lambda expression and the lambda expression takes in an integer `x`, it still displays `100`

### Stateful Lambda Expressions

```
[captured_variables] () -> return_type specifiers {};
```

- lambda expressions with non-empty capture lists are known as *stateful* lambda expressions
	- other than the non-empty capture list, they are just like stateless lambda expressions 
- a stateful lambda expression captures information from its enviornment - that means that it can use variables declared within its reaching scope without requiring those variables be passed into the lambda as parameters
- We accomplish this by listing the variables we would like the lambda expression to have access to within its capture list (see `[captured_variables]` in code snipit above)

#### Captured Variables

See **How Captured Variables in Lambda Expressions Work** below for some background


- The base captured variables are read only and cannot be modified inside the lambda expression. They are catpured by `const` value.

```
int y {1};

// Does not compile
[y]  () {std::cout << ++y;}();

// Does compile
[y]  () {std::cout << y;}(); // Displays 1

// Does compile
[y]  () {std::cout << y+1;}(); // Displays 2
```

- If we want to be able to modify captured variables in the lambda function, we need to include the keyword `mutable`. These variables are being passed by value (not by reference), so any changes made to them exist solely within the scope of the lambda expression

```
int x {100};
[x] () mutable {
	x+= 100;
	std::cout << x;
}(); // Displays 200

std::cout << x; // Displays 100
```

- We can also capture variables by reference. Any changes made to variables captured by reference are visible outside the lambda

```
int x {100};
[&x] () {
	x+= 100;
	std::cout << x;
}(); // Displays 200

std::cout << x; // Displays 200
```

- We can mix-and-match the various capture types

| Capture List |           x           |           y           |
|:--------------:|---------------------|---------------------|
| `[x, y]`     | captured by value     | captured by value     |
| `[x, &y]`    | captured by value     | captured by reference |
| `[&x, y]`    | captured by reference | captured by value     |
| `[&x, &y]`   | captured by reference | captured by reference |

- Note, even when mixing-and-matching, you still need the `mutable` keyword if you plan on modifying a variable that is passed by value within the context of the lambda expression

```
int y {10};
int x {4};

// Does not compile
[&y, x]  () {
    x++;
    y++;
}();

// Does compile
[&y, x]  () mutable {
    x++;
    y++;
}();
```


#### Default Captures

- We use default captures when we want to capture a large number of variables but don't want to least each variable
- A default capture allows the lambda to capturea all local (to the current function) variables referenced within its body


| Syntax   | Meaning                                                                                                            |
|:----------:|--------------------------------------------------------------------------------------------------------------------|
|   `[=]`  | Capture all referenced variables by value                                                                          |
|   `[&]`  | Capture all referenced variables by reference                                                                      |
| `[this]` | The referenced member variables of the current object the lambda is defined within should be captured by reference[^21.2] |

[^21.2]: This occurs when the lambda expression is defined within a class. The *this* is the `this` pointer that is used in a class


- We can also explicitly capture variables according to different capture modes.
- We must always place the default capture first in the capture list. 
- The explicit capture cannot be the same as the default - will cause compiler error

| Syntax      | Meaning                                               |
|-------------|-------------------------------------------------------|
|  `[=, &x]`  | Default capture by value but capture `x` by reference |
|   `[&, y]`  | Default capture by reference but capture `y` by value |
| `[this, z]` | Default capture `this` but capture `z` by value       |



### How Lambda Expressions Work

When a lambda expresion is compiled, the compiler is generating a closure type class with a default constructor and an `operator()` function implementing the logic of the lambda. That means that behind the scenes, this:

```
auto lam = [] (int x) {std::cout << x;};

```

becomes this:

```
class ComilerGeneratedName{
public:
	CompilerGeneratedName();
	
	void operator() (int x) {
		std::cout << x;
	}
};
```

This class is not generated until compile time. When we define lambda expressions, the type hasn't been generated yet. The types is only generated when the lambda is compiled. This is why we need to use the `auto` keyword.

This all means that when we assign a lambda expression to a variable, we are actually instantiating an object of the compiler generated [closure](https://simple.wikipedia.org/wiki/Closure_(computer_programming))[^21.1].


[^21.1]: A closure is a function that has an environment of its own. This enviornment must have at least one bound varaible (a name that has a value, such as a number) - definition from "Closure (Computer Pgroamming)", Simple English Wikipedia July 13, 2023


#### How Captured Variables in Lambda Expressions Work

Captured variables become member variables of the compiler generated closure/class

```
int y {10};
auto lam = [y] (int x) {std::cout << x+y;};
```

becomes:

```
class ComilerGeneratedName{
private:
	int y;
public:
	// Constructor
	CompilerGeneratedName(int y) : y{y} {};
	
	void operator() (int x) const {
		std::cout << x + y;
	}
};
```

- The captured variables are stored as member variables of the compiler generated class
	- When defining a stateful lambda's capture list, we are defining the parameterized constructor of the lambda's compiler generated closure 
	- When the stateful lambda is instantiated, a unique function object is created using this parameterized constructor, which stores the captured variables as member variables.
- Notice that the generated `operator()` function implementing the lambda expression is a `const` member function. This means that the member varible `y` cannot be modified
- If we want to pass in varibles by a non-constant value, we use the `mutable` keyword


```
auto lam = [x] () mutable {
	x+= 100;
	std::cout << x;
}
```

```
class ComilerGeneratedName{
private:
	int x;
public:
	// Constructor
	CompilerGeneratedName(int y) : y{y} {};
	
	void operator() () {
		x+= 100;
		std::cout << x;
	}
};

```

### Lambdas and the STL

- The most common use of Lambdas is with the standard templates library (STL), as either a predicate or an operator
- They will often be refered to as uniary/binary predicates or uniary/binary operations - indicates if the lambda expression is operating as a predicate or an operator and how many parameters it requires
	- unary means one parameters
	- binary means two parameters


All of these examples can be found in the class source code: `cpp_class/Class_Source_Code/Section21/STL_Lambdas/main.cpp`

#### Example: `for_each` algorithm

```
std::vector<int> nums {10,20,30,40,50};

std::for_each(
	nums.begin(), //from the beginning of nums
	nums.end(), 
	[] (int num) {std::cout << num << " ";});
```

This algorithm is iterating over each element in the vector `nums` staring at the beginning (`nums.begin()`) through the end (`nums.end()`). It is then preforming the lambda algorithm `[] (int num) {std::cout << num << " ";}` on each element in `nums`. In this case the lambda is an operator because it is doing something, not returing a boolean value. 


#### Example: `transform` algorithm

```
std::vector<int> test_scores {93,88,75,68,65};
int bonus_points {5};
	
std::transform(test_scores.begin(), test_scores.end(), test_scores.begin(), [bonus_points] (int score) {
        return score += bonus_points;
    });
```

- We are going to transform the container `test_scores` going through the whole container from the beginning (`test_scores.begin()`) to the end (`test_scores.end()`)
- We are goign to start writing back the information at `test_scores.begin()` - i.e. we are going to start upding the container from `test_scores.begin()`
	- you can imagine a scenario where you did not iterate through the whole container and you started upating part way through 
- The lambda expression ` [bonus_points] (int score) {return score += bonus_points;}` is the transformation operation we are preforming. 
	- `std::transform` is going to pass each element in `test_scores` as an argument to the lambda expression as its `score` parameter
	- The lambda expression is also capturing `bonus_points` by value.
	- `std::transform` takes the value that the lambda expression returns for each element and write it to `test_scores` starting at `test_scores.begin()`.
- The lambda expression here is an operator


#### Example: `remove_if` algorithm

```
std::vector<int> nums {1,2,3,4,5};
	
nums.erase(std::remove_if(nums.begin(), nums.end(), [] (int num) {
        return num % 2 == 0;
    }), 
    nums.end());
```

- The `remove_if` algorithm is removing the even numbers from the vector `nums`. Once it removes them, it is going to erase them using `nums.erase`)

- `remove_if` is iterating over the entire container `nums`.
- `remove_if` passes in each value from `nums` one at a time into the **predicate** lambda: `[] (int num) {return num % 2 == 0;}`
- This lambda returns a true/false boolean depending on if the element meets its criteria (in this case if it is even) - we are returning `true` for whatever we want to remove



- `remove_if` puts the numbers it wants to remove at the end of the container and sets `nums.end()` to point at the start of the numbers to be removed. 
- We then call `nums.erase()` staring at the newly defined (thanks to `remove_if`) `nums.end()`. This deletes the removed even numbers. It basially chops off those numbers