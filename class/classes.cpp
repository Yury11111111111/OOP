#include <iostream>
#include <string>
#include <vector>

using namespace std;



class Course {
private:
    string name;
public:
    Course(string name) : name(name) {}
};

class User {
private:
    string name;
    string email;
    vector<Course> courses;
public:
    User(string name, string email) : name(name), email(email) {};

    void enroll(Course course) {
        courses.push_back(course);
    }
    void showData() {
        cout << name << email;
    }
};

int main() {
    User user1("user1", "email");
    user1.showData();
    Course course1("course1");
    user1.enroll(course1);
    return 0;
}