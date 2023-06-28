## Section 19 - I/O and Streams


### Files, Streams, and Input/Output (I/O)

- C++ uses streams as an interface between the program and input and output devices
	- These devices may be physical (e.g. hard disk) or virtual (e.g. a web service)
-  These streams are independent of the actual device
-  A stream is a sequence of bytes
-  C++ provides different types of streams depending on if we want input or output, but there are also streams that do both
	-  An input stream provides data to the program
	-  An output stream receives data from the program 

#### Common header files for working iwth stream I/O

| Header File | Description                                                              |
|-------------|--------------------------------------------------------------------------|
| `iostream`  | Provides definitions for formatted input and output from/to streams      |
| `fstream`   | Provides definitions for formatted input and output from/to file streams |
| `iomanip`   | Provides definitions for manipulators used to format I/O streams in specific ways         |


#### Commonly used stream classes

| Class          | Description                                                                                                             |
|----------------|-------------------------------------------------------------------------------------------------------------------------|
| `ios`          | Provides basic support for formatted and unformatted I/O operations. It is the base class of most other classes.        |
| `ifstream`     | Provides for high-level input operations on file based streams. (i.e. from files)                                                        |
| `ofstream`     | Provides for high-level output operations on file based streams. (i.e. from files)                                                   |
| `stream`       | Provides for high-level I/O operations on file based streams. It is derived from `ofstream` and `ifstream`.             |
| `stringstream` | Provides for high level I/O operations on memory based strings. It is derived from `istreamstream` and `ostringstream`. |

#### Global stream objects

| Object | Description                                                                                                                         |
|--------|-------------------------------------------------------------------------------------------------------------------------------------|
| `cin`  | Standard input stream - by default "connected" to the standard input device (keyboard). It is an instance of `istream` class.             |
| `cout` | Standard output stream - by default "connected" to the standard output device (console). It is an instance of `ostream` class.            |
| `cerr` | Standard error stream - by default "connected" to the standard error device (console). It is an instance of `ostream` (unbuffered). |
| `clog` | Standard log stream - by default "connected" to the standard log device (console). It is an instance of `ostream` (unbuffered).     |

- Global objects - initialized before main executes
- `cin` and `cout` are buffered streams
	- input from `cin` won't be automatic until the user presses enter
	- output to `cout` occurs only when the stream buffer fills out, we provide an `std::endl`, or we flush the stream.
- best practices is to use `cerr` for error messages and `clog` for log messages
- `cerr` and `clog` are unbuffered - we get input or output from them as we need it.
- we used the `ostream` class when overriding the insert operator 
- we can redirect I/O to make input come from a file or output go to a file


### Stream Manipulators

- streams have useful member functions to control formatting
- can be used on input or output streams - formatting output is much more common
- the time of the effect on the stream varies - sometimes will be set for whole program, sometimes only impact the next object on the stream, sometimes their effect is immediate
- Can be used as a member method that you use with a stream object or as a manipulator function
	- `std::cout.width(10);` is a member method being used on the stream object `cout`
	- `std::cout << std::setw(10);` is a manipulator version - set to be used inline as a stream insertion. This overloads the insertion operator
	- To use manipulators you must include `iomanip`
	- We will focus on manipulator usage

#### Boolean Formatters

- we are using `cout` in these examples but any output streams will work

The default when displaying boolean values is `1` or `0` but sometimes the strings `true` or `false` are more appropriate. We can use stream manipulators to tell our output strings to dipslay `0`/`1` or `false`/`true`, depending on which we want.

Note: with boolean formatting, all further boolean output will be affected

##### Stream Insertion Mode

The default is to display booleans as the integers `1` (for true)`0` (for false).

```
std::cout << (10 == 10) << std::endl; //displays 1
std::cout << (10 == 20) << std::endl; //displays 0
```

We can use `std::boolalpha` as a stream insertion operator to display booleans as the strings `true` or `false`. 

```
std::cout << std::boolalpha; 

std::cout << (10 == 10) << std::endl; //displays true
std::cout << (10 == 20) << std::endl; //displays false
```

With boolean formatting, all futehr boolean output will be affected. To go back to  displaying `0` and `1`, we use `std::noboolalpha`

```
std::cout << std::noboolalpha;

std::cout << (10 == 10) << std::endl; //displays 1
std::cout << (10 == 20) << std::endl; //displays 0
```

##### Method Version

We can set the format of boolean types using the `setf` method.

- `std::cout.setf(std::ios::boolalpha)` is the same as the `std::boolalpha` insertion operator.
- `std::cout.setf(std::ios::noboolalpha)` is the same as the `std::noboolalpha` insertion operator.
- To reset to default, use the `resetiosflags` method
	- `std::cout << std::resetiosflags(std::ios::boolalpha)` 

