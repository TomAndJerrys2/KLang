# KLang

# <i>A Mid-Level, Multi-functional Language</i>

"I'm trying to add new and interesting stuff everyday - An error message isn't to bad but thousands of them make you question
why on earth you would ever make a language. It's not supposed to be revolutionary just tidy and useful. Because tidy and
useful is all anyone ever wanted. Everythings included and the stuff that isn't. Well. The language let's you dream big
so get to it" - <i>Kyle Brady 2025</i>

KLang was made as a side-project inspired by the will and curiosity of the cogs and wheels that drive the everyday compiler.
Since picking up the interest it's been interesting to see how each piece works and how, eventually, it does all fit together
in a nice neat picture. While not necessary, KLang was made to support an array of functions from Web development all the way
to Game Development and Database management. The Syntax and Compile resemnble and are built from C. Pure C. Nothing more or
nothing less was needed. While the language itself bears features to others like rust and C++, it keeps in its own lane and
hopefully has some use for problem's I have yet to encounter. Mabye for you too.

# Installation
# - Requirements
  - 
  -
  -
  -

# - Installation Guide
  -
  -
  -
  -
  -

# - Global Variable Set-up
  -
  -
  -
  -
  -

# Installation Via Klang Wizard
  -
  -
  -
  -
  -

# Goals
- Strongly Typed, memory safe definitions
- Optimized allocations and reallocations
- Multi-Thread built in capability
- Standard Library with Features - but no exclusive to: sockets, http, math, memory, types, algorithm, structure and more
  - Libraries and included features are explained in each documented piece
- Fast and Efficient Compiler with Human-Readable error messages and integrated assistance (intellisense, highlighting etc.)
- In-Built Data structure and algorithm processing.
- Direct access to Memory, System calls and Managing Sys process such as Networking.

These goals are to keep the build motivating and exciting. A Modest goal in my mind would be to make a fast and lightweight
language that has a more than capable strength of building an array of applications. Whether it be for websites, gaming or 
desktop applications. All tools should be available in one place.

# Features

- Staticly Typed
  - `int, float, double, char, string, bool` << all fundamental types (natively signed)
  - `uint, ufloat, double, char` << unsigned integral types
  - `null, void, class, public, private, protected`
  
- Object-Oriented Programming
  - Classes are defined as usual, specifying the "class" keyword.
  - Classes have pre-named constructors and destructors: init() and destroy()
  - Private, Public and Protected are specified as a trait to affect the visibility of attributes.
    - i.e `protected int myVal = 10; public string myName = "Kyle";`
  - In-Built OOP Design Patterns such as Special Classes i.e `Singleton`, `Factory` and `Blueprint`
  - Inheritance, Encapsulation and Abstraction are all valid configurations in KLang
    - `class A :: class B {}` using the `::` so Class A can inherit from Class B
    - the `super()` is used to access higher-order attributes that may be inherited
    - [FTF] getter and setter keywords... possible add as a redesign in the next patch
   
- KLang comes with a lot of features built-in natively to make things smoother.
  -> One thing is In-Built Objects to make certain processes quicker for the progranner
  -> `Stack, Queue, Hashmap, Dict, Vec2, Vec3, MinHeap, MaxHeap, Tree, BinTree, Graph`
      - Notice Items Like: `Map, List, DoublyLinkedList, CircularLinkedList, LinkedList`
      - are not listed as they are not generic and can be found in `std:structure`
      -> Typing for each is specified by a 'Trait' which is used for custom types
      -> i.e defining a stack would include: `Stack<int> myStack = {};`
      -> All Trait types use '<>' and is to be specified on the type
      -> If not type is specified for example: `Stack myStack = {};`
      -> A type will be allocated forr it depending on the size at runtime, to access this type by default its called `CustomType`.

  -> All In-Built Structures come with built-in memory and error handling that will be optimized every week
  
- Data Structures and Wrapper Classes Built-in
  - As youve saw data structures are inbuilt as object and ones that cant be accessed internally
    can be found via libraries and external means.
  - Being Versatile and Most importantly Memory-Safe it's important to distinguish what can be
    accessed and what shouldnt

  - Structures internally rely on Trait Arrays `CustomType* myArr;`
    -> CustomType referring to the default type allocated when no trait is specified by an Object
       containing a trait in its definition

  - Wrapper Classes Include In-Built functions and algorithms designed for cloaked access
    - `String, Int, Char, Bool, Float, Double, UInt, UChar, UFloat, UDouble` all standard types have wrapper classes and are usually capitalized to differentiate
    - Special Wrapper Classes Include: `UniquePtr, SharedPtr, WeakPtr, Thread, Time, DateTime, Date, `
   
  - Pointers and Smart Pointer usage for Memory management
    - C-Styled convention as follow the Ampersand `&` is used to get a reference and depending on the context
      the asterik `*` is used for defining or dereferencing a pointer
    - Pointers are defined by: `int* myPtr = &variable`
    - Dereferencing goes as usual: `int value = *myPtr`
   
    - Function Pointers and Object Pointers are all valid and handled by the compiler
      and Garbage Collector at compile time and runtime.

