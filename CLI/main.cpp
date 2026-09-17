#include "student.hpp"
#include <algorithm>

using namespace std;

int main()
{
    cout << "working";
    int choice;
    BTree<long long, student> rollTree; // Using B-Tree instead of vector

    loadAllStudentsFromFile(rollTree, "students.dat");

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
            newStudent.getdata(rollTree);
            newStudent.CGPA = newStudent.calculateCGPA();
            rollTree.insert(newStudent.Roll_no, newStudent);
            cout << "\nStudent Record Inserted Successfully!\n";
            break;
        }
        case 2:
        {
            vector<student> all;
            rollTree.traverse(all);
            cout << "\nAll Student Records (Sorted by Roll No via B-Tree)\n";
            for (const auto &s : all)
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

                student* s = rollTree.search(rollNo);
                if (s != nullptr)
                {
                    s->showdata();
                }
                else
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

                vector<student> all;
                rollTree.traverse(all);
                bool found = false;
                for (const auto& s : all) {
                    if (s.name == key) {
                        if (!found) cout << "\nStudent(s) Found:\n";
                        s.showdata();
                        found = true;
                    }
                }
                if (!found) {
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

                vector<student> all;
                rollTree.traverse(all);
                bool found = false;
                for (const auto& s : all) {
                    if (s.Branch == targetBranch) {
                        s.showdata();
                        cout << "\n--------------------------------------\n";
                        found = true;
                    }
                }
                if (!found) {
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

            if (rollTree.search(rollNo) != nullptr) {
                vector<student> all;
                rollTree.traverse(all);
                rollTree.clear(); // Clear existing tree
                for (const auto& s : all) {
                    if (s.Roll_no != rollNo) {
                        rollTree.insert(s.Roll_no, s);
                    }
                }
                cout << "Student with Roll No " << rollNo << " deleted.\n";
            } else {
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

            updateStudentRecord(rollTree, rollNo);
            break;
        }

        case 6:
        {
            vector<student> temp;
            rollTree.traverse(temp);
            sort(temp.begin(), temp.end(), [](const student& a, const student& b) {
                return a.name < b.name;
            });

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
            rollTree.traverse(temp);
            sort(temp.begin(), temp.end(), [](const student& a, const student& b) {
                return a.CGPA < b.CGPA;
            });

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
            long long targetRollNo;
            cout << "Enter Target Roll NO\n";
            cin >> targetRollNo;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            student* s = rollTree.search(targetRollNo);
            if (s != nullptr)
            {
                cout << "\nStudent found: ";
                s->showdata();
            }
            else
            {
                cout << "\nStudent with Roll No " << targetRollNo << " not found.\n";
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
            saveAllStudentsToFile(rollTree, "students.dat");
            cout << "Exiting Program...\n";
            return 0;
        }

        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}