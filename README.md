# INET 3101- Lab2

### Overview
This lab focuses on storing a custom record (part number, name, size, metric, cost) in **dynamically allocated memory** rather than a fixed-size array or linked list. I used a `struct` to define what a record looks like, and then a pointer that grows or shrinks as I add or remove records.

### What This Code Does
- **No static arrays**: Everything is done through `malloc()` and `realloc()`.
- **No linked lists**: We’re managing memory ourselves, not using nodes and pointers.
- **A simple menu**:  
  1. Print all records  
  2. Print number of records  
  3. Print database size (bytes)  
  4. Add record  
  5. Delete last record  
  6. Exit  

When a user **adds** a record, the program calls `realloc()` to increase the memory block by one more `struct`. When **deleting**, it shrinks the memory block by removing the last record.

### Files
- **lab2.c**: Main program with the menu and functions to add, remove, and print records.
- **(Optional) README.md / README.txt**: This document, describing how the code works and how to compile it.

### How to Compile and Run
1. **Compile** the code:
   ```bash
   gcc lab2.c -o lab2
