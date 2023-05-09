## Section 12 - Pointers and References

### Pointers

A **pointer** is a variable whose value is a memory address of another variable or a function.

- pointers also have a type (like all variables). To use the data that the pointer is point to, you must know its type.

Why Pointers?

- passing by reference is pointers
- We can allocate memory dynamically on the heap or free store. 
- Useful for working with embedded systems to access memory


#### Declaring and Initialize Pointers

Declare a pointer the same way you would declare any variable. The only difference is that you include an `*` before the variable name. It is very important to initialize pointers so they don't point to a random location.

```
// Both of these are valid ways to declare a pointer:

variable_type *pointer_name {nullptr};
variable_type* pointer_name {nullptr};
```

- The variable type of the pointer is the `type` of the data that pointer points to. 
	- the compiler will make sure that the address stored in a pointer variable is of the correct type.


- `nullptr` represents a null pointer value and is the equivalent of initializing with `{ }`.
	- It is best practice to initialize pointers using `{nullptr}` whenever not having them point to a variable or function. 

Examples:

```
int *int_ptr {nullptr}; // points to an integer
double* double_ptr {nullptr}; // points to a double
char *char_ptr {nullptr}; // points to a char

```

- The value of a pointer initialized to `nullptr` is 0.

#### Accessing the Pointer Address

`&` is the address operator 

- unary operator
- evalues to the address of its operand (i.e. `&var` returns the address of the variable `var`).
	- operand cannot be a const or exmpression that evaluates to temp values 
- Just like you can use the `&` in front of a regular variable to get its address, you can also use the `&` in front of a pointer to get the pointer address. 
	- because pointers are variables, they also have addresses 
- `sizeof` a pointer variable gets you the number of bites of storage it takes.
	- all pointers in a program have the same size, regardless of the size of what they are pointing to
	- don't confuse the size of a pointer with the size of what it points to 

#### Storing an Address in pointer variable

```
var_type var {var_value}; // create a variable var

var_type *var_ptr {nullptr}; // initialize var_ptr as a pointer with a null value 
var_ptr = &var; //assign the address of var to var_ptr
```

- `var` is a variable of type `var_type` with value `var_value`
- `var_ptr` is a pointer whose value is the address of `var`. Its type is also `var_type`
- the compiler will make sure that the address stored in a pointer variable is of the correct type

Example:

```
int score {10};
double high_temp {100.7};

int *scr_ptr {nullptr}; //declare and initialize pointer

scr_ptr = &score; // OK

scr_ptr = &high_temp // Error, types don't match
```

#### Dereferencing a Pointer

Dereferencing a pointer: Accessing the data to which the pointer is pointing requires following the pointer. 

If `ptr` is a pointer and has a valid address, then you can access the data at the address contained in the `ptr` using the dereferencing operator `*`

Example:

```
int var {100};
int *ptr {&var};

cout << *ptr << endl; // 100

*ptr = 200; // change the value of var indirectly using the pointer
cout << *ptr << endl; // 200
cout << var << endl; // 200 - you changed the value of var when you set *ptr = 200
```

Dereferencing a pointer leads to an l-value - the address of what `ptr` is pointing to

#### Dynamic Memory Allocation

Allocating storage from the heap at runtime

- we often don't know how much storage we need until we need it
- we can allocate storage for a variable at run time
- Recall that C++ arrays required the sized to be explicitly declared and once declared it was fixed. Vectors could grow and shrink dynamically.
- We can use pointers to acess newly allocated heap storage


Use `new` keyword to allocate storage at runtime

```
int *int_ptr {nullptr};

int_ptr = new int; // allocate an integer on the heap. Assign its addres to int_ptr

cout <<int_ptr << endl; // address of the newly created integer
cout << *int_ptr << endl; // garbage value - dereferenced pointer points to uninitialized value of the newly created int

*int_ptr = 100; // used dereferenced pointer to assign new integer a value

cout << *int_ptr << endl; / 100

```

- Allocated storage is on the heap. It contains garbage data until you initialize it.
	- heap memory is not deleted after the function call (I think) 
- The allocated storage does not have a name. The only way to get to it is via the pointer.
	- Memory leak: occurs when you lose that pointer
- You need to deallocate the storage when you are done with it. Use the `delete` keyword followed by the name of the pointer.
	- the `delete` keyword does not delete the pointer. 

```
int int_ptr {nullptr};
int_ptr = new int; // allocate an integer on the heap
...
delete int_ptr; //frees the allocated storage
```

Use `new[]` to allocate storage for an array

```
int *array_ptr {nullptr};
int size {};

cout << "How big do you want the array? ";
cin >> size;

array_ptr = new int[size]; // allocate array on the heap

...

delete [] array_ptr; // deallocate alloacted storage

```

