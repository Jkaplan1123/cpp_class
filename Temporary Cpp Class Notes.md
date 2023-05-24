## Section 16 - Polymorphism

### What is Polymorphism?

- [Polymorphism](https://www.geeksforgeeks.org/cpp-polymorphism/) allows us to think more abstractly when writing programs.
	- Let C++ figure out which function to call
- Two Types of Polymorphism: 
	- Compile Time - includes what we have already learned in this course
		- function overloading
		- operator overloading
	- Run-time Polymorphism - uses [function overriding](https://www.geeksforgeeks.org/function-overriding-in-cpp/) and [virtual functions](https://www.geeksforgeeks.org/virtual-function-cpp/)
		- we cover run-time polymorphism in this section 
	- Understanding run-time vs. compile time [article](https://stackoverflow.com/questions/846103/runtime-vs-compile-time)

![Types of Polymorphism](/Users/jack/Documents/GitHub/cpp_class/Images for Class Notes/Section 16 - Types of Polymorphism.png)


- for dynamic polymorphism we must have:
	- inheritance
	- a Base class pointer or Base class reference
	- must declare the methods we want dynamically bound as virtual

#### A non-polymorphic example - Static Binding

- Assume a class hierarchy the same as used in the Section 15 challenge:
	- Account
		- Savings
			- Trust 
		- Checking 
- Assume each class in the hierarchy has its own `withdraw` method

```
Account a;
a.withdraw(1000); // Account::withdraw

Savings b;
b.withdraw(1000); // Savings::withdraw

Checking c;
c.withdraw(1000); // Checking::withdraw

Trust d;
d.withdraw(1000); // Trust::withdraw
``` 

The compiler binds which withdraw method to use at compile time (statically). The compiler is binding the calls to `withdraw` based on the information that it has about the objects when they were declared in teh source code. 

```
Account *p = new Trust();
p -> withdraw(1000); // Account::withdraw
```

- `Account *p = new Trust();`
	- `p` is a pointer to an `Account` object. It containts the address of that `Account` object
	- We create a `Trust` object on the heap and assign its address to `p`.
		- This is allowed because `p` can hold addresses of accounts and `Trust` is an `Account` by inheritance.
- What happens when we call the `withdraw` method for `p` (i.e. `p -> withdraw(1000);`)?
	- we are using static binding by default, so the compiler doesn't really know what type of account object `p` is pointing to at runtime. 
	- It just knows that `p` is pointing to an `Account`, so it bind the withdraw call to `Account::withdraw()` at compile time. 
	- We may not be expecting this. We probably wanted to call `Trust::withdraw()`.

#### Example with Run-Time/Dynamic Polymorphism

Assume we have opted into runtime polymorphism: the `withdraw` method is virtual

```
Account a;
a.withdraw(1000); // Account::withdraw

Savings b;
b.withdraw(1000); // Savings::withdraw

Checking c;
c.withdraw(1000); // Checking::withdraw

Trust d;
d.withdraw(1000); // Trust::withdraw

Account *p = new Trust();
p -> withdraw(1000); // Trust::withdraw
``` 

- The behavior of `a`, `b`, `c`, and `d` is all the same as before since we are not using base class pointers or references.
	- Statically bound at compile time 
- This time, `p->withdraw(1000);` calls `Trust::withdraw`.
	- virtual functions tells the compiler not to bind at compile time but instead to defer the binding to runtime.

### Using a Base-Class Pointer

- Use the `Account` class hierarchy defined above.
- Assume that this class hierarchy is now using dynamic polymoprhism

Create pointers to four different `Account` classes

```
Account *p1 = new Account();
Account *p2 = new Savings();
Account *p3 = new Checking();
Account *p4 = new Trust();
```

C++ will figure out which method to bind at runtime
 
```
p1 -> withdraw(1000); // Account::withdraw
p2 -> withdraw(1000); // Savings::withdraw
p3 -> withdraw(1000); // Checking::withdraw
p4 -> withdraw(1000); // Trust::withdraw

// delete the pointers
```

A better use case for Base Class pointers:

```
Account *array [] = {p1, p2, p3, p4}

for (auto i=0; i < 4; i++){
	array[i]->withdraw(1000);
}

// delete the pointers
```

- When you loop through the array, the correct `withdraw` method will be called based on the type of object to which each pointer points.
	- If you were to add another type of `Account` (e.g. a bond account), the code will still work 
- This works with other collections, such as a `vector`. 
- Note: be careful when using raw pointers and collections (especially vectors). It is better to use smart pointers.

### Virtual Functions

#### Background

- Base class functions redefined in a Derived class are bound statically
	- creates a specialized version of the fucntion specific to the derived class 
- Overridden functions are bound dynamically
	- we do this by declaring the function to be **virtual** 
- Virtual functions are overridden - allows us to think abstractly
	- we can treat all objects in the hierarchy as objects of the Base class


#### Declaring Virtual Functions

- Declare the function you want to override as virtual in the Base class
	- preceed the function prototype with the **`virtual`** keyword
	- This makes the method a virtual function, which means it can be overridden in derived classes and bound dynamically at runtime when we use a base class pointer or reference.		 
- Virtual functions are virtual all the way down the hierarchy from this point
- Dynamic polymorphism only via `Account` class pointer or reference
	- we will not get dynamic polymorphism if we create a `Savings` class pointer and try to use with trust: 
	- `Savings *ptr = new Trust();` does not allow for dynamic polymorphism the way `Account *ptr = new Trust();` does

##### Declaring Virtual Function Example

```
class Account{
public:
	virtual void withdraw (double amount);
	...
};
```

`withdraw` is now a virtual function and it will be bound dynamically at runtime when we use an `Account` 

#### Overriding the Virtual Function in the Derived Class

- the derived function will be implicitly virtual, so we don't have to use the `virtual` keyword. Nonethless, it is best practice to do so.
- In order to override a base class's function, the function's signature and return type must match exactly
- If they don't match exaclty, the compiler will treat it as a redefinition and statically bind it.
- RemembeR: virtual functions are dynamically bound only when we call them via a base class pointer or reference. Otherwise, they are statically bound. 


```
class Checking : public Account{
public:
	virtual void withdraw(double amount);
	...
};
```

### Virtual Destructors

#### Problem

- problems can happen when we destroy polymorphic objects
- If a derived class object is destroyed by deleting its base class pointer, and that class does not have a virtual destructor, then the behavior is undefined in the C++ standard
- Derived objects must be destroyed in the correct order starting at the correct destructor

#### Solution

- If we have a class and that class has virtual functions, the that class must always provide a virtual destructor
- Once we provide a virtual destructor in the base class, then all destructors in the derived classes are also virtual. We don't have to provide the `virtual` keyword again, but it is best practice to do so.


```
class Account {
public:
    virtual void withdraw(double amount);
    virtual ~Account();
    ...
}; 
```

#### Rule of Thumb

- If there is a virtual function in the Base class, then provide a virtual destructor
- If the classes are meant to be used polymorphically via a Base class pointer, then provide a virtual destructor
	- this usually means that there is a virtual function
- If the class is **not** intended to be used polymorphically then do **not** provide a virtual destructor


A class can only have a single destructor. You do not need both since the virtual destructor works both with dynamic polymorphis and with static binding


### Override Specifier

- we can override Base class virtual functions
- The function signature and return type must be exactly the same - if they are different then we have redefinition not overriding
	- redefinition is statically bound
	- overriding is dynamically bound
- C++11 provides an `override` specifier to have the compiler ensure overriding


```
lass Base {
public:
    virtual void say_hello() const;
    virtual ~Base() {};
};

class Derived: public Base {
public:
    virtual void say_hello();
    virtual ~Derived() {}
};
```

Notice that in the `say_hello()` method in the `Derived` class, there is no `const` qualifier. That means that you are **redfining**, not **overriding**. This is legal so the code compiles.

If you want to make sure that you override the function, add the `override` keyword after the function definition. 

```
class Derived: public Base {
public:
    virtual void say_hello() override;
    virtual ~Derived() {};
};
```

The `override` keyword will cause a compiler error if the function is not overriding. 

### Final Specifier

C++11 provides the `final` specifier

#### Class Level
when used at the class level - prevents another class from inheriting from this class

```
class My_class final{
	...
};

class Derived final: public Base{
	...
};
```

#### Method Level
when used at the method level - prevents virtual method from being overrideen in derived classes 

```
virtual void say_hello() final;
```


```
Class Base {
public:
    virtual void say_hello() const;
};

class Derived: public Base {
public:
    virtual void say_hello() const override final; // prevent further overriding
};

class Another: public Derived {
public:
    virtual void say_hello()  const override; // Errror cannot override final method
};
```

### Using Base Class References

- We can use base class references with dynamic polymorphism
- This is useful when we pass objects to functions that expect a Base class reference


```
Account a;
Account &ref0 = a;
ref0.withdraw(1000); // Account::withdraw

Trust t;
Account &ref1 = t;
ref1.withdraw(1000); // Trust::withdraw
```

Example with function that expects an `Account` reference as an argument

```
void do_withdraw(Account &account, double amount) {
    account.withdraw(amount);
}

Account a1;
Savings a2;
Checking a3;
Trust a4;
   
do_withdraw(a1, 1000); // Account::withdraw
do_withdraw(a2, 2000); // Savings::withdraw
do_withdraw(a3, 3000); // Checking::withdraw
do_withdraw(a4, 4000); // Trust::withdraw
```

Functionts that take in Base class references allow us to think in the general, abstract case rather than in the specifics.

### Pure Virtual Functions and Abstract Classes

An abstract class works like a template for concrete classes, analogous to a template for objects (as seen in the concrete classes we've been defining up to this point)
 
Pure virtual functions are placeholder method names that form part of this template (abstract class), to be defined in derived concrete classes

[Geeks for Geeks article](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)
 
#### Abstract Class Overview

- Abstract Class: a class that cannot be instantiated
	- these classes are used as base classes in inheritance hierarchies
	- often refered to as abstract base classes
	- e.g. if we have an abstract class `Shape`, we cannot create any `Shape` objects. We may, however, have classes (e.g. `Triangle`) that derive from `Shape` and that we can use to create objects.
	- must contain at least one pure virtual function
- Concrete class: a class form which we can instantiate objects. 
	- This is the class we have been dealing with up until this point
	- All their member functions must be defined 


#### Pure Virtual Functions

- Pure virtual functions are used to make a class abstract
	- whatever class a pure virutal function is in becomes an abstract class and cannot be instantiated 
- specified with `=0` in its declaration: 
	- ex: `virtual void function () = 0;` is a pure virutal function
- Typically do not provide impelemenatations - up to the derived, concrete classes to provide this behavior

- The derived class must override the pure virutal function of the base class
	- if this does not happen, then the Derived class is also abstract
- A pure virtual function is used when it doesn't make sense for a base class to have an implementation
	- ex: `virtual void draw() = 0;` for the abstract `Shape` class  

#### Example Abstract Base Class with Pure Virtual Functions

```
class Shape {			// Abstract Base class
private:
       // attributes common to all shapes
public:
      virtual void draw() = 0; // pure virtual function
      virtual void rotate() = 0; // pure virtual function
      virtual ~Shape() { }
};
```

It makes no sense to implement `draw` and `rotate` in the `Shape` class because `Shape` is too generic to have a way to meaningfully draw or rotate

##### Concrete Class `Circle` inheriting from `Shape`
```
class Circle: public Shape {     // Concrete class
public:
    virtual void draw() override {
        std::cout << "Drawing a circle" << std::endl;
    }
    virtual void rotate() override {
        std::cout << "Rotating a circle" << std::endl;
    }
    virtual ~Circle() {}
};
```

The `Circle` class overrides the pure virtual functions. This allows it to be a concrete class.

#### Polymorphism and Abstract Base Classes:

Abstract Base Classes cannot be instantiated

```
Shape shape; // Error
Shape *ptr = new Shape(); //Error
```

We can use pointers and references to dynamically refer to concrete classes derived from them

```
Shape *ptr = new Circle();
ptr-> draw();
ptr->rotate();
```

### Abstract Classe as Interfaces

C++ does not provide a keyword or way to create an interface as part of the C++ core language, so we use abstract classes with pure virtual functions to achieve the concept of an interface

- An **interface class** is an abstract class that has only pure virtual functions
- These functions provide a general set of servies to the user of the class
	- services provided as `public`
- Each subclass is free to implement these services as needed
- Every service (method) must be implemented
	- The service type information is strictly enforced - when overriding the prototypes must match perfectly


- Suppose we want to be able to provide `Printable` support for any object we wish without knowing it's implementation at compile time
	- `std::cout << any_object << std::endl;`
- We can do this by creating a `Printable` interface class that provides the service in terms of a pure virtual function
	- our user-defined class can simply be derived from printable and override this pure virtual function 
	- `any_object` must conform to the `Printable` interface

#### Printable Example

```
class Printable {
    friend std::ostream &operator<<(std::ostream &os, const Printable &obj);
public:
    virtual void print(std::ostream &os) const = 0;
    virtual ~Printable () {};
};

// Friend function that allows us to print any object that conforms to this interface - Does not technically need to be a friend function because it isn't using any private attributes of Printable

std::ostream &operator<<(std::ostream &os, const I_Printable &obj) {
    obj.print(os);
    return os;
}
```

`obj.print(os)` dynamically binds to whatever object type was passed in since we know that the object is printable and we have a reference to it

```
class Any_Class : public Printable {

public:

	// must override Printable::print()
	virtual void print(ostream &os) override{
		os << "Hi from Any_Class" ;
	}
	...
};
```

For any class to be printable, it must be derived from `Printable` and override the pure virtual function `print` that is in the printable interface.

```
void fun1 (Any_Class &obj){
	std::cout << obj << endl;
}

void fun2 (Printable &obj){
	std::cout << obj << endl;
}

int main(){
	
	Any_Class *ptr = new Any_Class();
	std::cout << *ptr << std::endl;
	
	fun1(*ptr); //"Hi from Any_Class"
	fun2(*ptr); //"Hi from Any_Class"
	
	return 0;
}
```

Sometimes classes that are designed to be used as interface classes are named with an *I_* proceeding the class name. For example: `I_printable`.