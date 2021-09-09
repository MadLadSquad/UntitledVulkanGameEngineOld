# Code Style Guidelines
The following code style guidelines should be followed
## Braces and whitespaces
When declaring a scope, always have the opening bracket on a new line like this
```cpp
while (true)
{
    doStuff();
}
```
When declaring functions, there is no space between the last character of the function's name and the `(` symbol
```
void iAmAFunction();
```
It's the opposite when talking about `while` loops, `for` loops, `if` and `switch` statements
```cpp
while (true)
{
    doStuff();
}
```
There is no padding for arguments of loops, functions or statements
```cpp
while (true)
{
    doStuff();
}
```
When declaring an inline scope for any purpose, always add padding to the start and the end
```cpp
int arr[5] = { 1, 2, 3, 4, 5 };

iTakeAFunctionPointer([&](){ doStuff(); });

iUseStdInitializerList({ 1.0f, 1.0f, 1.0f });

void iAmAFunctionWithAnInlineScope() { doStuff; };
```
If declaring a function with an inline scope(not to be confused with inline functions), add a space between the scope and the `)` symbol
```cpp
void iAmAFunctionWithAnInlineScope() { doStuff; };
```
When using boolean or bitwise operators, always add padding between the 2 variables
```cpp
if (a == b)
    doStuff();
    
int e = c | d;
```
When assigning a value to a variable, always add padding
```cpp
int a = 5;
```
When filling a long initializer list always put the opening bracked on a new line, but keep the equal sign on the same line as the variable's declaration
```cpp
SomeBigStruct bigStruct = 
{
    10, 20, 30, 40, 50, 60
};
```
Since we use C++20 we have access to designated initializers. This means that if a struct is long and contains a lot of different values of different types, you can initialize it like this
```cpp
SomeVeryLargeStruct largeStruct =
{
    .type = STRUCT_TYPE_SOMETHING,
    .attributes = &attributes,
    .usesAcceleration = false,
};
```
Sometimes when used for specific purposes, arrays can have different formatting. An example of that is an index buffer
```cpp
unsigned int indices[] = 
{
    0, 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2
};
```
When using attributes such as `const` and `noexcept` after the `)` symbol of a function, always add a space between them and the `)` symbol
```cpp
void test() const
{

}
```
When declaring a pointer, declare it like this
```cpp
int* a = nullptr
```
same goes with references
```cpp
int& a = b;
```
When you want to pass the memory address of a variable or dereference a pointer, type it like this
```cpp
int a = *b;
int* c = &d;
```
## Naming
### Files
All files should be named like this
```
ThisIsAFile.type
```
or like this for single word names
```
level.yaml
```
with the exception of source files, which are always using capital letters, even if the name is only 1 word
```
Window.cpp
```
When creating source files, always add these extensions
```
.cpp for C++ files
.hpp for header files
.c for C files
.h for files used only in C APIs
```
When using YAML files, always use the long extension name
```
test.yaml
```
### Code
When naming types like structs, classes, typedefs, enums, namespaces, etc always make them like this
```cpp
struct IAmAStructureType;
```
When making a variable always name it like this
```cpp
int iAmAnIntegerVariable = 10;
```
When creating functions always make them like this
```cpp
void iAmAFunction();
```
Single letter varibales or abbriviations are acceptable when naming an iterator, an index in a loop or a small temporary variable. It should be noted that we have a naming standart to always call the iterator in a range based for loop `a`, while calling the index in a regular for loop `i` and a full iterator as `it`, though these are more of an unofficial rules so you are not required to follow them
```cpp
for (auto& a : array)
{
    doStuff();
}

for (int i = 0; i < 10; i++)
{
    doOtherStuff();
}
```
When developing a class that is going to have both an internal class and an interface class use the following naming
```cpp
class WindowInternal;// Will hold all internal engine operations here
class Window; // A regular name to give an interface
```
though there is a variation where you can do the reverse
```cpp
class Settings; // The internal setting class
class SettingsInterface; // An the interface into the settings class
```
