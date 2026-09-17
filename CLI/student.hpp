#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "btree.hpp"
using namespace std;

// Define Courses struct
struct Courses
{
    string courseID;
    string courseName;
    float credits;
};

// Student Class
class student
{
public:
    string name;
    long long Roll_no;
    int age;
    string Branch;
    vector<string> registeredCourses;
    int totalCourses;
    unordered_map<string, int> marks_map; // Use of Hashing to store grades efficiently
    double CGPA;

    student(); // intiliase

    void getdata(BTree<long long, student> &rollTree);
    void showdata() const;
    void Enter_courses(int n);
    double calculateCGPA();
};

unordered_map<string, Courses> courseCatalog();
void updateStudentRecord(BTree<long long, student> &rollTree, long long rollNo);
void saveAllStudentsToFile(BTree<long long, student> &rollTree, const char *filename);
void loadAllStudentsFromFile(BTree<long long, student> &rollTree, const char *filename);
void displayAllCourses();

#endif
