#include "student.hpp"
#include <fstream>
#include <iomanip>

using namespace std;

student::student() : totalCourses(0), CGPA(0.0) {}

unordered_map<string, Courses> courseCatalog()
{   
    unordered_map<string, Courses> courses;  // Stored the courses using hashing for efficint lookup
    courses["MA205"] = {"MA205", "Complex Analysis", 2};
    courses["MA207"] = {"MA207", "Differential Equations-II", 2};
    courses["CS201"] = {"CS201", "Discrete Mathematical Structures", 3};
    courses["CS203"] = {"CS203", "Data Structures and Algorithms", 3};
    courses["CS207N"] = {"CS207N", "Database and Information Systems", 3};
    courses["CS209"] = {"CS209", "Logic Design", 3};
    courses["CS253"] = {"CS253", "Data Structures and Algorithms Lab", 1.5};
    courses["CS257"] = {"CS257", "Database and Information Systems Lab", 1.5};
    courses["CS200"] = {"CS200", "Department Elective I", 3};
    courses["EE201"] = {"EE201", "Network Theory", 3};
    courses["EE203"] = {"EE203", "Electronic Devices", 3};
    courses["EE207"] = {"EE207", "Electric Machines", 3};
    courses["EE209"] = {"EE209", "Digital Systems", 3};
    courses["EE253N"] = {"EE253N", "Electronic Devices Lab", 1};
    courses["EE259"] = {"EE259", "Digital Systems Lab", 1};
    courses["EE251"] = {"EE251", "Electrical Networks Lab", 1};
    courses["EE2XX"] = {"EE2XX", "Department Elective I", 3};
    courses["ME203N"] = {"ME203N", "Fluid Mechanics", 3};
    courses["ME205N"] = {"ME205N", "Materials Science and Engineering", 1.5};
    courses["ME207"] = {"ME207", "Principles of Industrial Engineering", 3};
    courses["ME201N"] = {"ME201N", "Solid Mechanics", 3};
    courses["ME209"] = {"ME209", "Thermodynamics", 3};
    courses["ME251N"] = {"ME251N", "Solid Mechanics Lab", 1};
    courses["ME2XX"] = {"ME2XX", "Department Elective I", 3};
    courses["CE201"] = {"CE201", "Solid Mechanics", 4};
    courses["CE203"] = {"CE203", "Fluid Mechanics-I", 3};
    courses["CE251"] = {"CE251", "Solid Mechanics Lab", 1.5};
    courses["CE253"] = {"CE253", "Fluid Mechanics Lab-I", 1};
    courses["CE257"] = {"CE257", "Civil Engineering Drawing", 2.5};
    courses["IC211"] = {"IC211", "Experimental Engineering Lab", 1.5};
    return courses;
}

// Function to display the list of all the courses present
void displayAllCourses()
{
    unordered_map<string, Courses> courses = courseCatalog();

    cout << "\nAvailable Courses:\n";
    cout << "-------------------------------------------\n";
    for (const auto& course : courses)
    {
        cout << "Course ID: " << course.second.courseID
             << ", Course Name: " << course.second.courseName
             << ", Credits: " << course.second.credits << endl;
    }
    cout << "-------------------------------------------\n";
}