#### Integer Formatters

- integers have four basic formatting option:
	-  base: base 10 decimal (`dec`), base 8 octal (`oct`), base 16 hexadecimal (`hex`)
	- `noshowbase`/`showbase`- determines if a prefix will be displayed to clarify is a number is decimal, octal, or hexadecimal
		- the prefix for a hex number is `0x` and the prefix for an octal number is `0` 
		- if `showbase`, the number will consist of the appropriate prefix followed by the rest of the number in the appropriate base. 
			- For example, the number 10 will be desplayed as 10 in decimal, 012 in octal, and 0xa in hexidecimal
	- `uppercase`/`nouppercase` - determines if the letter prefix and hex values will be lower or upper case
	- `showpos`/`noshowpos` - determines if a `+` will be displayed for positive numbers
- the default for displaying integer values is: `dec`, `noshowbase`, `nouppercase`, `noshowpos`
- integer stream manipulators affect all further output to the stream



```
int num {255};

std::cout << std::dec << num << std::endl; // displays 255
std::cout << std::hex << num << std::endl; // displays ff
std::cout << std::oct << num << std::endl; // displays 377
```

All three numbers have the same value but display as `255` for decimal, `ff` for hexadecimal, and `377` for octal. You can see why the prefix may be important to prevent confusion

```
int num {255};

std::cout << std::showbase;
std::cout << std::dec << num << std::endl; // displays 255
std::cout << std::hex << num << std::endl; // displays 0xff
std::cout << std::oct << num << std::endl; // displays 0377
```

Toggling on `showbase` changes the outputs to `255` for decimal, `0xff` for hexadecimal, and `0377` for octal. The prefix can help carify any confusion.


You can also use the `setf` method to change these settings and use the `resetiosflags` to reset the flags to the default

#### Floating Point Numbers

- `setprecision` - the number of digits displayed (i.e. the number of significant figures)
	- the floating point number is rounded to the nth digit
	- e.g. if you are displaying 6 digits then the number `1234.5678` will display as `1234.57` even though the value is still stored without rounding
	- if c++ can't display the number in the given amount of significace, then it will use scientific notation (e.g. `123456789.987` will display as `1.23457e+008`)
