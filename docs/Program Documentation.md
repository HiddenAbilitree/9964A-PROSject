<!-- @format -->

# Program Documentation

=== "Main Program"

    ``` cpp title="main.cpp" 
    --8<-- "src/main.cpp"
    ```

=== "Variables"

    ``` cpp title="robot.h"
    --8<-- "include/robot.h"
    ```

    </br>
    
    !!! abstract inline end "Note"
        
        Variables are stored here primarily for readability purposes throughout the codebase, although it also enables modularity through the use of global variables.
    This file contains the variable definitions used in the odometry controller constructor in main.cpp.
    
    We utilized global objects at the bottom of the file for modularity, allowing for multiple files to utilize the same objects.


    ```mermaid
    graph LR
    A[#include] --> B{Already included?};
    B --->|Yes| C(Ignore);
    B --->|No| D(Include);
    C --> E(No double inclusion);
    ``` 

    !!! info inline end
        
        `#!cpp #pragma` serves as way to give the compiler a configuration setting before compiling the program.
    This chart illustrates the importance of the use of `#!cpp #pragma once` at the beginning of the header file.


    `#!cpp #pragma once` acts very similarly to a `#!cpp #ifndef` header guard.
    ```mermaid
    graph TD
    A(Header file)
    B(File A)
    C(File B)
    D[#pragma once in header file]
    %%E(Header only included once)
    A -->|#include| B;
    B -->|#include| D;
    A -->|#include| C;
    %%C --> E;
    D -->|Header not included again| C;
    %%E --> F(No double inclusion);
    ```

=== "Functions"

    ```cpp title="functions.cpp"
    --8<-- "src/functions.cpp"
    ```

=== "Functions Header"

    ```cpp title="functions.h"
    --8<-- "include/functions.h"
    ```