// Function to store the list of the student in the student.dat file for file handling
void saveAllStudentsToFile(const vector<student>& students, const char* filename)
{
    ofstream file(filename, ios::out | ios::binary);
    if (!file)
    {
        cout << "Error opening file for writing.\n";
        return;
    }

    int numStudents = students.size();
    file.write(reinterpret_cast<const char*>(&numStudents), sizeof(numStudents));

    for (const auto& s : students)
    {   
        size_t nameLength = s.name.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(s.name.c_str(), nameLength);

        file.write(reinterpret_cast<const char*>(&s.Roll_no), sizeof(s.Roll_no));
        file.write(reinterpret_cast<const char*>(&s.age), sizeof(s.age));

        size_t branchLength = s.Branch.size();
        file.write(reinterpret_cast<const char*>(&branchLength), sizeof(branchLength));
        file.write(s.Branch.c_str(), branchLength);

        int totalCourses = s.registeredCourses.size();
        file.write(reinterpret_cast<const char*>(&totalCourses), sizeof(totalCourses));

        for (const auto& course : s.registeredCourses)
        {
            size_t courseLength = course.size();
            file.write(reinterpret_cast<const char*>(&courseLength), sizeof(courseLength));
            file.write(course.c_str(), courseLength);
        }

        int marksCount = s.marks_map.size();
        file.write(reinterpret_cast<const char*>(&marksCount), sizeof(marksCount));

        for (const auto& entry : s.marks_map)
        {
            size_t courseLength = entry.first.size();
            file.write(reinterpret_cast<const char*>(&courseLength), sizeof(courseLength));
            file.write(entry.first.c_str(), courseLength);
            file.write(reinterpret_cast<const char*>(&entry.second), sizeof(entry.second));
        }

        file.write(reinterpret_cast<const char*>(&s.CGPA), sizeof(s.CGPA));
    }

    file.close();
}

// Function to load the list of the student already stored in the file 
void loadAllStudentsFromFile(vector<student>& students, const char* filename, multimap<string, student>& ByName)
{
    ifstream file(filename, ios::in | ios::binary);
    if (!file)
    {
        cout << "Error opening file for reading.\n";
        return;
    }

    int numStudents;
    file.read(reinterpret_cast<char*>(&numStudents), sizeof(numStudents));

    for (int i = 0; i < numStudents; ++i)
    {
        student s;

        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        s.name.resize(nameLength);
        file.read(&s.name[0], nameLength);

        file.read(reinterpret_cast<char*>(&s.Roll_no), sizeof(s.Roll_no));
        file.read(reinterpret_cast<char*>(&s.age), sizeof(s.age));

        size_t branchLength;
        file.read(reinterpret_cast<char*>(&branchLength), sizeof(branchLength));
        s.Branch.resize(branchLength);
        file.read(&s.Branch[0], branchLength);

        int totalCourses;
        file.read(reinterpret_cast<char*>(&totalCourses), sizeof(totalCourses));

        for (int j = 0; j < totalCourses; ++j)
        {
            size_t courseLength;
            file.read(reinterpret_cast<char*>(&courseLength), sizeof(courseLength));

            string courseID(courseLength, ' ');
            file.read(&courseID[0], courseLength);
            s.registeredCourses.push_back(courseID);
        }

        int marksCount;
        file.read(reinterpret_cast<char*>(&marksCount), sizeof(marksCount));

        for (int j = 0; j < marksCount; ++j)
        {
            size_t courseLength;
            file.read(reinterpret_cast<char*>(&courseLength), sizeof(courseLength));

            string courseID(courseLength, ' ');
            file.read(&courseID[0], courseLength);

            int marks;
            file.read(reinterpret_cast<char*>(&marks), sizeof(marks));

            s.marks_map[courseID] = marks;
        }

        file.read(reinterpret_cast<char*>(&s.CGPA), sizeof(s.CGPA));

        students.push_back(s);
    }

    ByName.clear();
    for (const auto& s : students)
    {
        ByName.insert({s.name, s});
    }

    file.close();
}