Note: notice the `[]` between `delete` and the pointer name. These brackets need to be empty.


#### Relationship between Pointers and Arrays

- the value of an array name is the address of the first element in the array
- The value of a pointer variable is an address
- If the pointer points to the same data type as the array element, then the pointer and array name can be used interchangeably (almost)
	- difference is the array name is not a variable

```
int scores [] {100, 95, 89};

cout << scores << endl; // address of the first element in the array
cout << *scores << endl; // dereferencing scores gets you the value of the first element in the array

int *scores_ptr {scores}; 
cout << score_ptr << endl; // address of the first element in scores

cout << *score_ptr << endl; // 100 - value of the first element in scores

cout << (scores == scores_ptr) << endl; // True
cout << (*scores == *scores_ptr) << endl; // True

```

Because we can use an array name and a pointer name almost interchangably, we can use an array name on a pointer

```
int scores [] {100, 95, 89};
int *scores_ptr {scores}; 

cout << scores_ptr[0] << endl; // 100
cout << scores_ptr[1] << endl; // 85
cout << scores_ptr[2] << endl; // 89
```

No need to put the `&` when assigning `scores_ptr` to `scores` because the array name is already an address. 

##### Using pointers in expressions

```
int scores [] {100, 95, 89};
int *scores_ptr {scores}; 

cout << score_ptr << endl; // assume the addres is 0x61ff10
cout << (score_ptr + 1) << endl; // 0x61ff14 - increases by 4 because we are adding the SIZE of one integer 
cout << (score_ptr + 2) << endl; // 0x61ff18 - we incrementing score_ptr by 8 that is 2 integers away


cout << *score_ptr << endl; // 100 - 0th index
cout << *(score_ptr + 1) << endl; // 95 - 1st index
cout << *(score_ptr + 2) << endl; // 89 - 2nd index
```

##### Subset and Offset notation equivalence

```
int array_name[] {1,2,3,4,5};
int *pointer_name {array_name};

```

| Subscript Notation    | Offset Notation           |
|-----------------------|---------------------------|
| `array_name[index]`   | `*(array_name + index)`   |
| `pointer_name[index]` | `*(pointer_name + index)` |


#### Pointer Arithmetic

Pointers can be used in

- assignment expressions
- arithmetic expressions
- Comparison expressions

C++ allows a subset of the arrithmetic operators to work with pointer variables - only make sense when you use them with raw arrays

- `++` increments a pointer to point to the next array element
	- ex: `int_ptr++`
	- assumes that we don't go out of the array - no bounds checking
- `--` decrements a pointer to point to the previous array element 
	- ex: `int_ptr++` 
	- assumes that we don't go out of the array - no bounds checking
- `+` increment a pointer by `n * sizeof(type)`
- `-` increment a pointer by `n * sizeof(type)`
	- Subtracting Two Pointers - determines the number of elements between the pointers
		- both pointers must point to the same data type - complier error otherwise
	- `int n = int_ptr2 - int_ptr2;`
- Can compare pointers using the `==` and `!=` operators - this only compares the values of the pointer variables, not the value of the data
	 - two pointers will only be equal if they are pointing to the same address

	 ```
	 int x {1};
	 int y {1};
	 
	 cout << (x == y) << endl; // true because x and y have the same value
	 
	 int *ptrx = &x;
	 int *ptry = &y;
	 
	 cout << (*ptrx == *ptry) << endl; //true because x and y have the same value
	 cout << (ptrx == ptry) << endl; // false because x and y have different addresses
	 
	int *ptrz {ptrx};
	cout << (z == ptrx) << endl; // true
	```
	 
##### Regarding precedence

`*score_ptr++`

- Precedence of postfix increment operator `var++` is greater than that of the dereference operator `*`.
	- `*score_ptr++` is thus equivalent to `*(score_ptr++)`
	- since the increment is a post-increment, then the effect of `*score_ptr++` is:
		1. `*score_ptr`
		2. `increment score_ptr`

`*++score_ptr`

- Precedence of the prefix increment operator `++var` is the same as that of the dereference operator `*`. That means we use associativity to determine what binds with what.
	- pre-increment and deference associate right-to-left
	- The rightmost operator is `++`, so it binds to `score_ptr` first then the deference. This becomes equivalent to `*(++score_ptr)`. The effect is thus:
		1. `increment score_ptr`
		2. `*score_ptr` 

```
int scores[]{100, 95, 89, 68, -1};
int *score_ptr_post {scores};
    
cout << "*score_ptr++" << endl;
cout << "-------------" << endl;
while (*score_ptr_post != -1){
	cout << *score_ptr_post++ << " "; // 100 95 89 68
}


cout << endl;
    
int *score_ptr_pre {scores};
    
cout << "*++score_ptr" << endl;
cout << "-------------" << endl;
while (*score_ptr_pre != -1){
	cout << *++score_ptr_pre << " "; // 95 89 68 -1
    }
```

