import tkinter as tk
from tkinter import messagebox, simpledialog
import os
import json


class Student:
    branches = ["CSE", "EE", "ME", "CE", "MEMS", "EP"]
    
    # Mapping course IDs to course names and credits (stored as tuples)
    courses = {
        "MA205": ("Complex Analysis", 2),
        "MA207": ("Differential Equations-II", 2),
        "CS201": ("Discrete Mathematical Structures", 3),
        "CS203": ("Data Structures and Algorithms", 3),
        "CS207N": ("Database and Information Systems", 3),
        "CS209": ("Logic Design", 3),
        "CS253": ("Data Structures and Algorithms Lab", 1.5),
        "CS257": ("Database and Information Systems Lab", 1.5),
        "CS200": ("Department Elective I", 3),
        "EE201": ("Network Theory", 3),
        "EE203": ("Electronic Devices", 3),
        "EE207": ("Electric Machines", 3),
        "EE209": ("Digital Systems", 3),
        "EE253N": ("Electronic Devices Lab", 1),
        "EE259": ("Digital Systems Lab", 1),
        "EE251": ("Electrical Networks Lab", 1),
        "EE2XX": ("Department Elective I", 3),
        "ME203N": ("Fluid Mechanics", 3),
        "ME205N": ("Materials Science and Engineering", 1.5),
        "ME207": ("Principles of Industrial Engineering", 3),
        "ME201N": ("Solid Mechanics", 3),
        "ME209": ("Thermodynamics", 3),
        "ME251N": ("Solid Mechanics Lab", 1),
        "ME2XX": ("Department Elective I", 3),
        "CE201": ("Solid Mechanics", 4),
        "CE203": ("Fluid Mechanics-I", 3),
        "CE251": ("Solid Mechanics Lab", 1.5),
        "CE253": ("Fluid Mechanics Lab-I", 1),
        "CE257": ("Civil Engineering Drawing", 2.5),
        "IC211": ("Experimental Engineering Lab", 1.5)
    }

    def __init__(self, roll_no, name, branch, cgpa, courses):
        self.roll_no = roll_no
        self.name = name
        self.branch = branch
        self.cgpa = cgpa
        self.courses = courses

    def __repr__(self):
        return (f"Roll No: {self.roll_no}, Name: {self.name}, Branch: {self.branch}, "
                f"CGPA: {self.cgpa:.2f}, Courses: {self.courses}")

    def to_dict(self):
        return {"roll_no": self.roll_no, "name": self.name, "branch": self.branch, "cgpa": self.cgpa, "courses": self.courses}

    @staticmethod
    def from_dict(data):
        return Student(data["roll_no"], data["name"], data["branch"], data["cgpa"], data["courses"])