- `fixed`/`scientific`/`hexfloat`/`defaultfloat` - not fixed to a specific 
	- [Documentation](https://en.cppreference.com/w/cpp/io/manip/fixed) 
	- when you use the `fixed` manipulator, precision is handled differently. In this case the precision refers not to the total number of digits but instead to the number of digits to the right of the decimal point.
- `showpoint`/`noshowpoint` - controls whether the decimal point is always included in floating point representation
	- `noshowpoint` removes trailing zeros to the right of the decimal point. A floating point representation of a whole number will not have a decimal point. 
- `uppercase`/`nouppercase` - controls whether uppercase characters are used when displaying in scientific notation
- `showpos`/`noshowpos` - determines if a `+` will be displayed for positive numbers


- The default for displaying floating point values is
	- `setprecision` is set to 6 digits
	- `defaultfloat` - no fixed set number of digits to the right of the decimal point
	- `noshowpoint`
	- `nouppercase`
	- `noshowpos`

- To reset the floating point format back to the general format:
	- `unsetf` method
	- `ios` manipulator

#### Align and Fill

- formatting options what work with any type of data

- field width (`setw`) - changes the width of the next input/output field
	- not set by default
	- to return to default use `setw(0)`
	- applies only to the next data item 
- justification (`internal`/`left`/`right`) - sets the placement of fill characters
	- default is `left` when no field width set, `right` when using field width 
	- `internal` only applies to integer, floating point, and monetary output
	- justification will only be used if associated with a set width manipulator
	- it is reccomended to use both the field width and justification manipulators together for clarity's sake

```
double num {1234.5678};
std::string hello{"Hello"};

std::cout << std::setw(10) 
			<< std::left
			<< num  //only affects num
			<< hello << std::endl;
```

- fill (`setfill`) - specify the fill character
	- not set by default, blank space is used
	- only works when an output has a field width associated with it. The fill character fills all the empty spaces not taken up by the output
	- this is persistant

### Reading from a text file

`fstream` and `ifstream` are commonly used for input files

1. `#include <fstream>`
2. Declare an `fstream` or `ifstream` object
3. connect it to a file on your file system - opens it for reading
4. read data from the file via the stream
5. close the stream (close the file)


#### Declaring an `fstream` of `ifstream` object and connect it to a file on your file system

```
std::fstream in_file {".../path/to/myfile.txt,
							std::ios::in};
							
std::fstream in_file {".../path/to/myfile.txt,
					  std::ios::in | std::ios::binary};
```

The initializer takes two arguments. The first specifies the name of the file. The file name is very OS-specific and IDE-specific. We are assuming in this code that the file exists and is where it is supposed to be.

The second parameters specifies the mode and anoy other properties of the file that is being opened. We are using `std::os::in`, which opens the file in input mode. This allows us to read from the file but no write to it. By default, files are opened in text mode. The first example is opening the file in text mode. The second example is opening the file in binary mode. Binary mode is necessary for reading non-text files that contain binary data.

The `fstream` class allows you to open a file for both input and output. If you are only opening for input, it is more common to use the `ifstream` class.

We create an `ifstream` object the same way we create an `fstream` object.

```
std::fstream in_file {".../path/to/myfile.txt,
							std::ios::in};

std::fstream in_file {".../path/to/myfile.txt}
```

The `std::ios::in` is optional because it is already the default, so the first two declarations have the same effect. 


Often we do not know the input file at compile time and we have to get it from the user or from some other source at runtime. 

```
std::ifstream in_file; // declare the stream object
std::string filename;
std::cin >> filename; // get the file name
```

Once we have the file name, we can use it with the open method on the stream object to open the file

```
in_file.open(filename);
//or 
in_file.open(filename, std::ios::binary); //if binary
```


We need to sure that we succesfully opened the file before we start reading from the file. There are a few ways to approach that.

The `is_open` method will return a boolean indicating whether the file is open for processing or not.

```
if (in_file.is_open()){
	// read from file
}
else {
	// file could not be opened 
	// or we cannot read from it
	// handle this however you want
}
```

We can test the stream object itself. If it could not open the file then it will return `false`

```
if (in_file){
	// read from file
}
else {
	// file could not be opened 
	// or we cannot read from it
	// handle this however you want
}
```

#### Closing a File

Always close any open files to flush out any unwritten data

```
in_file.close()
```

#### Reading from a file

There are many ways to read from a file. 

We can use the extraction operator (`>>`) to read from formatted text files the same way we used it with `cin` to get input from the keyboard.


Suppose we have an integer, a double, and a string in a text file and we want to read these into our program.

Text File:

```
100
255.67
Larry
```

Assume we have created `in_file` successfully. We can read from the file using `>>`

```
int num {};
double total {};
std::string name {};

in_file >> num;
in_file >> total >> name;
```


Sometimes we want to read files an entire line at a time. The extraction operators will stop when they see any white space. Therefore we can use `getline` to read the file one line at a time.

Text file:

```
This is a line
```

Source code:

```
std::string line {};
std::getline(in_file, line);
```

We can use loops to read all the lines of text in a file.

```
// assume the program is in main() and all the 
// appropriate packages are installed 

in_file.open("../poem.txt"); // open file
if (!in_file) {
    std::cerr << "Problem opening file" << std::endl;
    return 1; // exit the program (main)
}
std::string line{};
while (!in_file.eof()) { // while not at the end
	 std::getline(in_file, line); // read a line
    std::cout << line << std::endl; // display the line
}
    
in_file.close(); // close the file

```

We can write the while loop differently:

```
while (std::getline(in_file, line)) { //read a line
    std::cout << line << std::endl; // display the line
}
```

Since the statements only return a true value when the read was successful, when we reach the end of the file or some other error condition is encountered, they will return `false` and the loop will terminate. 

- We can also read a file one character at a time using the `get` method.
	- the characters come in unformatted 


For now, it is reccomended that you keep `.txt` files in the same folder as the `.cpp` file 

### Writing to a Text File

`fstream` and `ofstream` are commonly used for output files

1. `#include <fstream>`
2. Declare an `fstream` or `ofstream` object
3. Connect it to a file on your file system
4. Write data to the file via the stream
5. Close the stream and the file

- By default, output files will be created if they don't exist. 
- If we provide a path along with the file name, then we must make sure that path exists. If it does not exist then we will get an error when creating the file. 
- If the file already exists then it will be overwritten or truncated unless we specify that we want to append to the contents of the existing file
- We can write in text more or in binary mode

Creating an output file object using `fstream` is very similar to creating an input file object using `fstream`. `fstream` can be used to read and write from the same file.

```
std::fstream out_file {".../path/to/file", std::ios::out}
```

The `ofstream` class is exculusivley for output files. Creating an output file object using the `ofstream` class is similar to creating an input file object using `ifstream`.

```
std::ofstream out_file {".../path/to/file.txt", std::ios::out}

std::ofstream out_file {".../path/to/file.txt"}
```

Because `ofstream` is only for output, then the `std::ios::out` parameter is optional.


#### Choices when opening a file

- When we open a file for output, we have a few choices for how we want to open the file
- The default is the file is opened for truncation
	- truncation can be called out explicitly using `std::ios::trunc` but this parameter is optional because  it is the default

	```
	std::ofstream out_file {".../path/to/file.txt", 
								 std::ios::trunc};
								 
	std::ofstream out_file {".../path/to/file.txt"};
	```

- We can append to the end of an existing file using the `std::ios::app` flag when opening the file.
 
	```
	std::ofstream out_file {".../path/to/file.txt", 
								 std::ios::app};
	```
	
- When we want to open a file that exists and we want to set the initial position of the next write to the end of the existing file, we use the `std::ios::ate` flag.


- For more context on these various flags, see the [C++ Documentation](https://cplusplus.com/reference/fstream/ofstream/open/) and this [Stack Overflow](https://stackoverflow.com/questions/10359702/c-filehandling-difference-between-iosapp-and-iosate#:~:text=ios%3A%3Aapp%20%22set%20the,time%20you%20flush%20your%20stream.) answer (which also references the documentation).

#### Using the `.open()` method

We can first create an output stream object using `ofstream` then use the `open` method to open it. This is the same process option that we had for input files and is useful when you do not know the file name at compile time.

```
std::ofstream out_file;
std::string file_name;
std::cin >> file_name;

out_file.open(filename , FLAGS}
```

If you want multiple flags for the file, then separate them with the `|` operator.

#### Checking to see if the file is open

The syntax is the same as for reading from a file

The `is_open` method will return a boolean indicating whether the file is open for processing or not.

```
if (out_file.is_open()){
	// read from file
}
else {
	// file could not be opened 
	// or we cannot read from it
	// handle this however you want
}
```

We can test the stream object itself. If it could not open the file then it will return `false`

```
if (out_file){
	// read from file
}
else {
	// file could not be opened 
	// or we cannot read from it
	// handle this however you want
}
```


#### Closing the file

It is incredibly important to close any output file since it flushes any buffers that may not have been written yet.

```
out_file.close();
```

#### Writing to a Text File

##### Using the insertion operator (`<<`)

We can use the insertion operator for formatted write the same way we used it with `cout`. This is the most common way of writing to a text file.

```
int num {100};
double total {255.67};
std::string name {"Larry"};

outfile << num << "\n"
		<< total << "\n"
		<< name << std::endl;
```

The above program results in the text file:

```
100
255.67
Larry
```

Note: `endl` flushes out any unwritten buffers

The `put` method writes a single character to a test file

### Using String Streams

- allow us to read or write from strings in memory like we would read and write to files
- very powerful - very useful for data validation

- Three classes we can use when using string streams: `stringstream`, `istringstream`, `ostringstream`
	- `stringstream` allows us to read and write from string streams (equivalent of `fstream`)
	- `istringstream` - allows us to read from string streams (equivalent of `ifstream`)
	- `ostringstream` - allows us to write to string streams (equivalent of `ofstream`)

1. `#include <sstream>`
2. Declare an `stringstream`, `istringstream`, or `ostringstream`
3. Connect it to a `std::string`
4. Read/write the data from/to the string steam using formatted I/O


#### Example

##### Reading data from a string stream

```
int num {};
double total {};
std::string name {};
std::string info {"Moe  100.  1234.5"};

std::istringstring iss{info};
iss >> name >> num >> total;
```

##### Writing to a string stream

```
int num {100};
double total {1234.5};
std::string name {"Moe"};

std::ostringstring oss{};
oss << name << " " << num << " " << total;
std::cout << oss.str() << std::endl;

// outputs "Moe 100 1234.5"
```

#### Validating Input with `stringstream`

The following code validates user input. 

```
std::string input{};

std::cout << "Enter an integer: ";
std::cin >> input;

std::stringstream ss{input};
```

- The program asks the user to input an integer.
- The program writes whatever the user enters to the string `input`. 
- It then creates an `stringstream` object `ss` that it connects to the string `input`.

```
int value {};
if (ss >> value){
	std::cout << "An integer was entered";
	}
else {
	std::cout << "An integer was not entered";
}
```

- It then declares an integer `value`
- If the data in `ss` can be assigned to `value` then that data was an integer
- If the data in `ss` **cannot** be written to `value`, then the data was **not** an integer

```
// discards the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
```

This discards the input buffer, look this up 