#### Const and Pointers

- We can qualify a pointer using `const` several ways: 
	- pointers to constant
		- the data pointed to by the pointers is constant and cannot be changed.		
		- The pointer itself can change and point somewhere else
		- syntax: `const type *var_pointer {&var};`
		
		```
		int high_score {100};
		int low_score {65};
		const int *score_ptr {&high_score};
		
		*score_ptr = 86; // Error - trying to change the data
		score_ptr = &low_score; // OK - changing what the pointer is pointing to
		
		high_score = 95;
		cout << *score_ptr << endl; // 95
		```
		
		In the above example, notice that while `high_score` is not a constant, we cannot change the value using the pointer `score_ptr`. We can, however, change the value of `high_score` directly. This is useful when passing the data to functions that we don't want to modify.
		
	- constant pointers - the pointer is constant but the data is not	
		-  the data pointed to by the pointer can be changed
		-  the pointer itself cannot change and point somewhere else
		-  syntax: `type *const var_ptr {&var};`

		```
		int high_score {100};
		int low_score {65};
		int *const int score_ptr {&high_score};
		
		*score_ptr = 86; // OK 
		score_ptr = &low_score; // Error - cannot change the pointer
		```

		
	- constant pointers to constants 
		- the data pointed to by the pointers cannot be changed
		- the pointer itself cannot change and point somewhere else
		- syntax: `const type *const var_ptr{&var};`

#### Passing Pointers to Functions

We can use pointers and the deference operator to achieve pass-by-reference

- the function parameter is a pointer
- the actual parameter can be a pointer or address of a variable


##### Example

```

// Defining the Function

void double_data(int *int_ptr); //prototype

void double_data(int int_ptr){
	*int_ptr *= 2; // The * here both functions as the dereference operator and the multiplication operator
}

// Calling the Function

int main(){
	int value {10};
	cout << value << endl; // 10
	
	// The function parameter is a pointer to an interger, so it expects an address of an ineger.
	
	double_data(&value); //pass double_data the address of value
	
	cout << value << endl; // 20
	
	int *int_ptr{&value}; // create a pointer to value
	double_data(int_ptr); // you can also pass a pointer
	
	cout << value << endl; // 40
}
```

#### Returning a Pointer from a Function

Functions can return pointers: `type *function();`

- `type` is the type of the pointer
- notice the `*` operator before the function name
- needs to have this format both in the prototype and in the function definition.

Should return pointers to:

- memory dynamically allocated in the function
- To data that was passed in

Never return a pointer to a local variable

Example: take in pointers to two integers, return the pointer to the largest integer. This returns a pointer to data that was passed in.

```
int *largest_int(int *int_ptr1, int *int_ptr2); // prototype

int main(){
	int a {100};
	int b {200};
	
	int *largest_ptr {nullptr};
	largest_ptr = largest_int(&a, &b); // call the function that returns a pointer
	
	cout << *largest_ptr << endl; // 200
	return 0;	
}


// function declaration
int *largest_int(int *int_ptr1, int *int_ptr2){
	if (*int_ptr1 > *int_ptr2){
		return int_ptr1;
	}
	
	else{
		return int_ptr2;
	}
}
```

Example: returnning dynamically allocated memory

the funtion in the example below creates an array of length `size` and initializes the values to `init_value`. It then returns the pointer `new_storage` which points to the newly created array.

```
int *create_array(size_t size, int init_value = 0)}
	int *new_storage{nullptr};
	
	new_storage = new int[size]; // dynamically create the array
	
	for (size_t i{0}; i < size; i++){
		*(new_storage + i) = init_value;
	}
	
	return new_storage; // return the pointer to the newly created array
}

```

Calling the function:

```
int main(){
	int *my_array {nullptr}; // this will be allocated by the function
	
	my_array = create_array(100, 200); //create the array
	
	... // use the array somehow
	
	delete [] my-array; //free the storage
	
	return 0;
}
```

##### Things to not do

If you return a pointer to a local variable in a function it can cause problems because the local variable is deleted when that stage in the activation stack is deleted.

#### Potential Pointer Pitfalls

- unitialized pointers - contain garbage. could be pointing anywhere
	- be sure to initialize pointers using `nullptr` if not immediately assigning to an address
- dangling pointers - pointers that point to memory that is no longer valid. You don't know what the reults will be. 
	- pointer that is pointing to released memory
		- For example: 2 pointers point to the same data. One pointer releases the data with `delete`. The other pointer accesses the released data.
	- Pointer that points to memory that is invalid
		- For example: when a fucntion returns a pointer to a function local variable.    
- not checking if `new` failed to allocate memory
	- If `new` failes an `exception` is thrown. We can use exception handling to catch these.
	- dereferencing a null pointer causes your pointer to crash 
