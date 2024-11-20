# Student Grade Management System

This project is a Student Grade Checker program that allows users to manage student records in a menu-driven CLI interface and GUI interface. The program stores student data in a file, allowing for efficient storage. It supports various operations such as _adding new student_, _removing existing student_, _updating students details_, and _searching records_ efficiently using **binary** and **linear search** algorithms. It also calculates student CGPA based on the course policies.

This project implements Student grade managements system with two interfaces:
- **CLI (Command Line Interface)** using C++ for efficient data handling.
- **GUI (Graphical User Interface )** build using Python, providing user friendly interface.

This project was made by:
| Name         | Roll No |
|--------------|---------|
| Rohan       | 230001069     |
| Abhash Raj       | 230001002     |
| MARNENI VARUN BALAJI    | 230001052     |
| MARISETTI HRUDAY AMRIT    | 230001051    |

## Table of Contents

1. [Project Overview](#project-overview)
2. [Folder Structure](#folder-structure)
3. [Instructions to Use](#instructions-to-use)
   - [Prerequisites](#prerequisites)
   - [CLI Setup](#cli-setup)
   - [GUI Setup](#gui-setup)
4. [Data Structures and Algorithms Used](#data-structures-and-algorithms-used)
   - [Data Structures](#data-structures)
   - [Algorithms](#algorithms)
5. [References](#references)

## Project Overview
The system is built with an object-oriented approach in C++. It mainly focuses on data handling, input validation, and user interaction. The system utilizes a class-based design to manage student details and calculate CGPA based on marks and credits of courses provided to them. It uses various algorithms in an efficient way to perform these tasks. Data is stored in _binary files_ for efficient persistence with additional support of _sorting_, _searching_, and _updating_ records.

For user interaction, **Tkinter** is used to create a graphical user interface (GUI) to make it easier for users to interact with the system.

## Folder Structure

    Student-Grade-Management-System/
    │
    ├── CLI
    │   ├── main.cpp                # Main driver program for CLI
    │   ├── student.cpp             # Implementation of the student class
    │   ├── student.hpp             # Header file for the student class
    │   ├── students.dat            # Serialized data file for student records
    │   ├── Program.exe             # Compiled CLI executable
    │
    ├── GUI 
    │   ├── Student_Grade_checker_GUI.py # GUI implementation
    │   ├── students.json           # JSON format of student records
    │        
    └── README.md                   # Project documentation


## Instructions to Use

### Prerequisites
Ensure you have a C++ compiler installed on your system (e.g., GCC or Clang).

1. Clone the Repository:
   ``` bash
   git clone https://github.com/rohandhiman5/Student_Grade_Checker_.git
   cd Student_Grade_checker


### CLI:
2. To compile the project Run:
   ``` bash
   cd CLI
   g++ -std=c++11 main.cpp student.cpp -o Program
   ```
3. After Compiling, Run the program:
   ``` bash
    .\Program.exe
   ```
### Usage:
  Upon running the Student Grade Checker, users will interact with a menu-driven CLI interface offering the following operations:

  1. **Insert Student Record**: Add a new student record by providing details such as name, roll number, semester, branch, grades, and more.
  
  2. **View All Student Records**: Display all stored student records in a tabular format for easy review.
  
  3. **Search Student Record**: Search for a specific student using various filters such as name or roll number.
  
  4. **Delete Student Record**: Remove a student's record from the database by entering their roll number.
  
  5. **Update the Student**: Modify an existing student record to update details like grades, branch, or semester.
  
  6. **Sort the Students by Name**: Organize and display all student records alphabetically by name.
  
  7. **Sort the Students by CGPA**: Sort and display all student records based on their cumulative grade point average (CGPA).
  
  8. **Search by Roll No**: Quickly locate a student's record using their unique roll number.
  
  9. **List of Courses Available**: View a predefined list of courses to which students can enroll.
  
  10. **Exit the Program**: Save all data to persistent storage and terminate the program.

### GUI:
2. Install the Tkinter Library:
``` bash
  cd GUI
  pip install tk
```
4. After successful installation, run the program:
``` bash
python Student_Grade_checker_GUI.py
```




## Data stuctures and Algorithms used:
### Data Structures
  1. Vector `` (std::vector) `` : Stores the list of students.
  Provides dynamic resizing and sequential access to student records.
  2. Multimap `` (std::multimap) ``
  Indexes students by their names, allowing efficient searches for multiple students with the same name. Enables range-based queries.
  3. File I/O
  Uses .dat and .json files for saving and loading student records efficiently. Ensures data is retained across program sessions.
  4. Custom Classes
  `` student Class ``: Encapsulates attributes like name, roll number, branch, grades, and CGPA with methods for data input (getdata), output (showdata), and CGPA calculation.
  Additional helper functions for:
  - File operations (loadAllStudentsFromFile, saveAllStudentsToFile).
  - Searching (binarySearchByRollNo).
  - Sorting (mergeByName, mergeByCGPA)
### Algorithms:
  1. **hashing**: Hashing is used for efficient lookups for course information and marks .
  2. **Linear Search**:- To search student details with the help of linear search on the basis of Branch.
  3. **Binary search**:- To search student details with the help of Binary search on the basis of Roll number.
  4. **Merge sort**:-Merge sort was used here so that we can use binary search to search on the basis of roll number and for CGPA to sort students on basis of their CGPA.







### References:
1. [Serialize and Deserialze object in cpp](https://www.geeksforgeeks.org/serialize-and-deserialize-an-object-in-cpp/)
2. [File handing in cpp](https://stackoverflow.com/questions/69426096/how-to-serialize-and-deserialize-an-object-into-from-binary-files-manually)
















