#include <iostream>
#include <string>

const int MAX_STUDENTS = 100;

class Student {
public:
    std::string name;
    int rollNumber;
    std::string course;
    int totalMarks;

    Student() : name(""), rollNumber(0), course(""), totalMarks(0) {}

    Student(const std::string& name, int rollNumber, const std::string& course, int totalMarks)
        : name(name), rollNumber(rollNumber), course(course), totalMarks(totalMarks) {}
};

class StudentRecordManagementSystem {
private:
    Student students[MAX_STUDENTS];
    int studentCount;

public:
    StudentRecordManagementSystem() : studentCount(0) {}

    void insertStudent(const std::string& name, int rollNumber, const std::string& course, int totalMarks) {
        if (studentCount < MAX_STUDENTS) {
            students[studentCount++] = Student(name, rollNumber, course, totalMarks);
        } else {
            std::cout << "Student limit reached. Cannot add more students." << std::endl;
        }
    }

    void deleteStudent(int rollNumber) {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].rollNumber == rollNumber) {
                for (int j = i; j < studentCount - 1; ++j) {
                    students[j] = students[j + 1];
                }
                --studentCount;
                std::cout << "Student record deleted successfully." << std::endl;
                return;
            }
        }
        std::cout << "Student record not found." << std::endl;
    }

    void showStudent(int rollNumber) const {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].rollNumber == rollNumber) {
                std::cout << "Name: " << students[i].name << std::endl;
                std::cout << "Roll Number: " << students[i].rollNumber << std::endl;
                std::cout << "Course: " << students[i].course << std::endl;
                std::cout << "Total Marks: " << students[i].totalMarks << std::endl;
                return;
            }
        }
        std::cout << "Student record not found." << std::endl;
    }

    void searchStudent(int rollNumber) const {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].rollNumber == rollNumber) {
                std::cout << "Student found:" << std::endl;
                std::cout << "Name: " << students[i].name << std::endl;
                std::cout << "Roll Number: " << students[i].rollNumber << std::endl;
                std::cout << "Course: " << students[i].course << std::endl;
                std::cout << "Total Marks: " << students[i].totalMarks << std::endl;
                return;
            }
        }
        std::cout << "Student record not found." << std::endl;
    }

    void showAllStudents() const {
        if (studentCount == 0) {
            std::cout << "No student records available." << std::endl;
            return;
        }
        for (int i = 0; i < studentCount; ++i) {
            std::cout << "Name: " << students[i].name << std::endl;
            std::cout << "Roll Number: " << students[i].rollNumber << std::endl;
            std::cout << "Course: " << students[i].course << std::endl;
            std::cout << "Total Marks: " << students[i].totalMarks << std::endl;
            std::cout << "-------------------------" << std::endl;
        }
    }
};

int main() {
    StudentRecordManagementSystem srms;
    int choice;
    std::string name, course;
    int rollNumber, totalMarks;

    do {
        std::cout << "1. Insert Student Record" << std::endl;
        std::cout << "2. Delete Student Record" << std::endl;
        std::cout << "3. Show Student Record" << std::endl;
        std::cout << "4. Search Student Record" << std::endl;
        std::cout << "5. Show All Student Records" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter roll number: ";
                std::cin >> rollNumber;
                std::cout << "Enter course: ";
                std::cin.ignore();
                std::getline(std::cin, course);
                std::cout << "Enter total marks: ";
                std::cin >> totalMarks;
                srms.insertStudent(name, rollNumber, course, totalMarks);
                break;

            case 2:
                std::cout << "Enter roll number to delete: ";
                std::cin >> rollNumber;
                srms.deleteStudent(rollNumber);
                break;

            case 3:
                std::cout << "Enter roll number to show: ";
                std::cin >> rollNumber;
                srms.showStudent(rollNumber);
                break;

            case 4:
                std::cout << "Enter roll number to search: ";
                std::cin >> rollNumber;
                srms.searchStudent(rollNumber);
                break;

            case 5:
                srms.showAllStudents();
                break;

            case 6:
                std::cout << "Exiting..." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