// Function to Get the data about the student 
void student::getdata(const vector<student> &existingStudents)
{
    cin.ignore(); 
    cout << "\t* ENTER STUDENT NAME: ";
    getline(cin, name); 

    cout << "\t* ENTER STUDENT ROLL.NO: ";
    bool validRollNo = false;

    do
    {
        cin >> Roll_no;

        if (cin.fail())
        {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a numeric Roll No: ";
            continue; 
        }

  
        bool duplicateRollNo = false;
        for (const auto &existingStudent : existingStudents)
        {
            if (existingStudent.Roll_no == Roll_no)
            {
                cout << "Roll number already exists! Please enter a unique Roll No: ";
                duplicateRollNo = true;
                break;
            }
        }

        if (!duplicateRollNo)
        {
            validRollNo = true; 
        }
    } while (!validRollNo);

    cout << "\t* ENTER STUDENT AGE: ";
    bool ValidAge = false;
    do
    {
        cin >> age;
        if (cin.fail()) 
        {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a numeric Age: ";
            continue; 
        }

        if (age > 0) {
            ValidAge = true;
        } else {
            cout << "Age must be a positive number! Please enter again: ";
        }
    } while (!ValidAge); 


    cout << "\t* ENTER STUDENT BRANCH (options: CSE, EE, ME, MEMS, CE, MNC, EP): ";
    cin >> Branch;

    transform(Branch.begin(), Branch.end(), Branch.begin(), ::toupper);

    vector<string> validBranches = {"CSE", "EE", "ME", "MEMS", "CE", "MNC", "EP"};

    while (find(validBranches.begin(), validBranches.end(), Branch) == validBranches.end())
    {
        cout << "Invalid branch! Please enter a valid branch (CSE, EE, ME, MEMS, CE, MNC, EP): ";
        cin >> Branch;
        transform(Branch.begin(), Branch.end(), Branch.begin(), ::toupper); 
    }

    cout << "\t* ENTER TOTAL REGISTERED COURSES BY THE STUDENT: ";
    int n;
    cin >> n;

    Enter_courses(n);
}


void student::showdata() const
{
    cout << "\nSTUDENT NAME: " << name
         << "\nSTUDENT ROLL NO: " << Roll_no
         << "\nSTUDENT AGE: " << age
         << "\nSTUDENT BRANCH: " << Branch
         << "\nTOTAL REGISTERED COURSES: " << totalCourses;

    if (!marks_map.empty())
    {
        cout << "\nCOURSES AND MARKS: ";
        for (const auto &course : marks_map)
        {
            cout << "\n  Course ID: " << course.first
                 << ", Marks: " << course.second;
        }
    }

    cout << "\nCGPA OF STUDENT: " << CGPA << endl;
}


void student::Enter_courses(int n)
{
    unordered_map<string, Courses> Temp = courseCatalog();
    totalCourses = 0; 
    cin.ignore();     

    while (n--)
    {
        string courseID;
        cout << "Enter the Course ID: ";
        getline(cin, courseID); 

        if (Temp.find(courseID) == Temp.end())
        {
            cout << "Course not found! Try again.\n";
            ++n; 
        }
        else if (find(registeredCourses.begin(), registeredCourses.end(), courseID) != registeredCourses.end())
        {
         
            cout << "Course already registered! Please enter a different course.\n";
            ++n; 
        }
        else
        {
            registeredCourses.push_back(courseID);

            int marks;
            while (true)
            {
                cout << "Enter marks obtained in " << courseID << " (less than 100): ";
                cin >> marks;

                if (marks >= 0 && marks < 100)
                {
                    break; 
                }
                else
                {
                    cout << "Invalid marks! Please enter a value less than 100.\n";
                }
            }

            marks_map[courseID] = marks;
            cin.ignore();  
            totalCourses++; 
        }
    }
}


// For calculating CGPA of the student based on course policies
double student::calculateCGPA()
{
    double totalPoints = 0;
    float totalCredits = 0;

    unordered_map<string, Courses> Temp = courseCatalog();
    for (const auto &course : registeredCourses)
    {
        auto it = Temp.find(course);
        if (it != Temp.end())
        {
            totalPoints += it->second.credits * marks_map[course];
            totalCredits += it->second.credits;
        }
    }

    if (totalCredits == 0)
    {
        return 0.0;
    }
    return totalPoints / (totalCredits * 10);
}

// Function to update the student recods.
void updateStudentRecord(vector<student> &students, long long rollNo)

