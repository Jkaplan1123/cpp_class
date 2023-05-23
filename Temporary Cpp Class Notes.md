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

![Types of Polymorphism](/Users/jack/Documents/GitHub/cpp_class/Images for Class Notes/Section 16 - Types of Polymorphism.png)



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