## Section 17 - Smart Pointers

### Overview

#### Issues with Raw Pointers

- Raw pointers allow for absolute flexibility with memory management
	- This flexibility bring complexity: must explicitly allocate and deallocate storage for dynamic variables on the heap. We must also manager their lifetimes
- Some Potentially Serious problems
	- Uninitialized (wild) pointers: could be pointing anywhere in memory. Could access junk data or overwrite exiting data.
	- Memory leaks: comes from not deallocating storage that we previously stored on teh heap
	- Dangling pointers: when a pointer is pointing to storage that it thinks is valid but in fact has already been deallocated. These bugs can be hard to find and fix.
	- Not exception safe: if an exception is thrown, the code that releases allocated memory may not execute so we end up with memory leaks anyway
- Ownership
	- Who owns the pointer?
	- When should a pointer be deleted? 

#### What are Smart Pointers?

- Smart Pointers are objects
	- implemented as C++ template classes which we can instantiate
		- this is very similar to how vectors are implemented
		- we create a smart pointer much like we do a vector 
		- Actual implementation is compiler-dependent and beyond the scope of this course
- Can only point to heap-allocated memory
- Automatically call `delete` when no longer needed
- Adhere to RAII (resource acquisition is initialization) principles 
	- principle means that objects own resources
	- when a resource-owning stack object goes out of scope, its destructor is automatically invoked
- Several types of smart pointers
	- Unique pointers (`unique_ptr`)
	- Shared pointers (`shared_ptr`)
	- Weak pointers (`weak_ptr`)
	- Auto pointers (`auto_ptr`) - **Deprecated, don't use**

- Defined by class templates, similar to the way that the vector class is implemented - We create them using a template parameter, much like we did with vectors.
- Smart pointers are basically wrapper classes that contain and manage a raw pointer

#### Using Smart Pointers

- Need to have `#include <memory>` in code.
- Once we create a smart pointer, we can use it in much the same way as raw pointers
- The smart pointer classes provide overloaded dereference (`*`) and member selection (`->`) operators as well
- No pointer arithmetic on smart pointers
- We can have custom deleters with smart pointers - allows us to explicitly define the exact behavior we want when the pointer is about to be destroyed


#### Syntax for Declaring a Smart Pointer

```
{
	std::smart_pointer <Some_Class> ptr = ...
	ptr -> method(); // overloaded -> operator
	cout << (*ptr) << endl; // dereferncing
}
```

- replace `smart_pointer` with the specific type of C++ smart pointer you are going to use (unique pointer, shared pointer, or weak pointer)
- replace `Some_Class` with the class you want the pointer pointg to
- `ptr` will be destroyed and its memory deallocated when it is no longer needed (i.e. when it goes out of scope) 


#### RAII - Resource Acquisition is Initialization

