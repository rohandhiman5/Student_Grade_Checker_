#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
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

    void getdata(const vector<student> &existingStudents);
    void showdata() const;
    void Enter_courses(int n);
    double calculateCGPA();
};

unordered_map<string, Courses> courseCatalog();
void updateStudentRecord(vector<student> &students, long long rollNo);
void saveAllStudentsToFile(const vector<student> &students, const char *filename);
void loadAllStudentsFromFile(vector<student> &students, const char *filename, multimap<string, student> &ByName);
void mergeByRollNo(vector<student> &students, int left, int right);
void mergeByCGPA(vector<student> &students, int left, int right);
void mergeByName(vector<student> &students, int left, int right);
int binarySearchByRollNo(const vector<student> &students, int targetRollNo);
void displayAllCourses();

#endif