- leaking memory - one of the most common pointer problems
	- forgetting to release allocated memory with delete
	- If you lose your pointer to the storage allocated on the heap, you do not have a way to get to that storage again
	- The memory is orphaned or leaked 

### References

A reference is an alias for a variable. Whenever you are using a reference, you are actually using the variable it refers to.

- References must be initialized to a variable when declared.
	- they can never be null
	- once initialized, references cannot be made to refer to a different variable
- References are very useful as function parameters
- May be helpful to think of a reference as a constant pointer that is automatically dereferenced


#### Syntax

```
type var {value}; // create a variable var of
type &ref {var}; // create a reference ref to var. 

// ref and var must have the same type
```

##### Example

```
int num {100}; // create a variable num
int &ref {num}; // create a reference ref to num

cout << num << endl; // 100
cout << ref << endl; // 100
```

Changing the reference also changes the original value

```
ref = 300;

cout << num << endl; // 300
cout << ref << endl; // 300

```

Changing the origional variable also changes the reference

```
num = 200;

cout << num << endl; // 200
cout << ref << endl; // 200
```

Remember, a reference is an alias to the variable

#### Using references in range-based `for` loop

good for accessing collection elements in each iteration

- Passing using references reduces the overhead because there is no need to make a copy
- If you aren't going to modify the collection elements, make the reference `const`

##### Without references
```
vector <string> stooges {"Larry", "Moe", "Curly"};

for (auto str: stooges){
	str = "Funny"; // str is a copy of the value, so thischanges the copy, not the original
}

for (auto str: stooges){
	cout << str << endl; // Larry, Moe, Curly - no change
}
```

##### Using references
```
vector <string> stooges {"Larry", "Moe", "Curly"};

for (auto &str: stooges){
	str = "Funny"; // str is now an alias for these objects so we are changing the original vector
}

for (auto const &str: stooges){
	cout << str << endl; // Funny, Funny, Funny
}

```

#### Passing references to functions

See Section 11 notes

#### L-Values and R-Values

##### L-Values

- valus that have names and are addressable (have an address in memory)
	- things are addressable if they can be used on the left hand side of an assignment statment 
	- literals (e.g. `100`, `"Jack"`) are not l-values
- modifiable if they are not constants

```
int x {100}; // x is an l-value

string name; // name is an l-value
```

##### R-Values

- anything that is not an l-value is an r-value
- r-value is typically on the right-hand side of an assignment expression
- r-values are 
	- literals
	- a temporary which is intended to be non-modifiable (something that the C++ creates)
- Can be assigned to l-values explicity 
	- l-values can be on the right hand side of the assignment statment 

	
```
int x {100}; // 100 is an r-value

int y = x+200 // (x+200) is an r-value because (x+200) is a temporary variable that the compiler creates

string name {"Jack"}; // "Jack" is an r-value
int max_num = max(20, 30); // max(20,30) is an r-value
```



##### L-Value References

- the references we've used are l-value references, because we are referencing l-values

```
int x = 100; // x is an l-value

int &ref1 = x; //ref 1 is a reference the l-value x
ref1 = 1000; // this is okay since this is the equiavlent of saying x = 1000

int &ref2 = 100; // Error - 100 is an r-value

```

- the same when we pass-by-reference


```
int square(int &n){
	return n*n;
}

int num {10};

square(num); // Ok

square(5); // Error - can't reference r-value 5
```

### When to use pointers vs. references parameters

If working with data structures that can have null values (e.g. arrays), you want to use pointers, not references. 


#### Pass-by-value

- C++ default
- Use when the function does **not** modify the actual parameter and the parameter is small and efficient to copy
	- think twice before passing collections (e.g. vectors, strings) by value because they have more overhead 


#### Pass-by-reference using a pointer

Pass-by-reference using a pointer when (1) the function does modify the actual parameter and (2) the parameter is expensive to copy and (3) it is okay for the pointer to contain a `nullptr` value.

Pass-by-reference using a pointer to a `const` when (1) the function does **not** modify the actual parameter and (2) the parameter is expensive to copy and (3) it is okay for the pointer to contain a `nullptr` value.

Pass-by-reference using a `const` pointer to a `const` when (1) the function does **not** modify the actual parameter and (2) the parameter is expensive to copy and (3) it is okay for the pointer to contain a `nullptr` value and (4) you do **not** want to modify the pointer itself.

#### Pass-by-reference using a reference

Pass-by-reference using a reference when (1) the function **does** modfiy the actual parameter and (2) the parameter is expensive to copy and (3) the parameter will never be `nullptr`.

Pass-by-reference using a `const` reference when (1) the function does **not** modfiy the actual parameter and (2) the parameter is expensive to copy and (3) the parameter will never be `nullptr`.