class StudentManagementSystem:
    def __init__(self, root):
        self.file_path = "students.json"
        self.students = self.load_students()
        self.root = root
        self.root.title("Student Management System")
        self.create_gui()

    def create_gui(self):
        self.root.config(bg="#f0f0f0")  # Set background color for window
        self.menu_frame = tk.Frame(self.root, bg="#f0f0f0")
        self.menu_frame.pack(pady=20)

        tk.Label(self.menu_frame, text="Student Management System", font=("Arial", 16), bg="#f0f0f0", fg="darkblue").grid(row=0, columnspan=2, pady=10)

        menu_items = [
            "Insert Student Record",
            "View All Student Records",
            "Search Student Records",
            "Delete Student Record",
            "Sort Students",
            "Update Student Record",
            "Show Course List",  # Added option to show course list
            "Exit Program",
        ]

        button_colors = ["#4CAF50", "#2196F3", "#FF9800", "#F44336", "#9C27B0", "#00BCD4", "#FFC107", "#E91E63"]

        for i, item in enumerate(menu_items):
            tk.Button(self.menu_frame, text=item, width=25, command=lambda i=i: self.handle_choice(i + 1),
                      bg=button_colors[i], fg="white", relief="raised").grid(row=i + 1, column=0, padx=10, pady=5)

    def handle_choice(self, choice):
        if choice == 1:
            self.insert_student()
        elif choice == 2:
            self.view_students()
        elif choice == 3:
            self.search_student()
        elif choice == 4:
            self.delete_student()
        elif choice == 5:
            self.sort_students()
        elif choice == 6:
            self.update_student()
        elif choice == 7:
            self.show_course_list()  # Call function to show course list
        elif choice == 8:
            self.exit_program()

    def load_students(self):
        if os.path.exists(self.file_path):
            with open(self.file_path, "r") as file:
                return [Student.from_dict(data) for data in json.load(file)]
        return []

    def save_students(self):
        with open(self.file_path, "w") as file:
            json.dump([student.to_dict() for student in self.students], file, indent=4)

    def calculate_cgpa(self, courses):
        total_points = 0
        total_credits = 0
        for course, marks in courses.items():
            course_info = Student.courses.get(course, ("Unknown", 0))
            credits = course_info[1]
            total_points += (marks / 10) * credits
            total_credits += credits
        return total_points / total_credits if total_credits > 0 else 0

    def insert_student(self):
        roll_no = simpledialog.askstring("Input", "Enter Roll No:")
        if any(student.roll_no == roll_no for student in self.students):
            messagebox.showerror("Error", "Roll No already exists.")
            return

        name = simpledialog.askstring("Input", "Enter Name:")

        while True:
            branch = simpledialog.askstring("Input", f"Enter Branch ({', '.join(Student.branches)}):")
            if branch in Student.branches:
                break
            else:
                messagebox.showerror("Error", "Invalid branch. Please enter a valid branch.")

        num_courses = simpledialog.askinteger("Input", "Enter number of courses:")
        courses = {}
        for _ in range(num_courses):
            while True:
                course = simpledialog.askstring("Input", "Enter Course ID:")
                if course in courses:
                    messagebox.showerror("Error", "Duplicate course name. Please enter a unique course.")
                elif course not in Student.courses:
                    messagebox.showerror("Error", f"'{course}' is not a valid course. Please enter a valid course.")
                else:
                    break

            while True:
                marks = simpledialog.askinteger("Input", f"Enter Marks for {course} (0-100):")
                if marks is None or not (0 <= marks <= 100):
                    messagebox.showerror("Error", "Marks must be between 0 and 100. Please re-enter.")
                else:
                    break

            courses[course] = marks

        cgpa = self.calculate_cgpa(courses)
        self.students.append(Student(roll_no, name, branch, cgpa, courses))
        self.save_students()
        messagebox.showinfo("Success", "Student record added successfully!")

    def show_course_list(self):
        # Display course list
        courses = "\n".join([f"{course_id}: {course_name} - {credits} Credits"
                             for course_id, (course_name, credits) in Student.courses.items()])
        self.show_text("Course List", courses)

    def show_text(self, title, text):
        top = tk.Toplevel(self.root)
        top.title(title)
        text_widget = tk.Text(top, height=15, width=60)
        text_widget.insert(tk.END, text)
        text_widget.pack()
        text_widget.config(state=tk.DISABLED)

    def update_student(self):
        roll_no = simpledialog.askstring("Update", "Enter Roll No to update:")
        for student in self.students:
            if student.roll_no == roll_no:
                name = simpledialog.askstring("Update", f"Enter New Name (Current: {student.name}):") or student.name

                while True:
                    branch = simpledialog.askstring("Update", f"Enter New Branch (Current: {student.branch}):") or student.branch
                    if branch in Student.branches:
                        break
                    else:
                        messagebox.showerror("Error", "Invalid branch. Please enter a valid branch.")

                num_courses = simpledialog.askinteger("Input", "Enter number of courses:")
                courses = {}
                for _ in range(num_courses):
                    while True:
                        course = simpledialog.askstring("Input", "Enter Course Name:")
                        if course in courses:
                            messagebox.showerror("Error", "Duplicate course name. Please enter a unique course.")
                        elif course not in Student.courses:
                            messagebox.showerror("Error", f"'{course}' is not a valid course. Please enter a valid course.")
                        else:
                            break

                    while True:
                        marks = simpledialog.askinteger("Input", f"Enter Marks for {course} (0-100):")
                        if marks is None or not (0 <= marks <= 100):
                            messagebox.showerror("Error", "Marks must be between 0 and 100. Please re-enter.")
                        else:
                            break

                    courses[course] = marks

                cgpa = self.calculate_cgpa(courses)
                student.name, student.branch, student.courses, student.cgpa = name, branch, courses, cgpa
                self.save_students()
                messagebox.showinfo("Update", "Student record updated successfully.")
                return
        messagebox.showinfo("Update", "No student found with the given Roll No.")

    def view_students(self):
        if not self.students:
            messagebox.showinfo("View Students", "No student records found.")
        else:
            records = "\n".join([str(student) for student in self.students])
            self.show_text("View Students", records)

    def search_student(self):
        options = ["Roll No", "Name", "Branch"]
        choice = simpledialog.askstring("Search", f"Search by ({', '.join(options)}):" )
        if choice == "Roll No":
            self.search_by_roll_no()
        elif choice == "Name":
            self.search_by_name()
        elif choice == "Branch":
            self.search_by_branch()

    def search_by_roll_no(self):
        roll_no = simpledialog.askstring("Search", "Enter Roll No to search:")
        for student in self.students:
            if student.roll_no == roll_no:
                messagebox.showinfo("Search Result", str(student))
                return
        messagebox.showinfo("Search Result", "No student found with the given Roll No.")

    def search_by_name(self):
        name = simpledialog.askstring("Search", "Enter Name to search:")
        found_students = [str(student) for student in self.students if name.lower() in student.name.lower()]
        if found_students:
            messagebox.showinfo("Search Result", "\n".join(found_students))
        else:
            messagebox.showinfo("Search Result", "No student found with the given Name.")

    def search_by_branch(self):
        branch = simpledialog.askstring("Search", f"Enter Branch ({', '.join(Student.branches)}):")
        found_students = [str(student) for student in self.students if branch.lower() == student.branch.lower()]
        if found_students:
            messagebox.showinfo("Search Result", "\n".join(found_students))
        else:
            messagebox.showinfo("Search Result", "No student found with the given Branch.")

    def delete_student(self):
        roll_no = simpledialog.askstring("Delete", "Enter Roll No to delete:")
        for student in self.students:
            if student.roll_no == roll_no:
                self.students.remove(student)
                self.save_students()
                messagebox.showinfo("Delete", "Student record deleted successfully.")
                return
        messagebox.showinfo("Delete", "No student found with the given Roll No.")

    def sort_students(self):
        sorted_students = sorted(self.students, key=lambda x: x.cgpa, reverse=True)
        sorted_info = "\n".join([str(student) for student in sorted_students])
        self.show_text("Sorted Students by CGPA", sorted_info)

    def exit_program(self):
        self.root.quit()


if __name__ == "__main__":
    root = tk.Tk()
    app = StudentManagementSystem(root)
    root.mainloop()
