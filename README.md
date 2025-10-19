# KLang

# <i>A Mid-Level, Multi-functional Language</i>

KLang was made as a side-project inspired by the will and curiosity of the cogs and wheels that drive the everyday compiler.
Since picking up the interest it's been interesting to see how each piece works and how, eventually, it does all fit together
in a nice neat picture. While not necessary, KLang was made to support an array of functions from Web development all the way
to Game Development and Database management. The Syntax and Compile resemnble and are built from C. Pure C. Nothing more or
nothing less was needed. While the language itself bears features to others like rust and C++, it keeps in its own lane and
hopefully has some use for problem's I have yet to encounter. Mabye for you too.

# Installation
-
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
  - `null, void, `
- Object-Oriented Programming
  - Classes are defined as usual, specifying the "class" keyword.
  - Classes have pre-named constructors and destructors: init() and destroy()
  - Private, Public and Protected are specified as a trait to affect the visibility of attributes.
    - i.e `protected int myVal = 10; public string myName = "Kyle";`
   
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
  - Fast type conversion and coercion -> using C Styled conversion
    - i.e `float myFloatConverted = 1.2;`
    - ->  `IntFromFloat = (int)myFloatConverted;`
    - or even just: `int intTOfloat = (int)(1.2);`
  - Lightweight and Funtionality Focused
  - Designed for Safe Low-Level Programming that can be utilized where ever it is put
    - In the standard library namespace, there exists a list of libraries that are stored
    - and similar class inheritence ("::") should be accessed through ":".
    - i.e `using std:game` for the game library
    - `using std:http` for http instructions / web server development
    - `using std:window` Library built for custom GUI building
    - `using math` The KLang Math library (not found in standard)
    - `using std:sockets` the Sockets library for network communication
    - `using std:memory` Memory Library that includes allocating, reallocating, freeing and cleaning up memory
    - `using std:sys` System Library that can be used to make system calls and make changes to the os
    - And much more - most will take time to add and most are not even included here. All available libraries can be found
    - and installed using KPacker (the KLang Package Manager)

# Libraries

TBD

# KPackager

TBD


# Documentation

- Official Documentation will be available at: www.kylebrady/klang-docs/book.co.uk

# Changelog - Version 1.03 (3rd Iteration)

- Official Changelog will be available at: www.kylebrady/klang-docs/changes.co.uk

# Authors

Kyle Brady
