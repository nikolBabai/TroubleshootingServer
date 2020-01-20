//
// Created by oem on 10/01/2020.
//

#ifndef EXX4_POINT_H
#define EXX4_POINT_H

/** we use a point to be the generic of the states in the matrix, every state in the matrix is from type point
 * because it has a clear location this way**/
class Point {
public:
    const int x;
    const int y;

    Point getLocation() {
        return *this;
    }

    Point(const int xIn, const int yIn) : x(xIn), y(yIn) {}

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
