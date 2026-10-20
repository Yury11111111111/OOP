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

    virtual ~User() = default;

    virtual void displayInfo() {
        cout << "ID: " << id << " | Name: " << name << " | Email: " << email << endl;
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
        cout << name << " enrolled in course #" << courseId << endl;
    }
};

class Instructor : public User {
public:
    Instructor(int userId, string userName, string userEmail)
        : User(userId, userName, userEmail) {}

    void createCourse(string title) {
        cout << "Instructor " << name << " created course: " << title << endl;
    }
};

class Admin : public User {
public:
    Admin(int userId, string userName, string userEmail)
        : User(userId, userName, userEmail) {}

    void manageUsers() {
        cout << "Admin " << name << " is managing users" << endl;
    }
};

class Lesson {
private:
    int id;
    string title;

public:
    Lesson(int lessonId, string lessonTitle) {
        id = lessonId;
        title = lessonTitle;
    }

    void displayInfo() {
        cout << "Lesson #" << id << ": " << title << endl;
    }
};

class Module {
private:
    int id;
    string title;
    vector<Lesson*> lessons;

public:
    Module(int moduleId, string moduleTitle) {
        id = moduleId;
        title = moduleTitle;
    }

    void addLesson(Lesson* lesson) {
        lessons.push_back(lesson);
    }

    void displayInfo() {
        cout << "Module #" << id << ": " << title << endl;
    }
};

class Course {
private:
    int id;
    string title;
    vector<Module*> modules;

public:
    Course(int courseId, string courseTitle) {
        id = courseId;
        title = courseTitle;
    }

    void addModule(Module* module) {
        modules.push_back(module);
    }

    void displayInfo() {
        cout << "Course #" << id << ": " << title << endl;
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
        cout << "Enrollment #" << id << endl;
        if (student != nullptr) student->displayInfo();
        if (course != nullptr) course->displayInfo();
    }
};

class Progress {
private:
    Student* student;
    Lesson* lesson;
    bool isCompleted;

public:
    Progress(Student* s, Lesson* l, bool completed) {
        student = s;
        lesson = l;
        isCompleted = completed;
    }

    void displayInfo() {
        cout << "Progress: lesson " << (isCompleted ? "completed" : "not completed") << endl;
    }
};

class Review {
private:
    Student* student;
    Course* course;
    string text;

public:
    Review(Student* s, Course* c, string reviewText) {
        student = s;
        course = c;
        text = reviewText;
    }

    void displayInfo() {
        cout << "Course review: " << text << endl;
    }
};

class Certificate {
private:
    Student* student;
    Course* course;

public:
    Certificate(Student* s, Course* c) {
        student = s;
        course = c;
    }

    void displayInfo() {
        cout << "Certificate of course completion successfully issued" << endl;
    }
};

int main() {
    Student student(1, "Ivan", "ivan@example.com");
    Instructor instructor(2, "Petr", "petr@example.com");
    Admin admin(3, "Anna", "anna@example.com");

    Lesson lesson1(1, "Introduction to OOP");
    Module module1(1, "Chapter 1. Basics");
    module1.addLesson(&lesson1);

    Course course(101, "C++ Basics");
    course.addModule(&module1);

    instructor.createCourse("C++ Basics");
    admin.manageUsers();
    student.enroll(101);

    Enrollment enrollment(1, &student, &course);
    
    cout << "\n--- Data Check ---" << endl;
    enrollment.displayInfo();
    
    Progress progress(&student, &lesson1, true);
    progress.displayInfo();

    Review review(&student, &course, "Very useful course!");
    review.displayInfo();

    Certificate certificate(&student, &course);
    certificate.displayInfo();

    return 0;
}