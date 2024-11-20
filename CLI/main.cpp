#include "student.hpp"

using namespace std;

int main()
{
    multimap<string, student> ByName;
    cout << "working";
    int choice;
    vector<student> students;

    loadAllStudentsFromFile(students, "students.dat", ByName);
    cout << "ByName size: " << ByName.size() << endl;
    for (const auto &entry : ByName)
    {
        cout << "Name: " << entry.first << ", Roll No: " << entry.second.Roll_no << endl;
    }

    while (true)
    {
        // Displaying Menu to the User
        cout << "\n*                                                           *\n";
        cout << "*              1. Insert Student Record                     *\n";
        cout << "*              2. View All Student Records                  *\n";
        cout << "*              3. Search Student Record                     *\n";
        cout << "*              4. Delete Student Record                     *\n";
        cout << "*              5. Update the student                        *\n";
        cout << "*              6. Sort the students by name                 *\n";
        cout << "*              7. Sort the students by cgpa                 *\n";
        cout << "*              8. Search by Roll No                     *\n";
        cout << "*              9. List of Courses Available                    *\n";
        cout << "*              10. Exit the Program                          *\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            student newStudent;
            newStudent.getdata(students);
            newStudent.CGPA = newStudent.calculateCGPA();
            students.push_back(newStudent);
            cout << "\nStudent Record Inserted Successfully!\n";
            break;
        }
        case 2:
        {

            cout << "\nAll Student Records\n";
            for (const auto &s : students)
            {
                s.showdata();
                cout << "\n--------------------------------------\n";
            }
            break;
        }

        case 3:
        {
            cout << "1. Search By Roll Number\n";
            cout << "2. Search By Name of the Student\n";
            cout << "3. Search By Branch\n";

            int value;
            cin >> value;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            switch (value)
            {
            case 1:
            {
                long long rollNo;
                cout << "Enter Roll No to Search: ";
                cin >> rollNo;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number.\n";
                    continue;
                }

                bool found = false;
                for (const auto &s : students)
                {
                    if (s.Roll_no == rollNo)
                    {
                        s.showdata();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Student with Roll No " << rollNo << " not found.\n";
                }
                break;
            }

            case 2:
            {
                string key;
                cout << "Enter the Name to search: ";
                cin.ignore();
                getline(cin, key);

                auto range = ByName.equal_range(key);
                if (range.first != range.second)
                {
                    cout << "\nStudent(s) Found:\n";
                    for (auto it = range.first; it != range.second; ++it)
                    {
                        it->second.showdata();
                    }
                }
                else
                {
                    cout << "Student with name \"" << key << "\" not found.\n";
                }
                break;
            }

            case 3:
            {
                string targetBranch;
                cout << "Enter the branch to search for: ";
                cin.ignore();
                getline(cin, targetBranch);

                bool found = false;
                for (const auto &s : students)
                {
                    if (s.Branch == targetBranch)
                    {
                        s.showdata();
                        cout << "\n--------------------------------------\n";
                        found = true;
                    }
                }
                if (!found)
                {
                    cout << "\nNo students found in the \"" << targetBranch << "\" branch.\n";
                }
                break;
            }

            default:
                cout << "Invalid Choice! Please try again.\n";
                break;
            }
            break;
        }

        case 4:
        {
            long long rollNo;
            cout << "Enter Roll No to Delete: ";
            cin >> rollNo;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            auto it = remove_if(students.begin(), students.end(), [rollNo](const student &s)
                                { return s.Roll_no == rollNo; });

            if (it != students.end())
            {
                students.erase(it, students.end());
                cout << "Student with Roll No " << rollNo << " deleted.\n";
            }
            else
            {
                cout << "Student with Roll No " << rollNo << " not found.\n";
            }
            break;
        }

        case 5:
        {
            cout << "Enter Roll No of the Student to Update: ";
            long long rollNo;
            cin >> rollNo;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            updateStudentRecord(students, rollNo);
            break;
        }

        case 6:
        {
            vector<student> temp;

            for (int i = 0; i < students.size(); i++)
            {
                temp.push_back(students[i]);
            }

            mergeByName(temp, 0, temp.size() - 1);

            cout << "\nAll Student Records (Sorted by Name): \n";
            for (const auto &s : temp)
            {
                s.showdata();
                cout << "\n--------------------------------------\n";
            }

            break;
        }

        case 7:
        {

            vector<student> temp;

            for (int i = 0; i < students.size(); i++)
            {
                temp.push_back(students[i]);
            }
            mergeByCGPA(temp, 0, temp.size() - 1);

            cout << "\nAll Student Records (Sorted by CGPA): \n";
            for (const auto &s : temp)
            {
                s.showdata();
                cout << "\n--------------------------------------\n";
            }

            break;
        }

        case 8:
        {
            vector<student> temp;

            int targetRollNo;
            cout << "Enter Target Roll NO" << endl;
            cin >> targetRollNo;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            for (int i = 0; i < students.size(); i++)
            {
                temp.push_back(students[i]);
            }

            mergeByRollNo(temp, 0, temp.size() - 1);

            int result = binarySearchByRollNo(temp, targetRollNo);

            if (result != -1)
            {
                cout << "\nStudent found: ";
                temp[result].showdata();
            }
            else
            {
                cout << "\nStudent with Roll No " << targetRollNo << " not found." << endl;
            }

            break;
        }

        case 9:
        {
            displayAllCourses();
            break;
        }

        case 10:
        {

            saveAllStudentsToFile(students, "students.dat");
            cout << "Exiting Program...\n";
            return 0;
        }

        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}