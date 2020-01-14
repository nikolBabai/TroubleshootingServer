//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_POINT_H
#define EXX4_POINT_H

class Point {
public:
    const int x;
    const int y;

    Point getLocation() {
        return *this;
    }

    Point(const int x, const int y) : x(x), y(y) {}

    bool operator==(Point s) {
        return (this->x == s.x) && (this->y == s.y);
    }

    int getX() {
        return this->x;
    }

    int getY() {
        return this->y;
    }
};

#endif //EXX4_POINT_H
