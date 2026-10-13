#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class Box;

class Ball {
private:
    string color;
    Box* box = nullptr;

public:
    Ball(const string& color) : color(color) {}

    Ball(const Ball&) = delete;
    Ball& operator=(const Ball&) = delete;

    const string& get_color() const { return color; }

    Box* get_box() const { return box; }

    void set_box(Box* new_box) { box = new_box; }

    void show_place() const;
};

class Box {
private:
    string name;
    vector<reference_wrapper<Ball>> balls;

public:
    Box(const string& name) : name(name) {}

    Box(const Box&) = delete;
    Box& operator=(const Box&) = delete;

    const string& get_name() const { return name; }

    void add_ball(Ball& ball) {
        if (ball.get_box() == this) return;

        if (ball.get_box() != nullptr) {
            ball.get_box()->remove_ball(ball);
        }

        ball.set_box(this);
        balls.push_back(ball);
    }

    void remove_ball(Ball& ball) {
        auto it = find_if(balls.begin(), balls.end(),
            [&ball](const reference_wrapper<Ball>& r) {
                return &r.get() == &ball;
            });
        if (it != balls.end()) {
            balls.erase(it);
            ball.set_box(nullptr);
        }
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

    box1.add_ball(green);

    box1.show_balls();
    box2.show_balls();

    box1.remove_ball(blue);

    box1.show_balls();
    box2.show_balls();

    red.show_place();
    blue.show_place();
    green.show_place();
    yellow.show_place();

    return 0;
}