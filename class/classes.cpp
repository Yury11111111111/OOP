#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {
protected:
    int id;
    string name;
    string email;

public:
    User(int userId, string userName, string userEmail) {
        id = userId;
        name = userName;
        email = userEmail;
    }

    void displayInfo() {
        cout << "ID: " << id << endl;
        cout << "Имя: " << name << endl;
        cout << "Email: " << email << endl;
    }
};

class Student : public User {
private:
    vector<int> enrollments;

public:
    Student(int userId, string userName, string userEmail)
        : User(userId, userName, userEmail) {}

    void enroll(int courseId) {
        enrollments.push_back(courseId);
        cout << name << " записался на курс #" << courseId << endl;
    }
};

class Course {
private:
    int id;
    string title;

public:
    Course(int courseId, string courseTitle) {
        id = courseId;
        title = courseTitle;
    }

    void displayInfo() {
        cout << "Курс #" << id << ": " << title << endl;
    }
};

class Enrollment {
private:
    int id;
    Student* student;
    Course* course;

public:
    Enrollment(int enrollmentId, Student* s, Course* c) {
        id = enrollmentId;
        student = s;
        course = c;
    }

    void displayInfo() {
        cout << "Запись #" << id << endl;
        if (student != nullptr) student->displayInfo();
        if (course != nullptr) course->displayInfo();
    }
};

int main() {
    Student student(1, "Иван", "ivan@example.com");
    Course course(101, "Основы C++");

    Enrollment enrollment(1, &student, &course);

    student.enroll(101);
    enrollment.displayInfo();

    return 0;
}