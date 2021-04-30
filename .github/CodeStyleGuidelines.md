# Code Style Guidelines
This document defines the code style guidelines everyone needs to follow.
## For the engine developer
### For everyone
1. Variable and function names look like this
```cpp
int iAmNumber = 0;

void iPrintANumber(int thisArgIsANumber);
```
2.  Bools start with lower case 'b'
3.  Types are named like this
```cpp
ThisIsAType
```
4.  Defines and enum members are typed like this
```cpp
#define I_AM_A_MACRO

enum MyEnum
{
    I_AM_AN_ENUM_MEMBER
};
```
5.  Scope open bracket is on a new line
## Components
1.  Components are always structs
2.  Variables in components are always public if they are used in the process of saving the component to a level
3.  Components can contain functions
4.  Components used for debug should be marked as such
5.  Components that are editor runtime only should be marked as such
6.  Always make sure to fill your component with default data when creating it
## Internal classes
1.  All variables are private and accessed with getter and setter functions
2.  Classes should always have some type of constructor
3.  Classes can be global variables only if and when there needs to be 1 instance of them
## UI
1.  Editor UI should be label on the right, content on the left
2.  An editor UI widget can be contained in the GLRenderer.cpp or in a seperate file in a namespace with the name of the widget
3.  The render function for UI is a static function that is always called display
## For the game developer
Coming soon
