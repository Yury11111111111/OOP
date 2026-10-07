#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class Box;

class Ball {
private:
    string color;
    Box* box = nullptr;

public:
    Ball(const string& color) : color(color) {}

    const string& get_color() const {
        return color;
    }

    void set_box(Box* new_box) {
        box = new_box;
    }

    void show_place() const;
};

class Box {
private:
    string name;
    vector<reference_wrapper<Ball>> balls;

public:
    Box(const string& name) : name(name) {}

    const string& get_name() const {
        return name;
    }

    void add_ball(Ball& ball) {
        ball.set_box(this);
        balls.push_back(ball);
    }

    void show_balls() const {
        cout << "Box " << name << ": ";
        for (const auto& ball_ref : balls) {
            cout << ball_ref.get().get_color() << " ";
        }
        cout << "\n";
    }
};

void Ball::show_place() const {
    if (box == nullptr) {
        cout << color << " ball is not in a box\n";
    } else {
        cout << color << " ball is in " << box->get_name() << "\n";
    }
}

int main() {
    Ball red("red");
    Ball blue("blue");
    Ball green("green");
    Ball yellow("yellow");

    Box box1("A");
    Box box2("B");

    box1.add_ball(red);
    box1.add_ball(blue);
    box2.add_ball(green);

    box1.show_balls();
    box2.show_balls();

    red.show_place();
    blue.show_place();
    green.show_place();
    yellow.show_place();

    return 0;
}