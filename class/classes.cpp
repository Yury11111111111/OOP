#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * ПРЕДМЕТНАЯ ОБЛАСТЬ: Платформа онлайн-курсов
 * 
 * КРАТКОЕ ПОЯСНЕНИЕ ПО АССОЦИАТИВНЫМ СВЯЗЯМ:
 * 1. Наследование: Классы Student, Instructor, Admin наследуются от User
 * 2. Связь 1 ко многим (Агрегация): Course содержит модули, Module содержит уроки
 * 3. Связь многие ко многим: Реализована через ассоциативные классы (Enrollment, Review, Certificate)
 * Связи реализованы с помощью указателей (*) и векторов (vector), что позволяет 
 * объектам ссылаться друг на друга без дублирования данных
 */

// Базовый класс, реализующий инкапсуляцию общих свойств
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

// НАСЛЕДОВАНИЕ: Студент является частным случаем пользователя
class Student : public User {
private:
    vector<int> enrollments; // Список ID курсов, на которые записан студент

public:
    Student(int userId, string userName, string userEmail)
        : User(userId, userName, userEmail) {}

    void enroll(int courseId) {
        enrollments.push_back(courseId);
        cout << name << " enrolled in course #" << courseId << endl;
    }
};

// НАСЛЕДОВАНИЕ: Преподаватель
class Instructor : public User {
public:
    Instructor(int userId, string userName, string userEmail)
        : User(userId, userName, userEmail) {}

    void createCourse(string title) {
        cout << "Instructor " << name << " created course: " << title << endl;
    }
};

// НАСЛЕДОВАНИЕ: Администратор
class Admin : public User {
public:
    Admin(int userId, string userName, string userEmail)
        : User(userId, userName, userEmail) {}

    void manageUsers() {
        cout << "Admin " << name << " is managing users" << endl;
    }
};

// Независимая сущность (Урок)
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

// СВЯЗЬ 1 КО МНОГИМ: Модуль содержит множество уроков
class Module {
private:
    int id;
    string title;
    vector<Lesson*> lessons; // Ассоциация с уроками

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

// СВЯЗЬ 1 КО МНОГИМ: Курс содержит множество модулей
class Course {
private:
    int id;
    string title;
    vector<Module*> modules; // Ассоциация с модулями

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

// СВЯЗЬ МНОГИЕ КО МНОГИМ: Ассоциативный класс, связывающий Студента и Курс.
// Хранит указатели на оба объекта.
class Enrollment {
private:
    int id;
    Student* student; // Ссылка на студента
    Course* course;   // Ссылка на курс

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

// АССОЦИАЦИЯ: Класс прогресса связывает Студента и конкретный Урок
class Progress {
private:
    Student* student; // Кто проходит
    Lesson* lesson;   // Какой урок
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

// АССОЦИАЦИЯ: Отзыв связывает Студента и Курс
class Review {
private:
    Student* student; // Автор отзыва
    Course* course;   // Курс, на который оставлен отзыв
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

// АССОЦИАЦИЯ: Сертификат связывает Студента и пройденный Курс
class Certificate {
private:
    Student* student; // Кому выдан
    Course* course;   // За какой курс

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
    // Создание объектов ролей (наследники User)
    Student student(1, "Ivan", "ivan@example.com");
    Instructor instructor(2, "Petr", "petr@example.com");
    Admin admin(3, "Anna", "anna@example.com");

    // Создание контента (Курс -> Модуль -> Урок)
    Lesson lesson1(1, "Introduction to OOP");
    Module module1(1, "Chapter 1. Basics");
    module1.addLesson(&lesson1); // Связываем урок с модулем

    Course course(101, "C++ Basics");
    course.addModule(&module1); // Связываем модуль с курсом

    // Демонстрация действий ролей
    instructor.createCourse("C++ Basics");
    admin.manageUsers();
    student.enroll(101);

    // Демонстрация ассоциативных связей
    Enrollment enrollment(1, &student, &course); // Связываем студента и курс
    
    cout << "\n--- Data Check ---" << endl;
    enrollment.displayInfo();
    
    // Связываем прогресс, отзыв и сертификат с конкретными объектами
    Progress progress(&student, &lesson1, true);
    progress.displayInfo();

    Review review(&student, &course, "Very useful course!");
    review.displayInfo();

    Certificate certificate(&student, &course);
    certificate.displayInfo();

    return 0;
}