- Fast type conversion and coercion -> using C Styled conversion
  - i.e `float myFloatConverted = 1.2;`
  - ->  `IntFromFloat = (int)myFloatConverted;`
  - or even just: `int intTOfloat = (int)(1.2);`
 
- Built-In Wrapper Class Functions:
  - Like most Languages that include OOP - Two styles of types are usually available.
    fundamental types that are native like `string`, `int` and `uchar `etc and what I
    would call a "Wrapper Type". Usually working with the native type requires working
    with the memory as well. To make it easier when we come to using types we can make
    a class that resembles that type, stores that type - but also outlines methods, operations
    and behaviour that can be used and associated with that type.

  # - <i>Some Functions as Examples:</i>
  - String:
    - `SubString(string x, int start, int end`),
    - `Concatenate(string x, string y)`,
    - `CharAt(string x, int index)`,
    - `Insert(string x, int position)`,
    - `Remove(string, int position)`,
    - `PushChar(string x, char character) // pushes to the end`,
    - `PopChar(string x) // removes character at end`,

    Functions for Unsigned and Signed integral values are the same.

  - Integers:
    - `ToFloat(int input)`,
    - `ToDouble(int input)`,
    - `ToString(int input)`,
    - `ToChar(int input)`,
    - `MaxSize(int input)`,
    - `MinSize(int input)`,
   
  - Decimals (Floats and Doubles):
    - `ToString()`,
    - `ToInt()`,
    - `ToChar()`,
    - `MaxSize(`,
    - `MinSize()`,
    - `Round(decimal, figure)`,

  - Characters:
    - `ToString()`,
    - `ToInt()`,
    - `ToFloat()`,
    - `MaxSize()`,
    - `MinSize()`,
    - `Round(decimal, figure)`,
        
- Lightweight and Funtionality Focused
- Designed for Safe Low-Level Programming that can be utilized where ever it is put.
- Powerfully Enhanced Error handling: From descriptive error messages that don't leave the
  Programmer questioning there sanity, to smart and helpful tips, suggestions and insightful
  syntax and intellisense quality that keeps your quality of code to a high, readable standard.
- Native REPL and Command-Line Utilization
- [FTF] Command-Line Tools
  
- In the standard library namespace, there exists a list of libraries that are stored
  - and similar class inheritence (`"::"`) should be accessed through ":".
  - i.e `using std:game` for the game library
  - `using std:http` for http instructions / web server development
  - `using std:window` Library built for custom GUI building
  - `using math` The KLang Math library (not found in standard)
  - `using std:sockets` the Sockets library for network communication
  - `using std:memory` Memory Library that includes allocating, reallocating, freeing and cleaning up memory
  - `using std:sys` System Library that can be used to make system calls and make changes to the os
  - `using std:time` Time and date library
  - `using std:thread` Threading library for Multi-Thread Procedures
  - `using std:types` Wrapper Classes
    
  - And much more - most will take time to add and most are not even included here. All available libraries can be found
  - and installed using KPackager (the KLang Package Manager)

# Libraries

If you've read the documentation or had a read through some of this repository. You'll notice a reoccuring theme.
KLang was my idea of having the power of C++ and Rust but also highly functional and  capable of any task you put
it's way. JavaScript tries to achieve this - however the overhead complexity and number of libraries seems to increase
everday. Not that JavaScript is a bad language or that it's hard, certainly not - and I love using javascript where its
best in the web.

The Problem with having a very high number of externals is that there is more room for error. And quite frankly a lot of
repeated statements, when most ideas can be added and expanded of already existing software. As I'm the sole developer on
this journey I've made sure to check and optimize every library that gets added. This doesnt mean they'll be perfect and
definitely doesnt mean any overhead - But the idea of having everything in one place and easily accessible, as part of the 
language natively, seems like a much smoother idea. That doesnt go without saying custom libraries and open-source implementations
can't be made, as they very much can be using the `config visible=true`

# KPackager

TBD

# Use with Kyode or The Coffee Editor


# Documentation

- Official Documentation will be available at: www.kylebrady/klang-docs/book.co.uk

# Changelog - Version 1.03 (3rd Iteration)

- Official Changelog will be available at: www.kylebrady/klang-docs/changes.co.uk

# Authors

Kyle Brady