- Principle means that objects own reesources
- RAII objects are allocated on the stack
- Resource Acquisition - open a file, alloacte memory, acquire a lock, etc.
- Is Initialization - the resource is acquired at object initialization time (in the object's constructor)
- Resource relinquishing happens in that object's destructor 
	- close the file, deallocate the memory, release the lock, etc.  


[Helpful Article](https://learn.microsoft.com/en-us/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170)

### Unique Pointers (`unique_ptr`)

#### Use Case

- Simple smart pointer - very efficient
- Can usually be a simple one-to-one replacement for the typical pointer use case
	- good use case for when you allocate storage, use it, then free it in the same block 

#### Capabilities

- `unique_ptr<T>`
	- points to an object of type `T` on the heap
	- is unique - there can only be one `unique_ptr<T>` pointing to a particular object on the heap
		- not absolutely unique - does not block raw pointers from pointing to the object 
	- owns what it points to
	- cannot be assigned or copied
	- **can** be moved - great for placing in standard template library containers such as vectors
- when the pointer is destroyed, what it points to is automatically destroyed 

#### Creating, Initializing, and Using

```
{
	// Initialize the pointer
	std::unique_ptr<int> p1 {new int {100}};
	
	// Using the pointer
	std:: cout << *p1 << std:: endl; // 100
	*p1 = 200;
	std:: cout << *p1 << std:: endl; // 100
	
	
	
} // p1 out of scope so it is automatically deleted
```

- `std::unique_ptr<int> p1 {new int {100}};` - create a unique pointer to an `int`. That `int` has been created on the heap and initialized to `100`.
	- `p1` now owns that object on the heap. When `p1` goes out of scope, the `int` on the heap will be de-allocated 
	- You do not need to call `delete` with a smart pointer
- You can use the pointer much the same way as a raw pointer
	- `std::cout << *p1 << std::endl` - dereferencing `p1` gets the integer that it is pointing to
	- you can use `p1 -> method()` with other classes just like you would with raw pointers (see below)

#### Other Useful Methods

```
std::unique_ptr<int> p1 {new int {100}};

std::cout << p1.get() << std::endl; // memory location of *p1

p1.reset(); // p1 is now nullptr
if (p1){
	std::cout << *p1 << std::endl; // won't execute since p1 is nullptr
}
```

- `p1.get()` returns a pointer to the object that `p1` points to
	- useful for working with libraries that use raw pointers 
	- Another way to phrase it: the `get()` method for smart pointers returns the raw pointer being managed
- `p1.reset()` makes `p1` a `nullptr`. Memory that it points to is released.
- `if(p1)` checks to see if `p1` is initialized. 
	- conditional evaluates to true if `p1` is initialized
	- conditional evaluates to false if `p1` is `nullptr`  
- It is possible to create a raw pointer variable and then initialize the unique pointer variable using that raw pointer. - this is bad practice
	- you are refering to an object on the heap form a smart pointer and a raw pointer. You do not generally want this


```
{
	// Initialize the pointer
	std::unique_ptr<Account> p1 {new Account {"Jack"}};
	
	// Using the pointer
	std:: cout << *p1 << std:: endl; // display account
	p1 -> deposit(1000);
	p1 -> withdraw(500);	
} // automatically deleted
```

- `std::unique_ptr<Account> p1 {new Account {"Jack"}};` - `p1` will manage an `Account` object on the heap


```
std::unique_ptr<int> p1 {new int {100}};
std::unique_ptr<int> p2; // creates a nullpointer p2

p2 = p1; //Error
p2 = std::move(p1); //okay

```

- `std::unique_ptr<int> p1 {new int {100}};` - create a unique pointer `p1` that points to an `int` on the heap with value `100`
- `std::unique_ptr<int> p2;` - creates a unique pointer `p2` with value `nullptr` and no memory on the heap allocated
- `p2 = p1;` - causes an **Error** because you cannot copy unique pointers
- `p2 = std::move(p1);` is okay because you are using move rather than copy semantics. This process transfers ownership of the object `p1` is managing to `p2`
	- `p1` is reassigned to `nullptr`
	- `*p2` returns the `int` 100

#### Vectors and Move

```
{
	std::vector<std::unique_ptr<int>> vec;
	std::unique_ptr<int> ptr {new int {100}};
	vec.push_back(ptr); //Error - copy not allowed
	vec.push_back(std::move(ptr)); //allowed - moving not copying
}
```

- `std::vector<std::unique_ptr<int>> vec;` - create a vector to be filled with `unique_ptr` objects pointing to `int` objects
- `std::unique_ptr<int> ptr {new int {100}}` - creates a unique pointer `ptr` that points to an `int` 
- `vec.push_back(ptr)` you cannot add a `unique_ptr` to a vector using the `push_back()` method since that involves copying ([Documentation](https://cplusplus.com/reference/vector/vector/push_back/))
- `vec.push_back(std::move(ptr))` is allowed because `std::move(ptr)` allows `push_back` to move `ptr` to `vec` rather than trying to copy it - this uses move semantics ([Documentation](https://en.cppreference.com/w/cpp/utility/move)). 
	- `ptr` gives up ownership of the pointer
	- `vec` now owns the pointer
	- `ptr` will be set to `nullptr` 

#### A Better Way to Initialize Unique Pointers

- `make_unique<Type>(args)` is a function
	- returns a unique pointer of the specified `Type`. 
	- the `args` allow us to pass the initialization values into the constructor for the managed object
	- we do not use the `new` keyword

- `std::unique_ptr<int> p1 = make_unique<int>(100);` 
	- creates an `int` object on the heap with a value `100`
	- This object is managed by `p1`

- We can use the `auto` keyword when assigning the pointer
	- `auto p3 = make_unique<Player>("Hero", 100, 100);` 
	- compiler figures out the type of `p3` based on what `make_unique` returns. 
		- in this case `p3` is a unique pointer to a player object 


- `make_unique`
	- was introduced in C++14. 
	- It is more efficient since it does not make any calls to `new` or `delete`

### Shared Pointers

- smart pointer that provides shared ownership of heap objects
- `shared_ptr<T>`
	- points to an object of type `T` on the heap
	- is **not** unique - there can be many shared pointers pointing to the same object on the heap
	- Establishes shared ownership relationship
	- **can** be assigned and copied - this is how we make them access the same heap object
		- remember, when you make a copy you are copying the shared pointer object not the test object on the heap 
	- **can** be moved - for efficiency
	- Does not support managing arrays by default
		- prior to C++17, `shared_ptr` could not be used to manage a dynamically allocated array because it would call `delete` instead of `delete[]`.
		- C++17 has addressed this issue and we can now use them safely for dynamically allocated arrays 
	- When the use count is zero, the managed object on the heap is destroyed 
		- reference counting - every time we instantiate a `shared_ptr` object and have it point or reference to the heap object, we increment the use counter
		- when the reference count becomes 0, we know that nothing is referring to the heap object and it can be safely destroyed
		- simple, but effective - does introduce some overhead, but this usually isn't a big deal


#### Creating, Initializing, Using


```
{
	// Initialize the pointer
	std::shared_ptr<int> p1 {new int {100}};
	
	// Using the pointer
	std:: cout << *p1 << std:: endl; // 100
	*p1 = 200;
	std:: cout << *p1 << std:: endl; // 100
} // p1 out of scope
```

- `std::shared_ptr<int> p1 {new int {100}};` - create a unique pointer to an `int`. That `int` has been created on the heap and initialized to `100`.
	- `p1` now owns that object on the heap. When `p1` goes out of scope, the `int` on the heap will be deallocated **unless** other shared pointers are referencing it
	- You do not need to call `delete` with a smart pointer
- You can use the pointer much the same way as a raw pointer or a `unique_ptr`
	- `std::cout << *p1 << std::endl` - dereferencing `p1` gets the integer that it is pointing to
	- you can use `p1 -> method()` with other classes just like you would with raw pointers (see below)
- Since `p1` is the only `shared_ptr` referencing the integer on the heap, when `p1` goes out of scope the integer will be deallocated from the heap


#### `use_count` Method

The `use_count` method tells use the number of `shared_ptr` objects managing the heap object ([Documentation](https://en.cppreference.com/w/cpp/memory/shared_ptr/use_count))

```
{
	std::shared_ptr<int> p1 {new int {100}};
	std::cout<< p1.use_count() << std::endl; // 1
	
	std::shared_ptr<int> p2 {p1}; // shared ownership
	std::cout<< p1.use_count() << std::endl; // 2
	std::cout<< p2.use_count() << std::endl; // 2
	
	p1.reset();
	std::cout<< p1.use_count() << std::endl; // 0
	std::cout<< p2.use_count() << std::endl; // 1
} // p2 goes out of scope
```

- `p1.reset()` makes `p1` a `nullptr`. It no longer manages the object. Use count decremented by 1.
- when both `p1` and `p2` point to the same object on the heap, then `p1.use_count()` = `p2.use_count()`.
- When `p2` goes out of scope, the use count is decremented by one. Because `p2` was the last shared pointer that pointed to the integer on the heap, then the the memory on the heap is deallocated

#### Vectors and Move

Unlike unique pointers, shared pointers can be copied, assigned, and moved



```
{
	std::vector<std::shared_ptr<int>> vec;
	std::shared_ptr<int> ptr {new int {100}};
	vec.push_back(ptr); // OK - copying allowed
	std::cout << ptr.use_count() << std::endl; // 2
}
```

- `std::vector<std::unique_ptr<int>> vec;` - create a vector to be filled with `shared_ptr` objects pointing to `int` objects
- `std::unique_ptr<int> ptr {new int {100}}` - creates a unique pointer `ptr` that points to an `int` 
- `vec.push_back(ptr)` copies the shared pointer `ptr` to the vector `vec`.
- Because we copied rather than moved `ptr` to the vector, the use_count is now 2
	- integer on the heap is being referenced from `ptr` and from the shared pointer in `vec`.
- because both `ptr` and `vec` go out of scope at the same time, the use count is decremented by 2 and hits 0. The pointers are deleted and the memory is automatically deallocated


#### A Better Way to Initialize Shared Pointers

- `make_shared<Type>(args)` is a function in the standard (`std`) library
	- returns a unique pointer of the specified `Type`. 
	- the `args` allow us to pass the initialization values into the constructor for the managed object
	- This is the prefered way to make shared pointers - `make_shared` is more efficient


- `std::shared_ptr<int> p1 = make_shared<int>(100);` 
	- creates an `int` object on the heap with a value `100`
	- This object is managed by `p1`


- if creating another shared pointer to point to an existing object on the heap, you can **not** use `make_shared` and pass in another pointer that points to that object as the `args`
- you must use `std::shared_ptr` in that case 

```
std::shared_ptr<int> p1 = make_shared<int>(100); //use_count: 1
std::shared_ptr<int> p2 {p1}; // use_count: 2

std::shared_ptr<int> p3;
p3 = p1; // Okay - use_count: 3

auto p4 = make_shared<int>(*p1); //use_count 1

std::shared_ptr<int> p4 = make_shared<int>(p1); // Error
```

- We can use the `auto` keyword when assigning the pointer
	- `auto p4 = make_shared<int>(100);` 
	- compiler figures out the type of `p4` based on what `make_shared` returns.
- Notice that the use_count of the line `auto p4 = make_shared<int>(*p1)` is 1. This is because even though we are passing in a dereferenced `p1` as an argument to `make_shared`, p4 is pointing to a new object on the heap
	- the object that `p4` points to has the same type and value as the object that `p1` points to (i.e. `p1 == p4` is `true`) but they are not the same object

### Weak Pointer

- the weak pointer provides a non-owning "weak" reference to an object on the heap
- `weak_ptr<T>`
	- points to an object of type `T` on the heap
	- does **not** participate in the owning relationship - don't affect the objects they are pointing to 
	- Always created from a `shared_ptr`
	- does **not** icrement or decrement the reference use count
	- Used to prevent strong reference cycles which could prevent objects from being deleted

Use Cases:

1. Prevent Strong reference cycles between two objects
2. When we have a pointer that we use to temporarily reference another object. For example, an iterator pointer that traverses a list of nodes doesn't own them. It just visits them temporarily 


#### Use Case for Weak Pointers - Circular References


- Sometimes when we design programs, we may have two classes where each class refers to the other
- This implies a one-to-one relationship between the classes and this will be reflected in the class objects when we instantiate them
- When they go out of scope, they will be destroyed from the stack, but their shared resources on the heap will not be destroyed and will leak memory
	- A and B keep each other alive 

![A and B classes each with a data field pointing at the other using a shared pointer](/Users/jack/Documents/GitHub/cpp_class/Images for Class Notes/Section 17 - AB Shared Pointer Circular Reference.webp)

![Husband and Wife classes each with a spouse data field pointing at the other using a shared pointer](/Users/jack/Documents/GitHub/cpp_class/Images for Class Notes/Section 17 - Shared Pointer Circular Reference.gif)


- The solution to this problem is to make one of the pointers non-owning or "weak"
- This allows heap storage to be deallocated properly

![A and B classes each with a data field pointing at the other. A has a shared_ptr pointing to B. B has a weak_ptr pointing to A](/Users/jack/Documents/GitHub/cpp_class/Images for Class Notes/Section 17 - AB Weak Pointer Circular Reference.webp)

![Husband and Wife classes each with a spouse data field pointing at the other. Husband has a strong pointer pointing to Wife. Wife has a Weak pointer pointing to Husband](/Users/jack/Documents/GitHub/cpp_class/Images for Class Notes/Section 17 - Weak Pointer Circular Reference.gif)


Notes: when classes refer to each other, you may need a [forward delcaration](https://www.geeksforgeeks.org/what-are-forward-declarations-in-c/)


#### Syntax

```
std::weak_ptr<Type> name {shared_ptr};
```


### Custom Deleters for Smart Pointers

- Sometimes when we destroy a smart pointer, we need more than just to destroy the object on the heap
	- does not occur very often, but there are special use-cases
	- These cases could include the need to close a log file or something like that
- If you use custom deleters, you cannot use `make_unique` or `make_shared`
	- if you need a specialized way to delete your object, you probably need a specialized way to create it too
- Many ways to handle this:

#### Using Functions:

- Write a deleter function that will be called automatically when the smart pointer is deleted
- function will be provided with a raw pointer to the managed object that the smart pointer is referencing
- In the function, do whatever you need to do to relinquish your resources

```
void my_deleter(Some_Class *raw_pointer){
	// custom deleter code
	delete raw_pointer;
}
```

- When you initialize the smart pointer, you need to provide it with the deleter function

```
int main(){
	...
	shared_ptr<Some_Class> ptr {new Some_Class {}, my_deleter}; 
	...
}
```

#### Using Lambda Functions

- A lambda function is an anonymous function that has no name and can be defined in line right where you expect to use it. 
	- lambda functions will be covered more in a later section
- put the lambda function in the same place as you put the `my_deleter` function during the initialization of the smart pointer.
- This code will execute whenver the pointer object is destroyed

```
shared_ptr<Some_Class> ptr (new Some_Class {}, 
	[](Some_Class *ptr) {
	\\custom delete code
};)	
```

### Advice on when to use Smart Pointers

- Use unique pointers as often as you can - they are simple, efficient, and can drop-in for raw pointers in many common use cases
- Use shared pointers for more complex object management semantics involving shared ownership.