{
    bool found = false;

    for (auto &s : students)
    {
        if (s.Roll_no == rollNo)
        {
            found = true;

            cout << "\nStudent Found. Current Details:\n";
            s.showdata();

            cout << "\nEnter New Details (Leave blank to keep existing values):\n";

            cin.ignore();
            cout << "New Name (current: " << s.name << "): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty())
            {
                s.name = newName;
            }

          
            cout << "New Age (current: " << s.age << "): ";
            string newAgeStr;
            getline(cin, newAgeStr);
            if (!newAgeStr.empty())
            {
                s.age = stoi(newAgeStr);
            }


            cout << "New Branch (current: " << s.Branch << "): ";
            string newBranch;
            getline(cin, newBranch);
            if (!newBranch.empty())
            {
                s.Branch = newBranch;
            }

    
            cout << "Do you want to update courses? (yes/no): ";
            string updateCourses;
            cin >> updateCourses;

            if (updateCourses == "yes")
            {
                cout << "Enter the new total number of courses: ";
                int newTotalCourses;
                cin >> newTotalCourses;

                s.registeredCourses.clear();
                s.marks_map.clear();
                s.Enter_courses(newTotalCourses);
            }

        
            s.CGPA = s.calculateCGPA();

            cout << "\nStudent Record Updated Successfully!\n";
            break;
        }
    }

    if (!found)
    {
        cout << "Student with Roll No " << rollNo << " not found.\n";
    }
}

// Implemented linear search to look up the studnet by the branch
int linearSearchByBranch(const vector<student> &students, const string &targetBranch)
{
    for (int i = 0; i < students.size(); ++i)
    {
        if (students[i].Branch == targetBranch)
        {
            return i;
        }
    }
    return -1;
}

// Implemented Binary search to look up the Student by Roll Number
int binarySearchByRollNo(const vector<student> &students, int targetRollNo)
{
    int left = 0, right = students.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

       
        if (students[mid].Roll_no == targetRollNo)
        {
            return mid;
        }
       
        else if (students[mid].Roll_no < targetRollNo)
        {
            left = mid + 1;
        }
      
        else
        {
            right = mid - 1;
        }
    }

    return -1; // Not found
}

// Implemented merge sort to Sort the Student based on ROll number 
void mergeByRollNo(vector<student> &students, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    
    mergeByRollNo(students, left, mid);

  
    mergeByRollNo(students, mid + 1, right);

    
    vector<student> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (students[i].Roll_no <= students[j].Roll_no)
        {
            temp.push_back(students[i]);
            i++;
        }
        else
        {
            temp.push_back(students[j]);
            j++;
        }
    }

   
    while (i <= mid)
    {
        temp.push_back(students[i]);
        i++;
    }

  
    while (j <= right)
    {
        temp.push_back(students[j]);
        j++;
    }

    for (int k = left; k <= right; ++k)
    {
        students[k] = temp[k - left];
    }
}

// implemented merge sort to sort the student based on CGPA
void mergeByCGPA(vector<student> &students, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

   
    mergeByCGPA(students, left, mid);

    
    mergeByCGPA(students, mid + 1, right);

    
    vector<student> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (students[i].CGPA <= students[j].CGPA)
        {
            temp.push_back(students[i]);
            i++;
        }
        else
        {
            temp.push_back(students[j]);
            j++;
        }
    }

    
    while (i <= mid)
    {
        temp.push_back(students[i]);
        i++;
    }

   
    while (j <= right)
    {
        temp.push_back(students[j]);
        j++;
    }

   
    for (int k = left; k <= right; ++k)
    {
        students[k] = temp[k - left];
    }
}

// Implemented merge sort to sort the student based on Names
void mergeByName(vector<student> &students, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    
    mergeByName(students, left, mid);

    mergeByName(students, mid + 1, right);

    
    vector<student> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (students[i].name <= students[j].name)
        {
            temp.push_back(students[i]);
            i++;
        }
        else
        {
            temp.push_back(students[j]);
            j++;
        }
    }

    
    while (i <= mid)
    {
        temp.push_back(students[i]);
        i++;
    }

    
    while (j <= right)
    {
        temp.push_back(students[j]);
        j++;
    }

   
    for (int k = left; k <= right; ++k)
    {
        students[k] = temp[k - left];
    }
}


