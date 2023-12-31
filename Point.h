#pragma once
#ifndef POINT_H
#define POINT_H

class Point {
private:
    double x;
    double y;
public:
    Point() {};
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    double get_x() { return this->x; }
    double get_y() { return this->y; }

    void set_x(double x) { this->x = x; }
    void set_y(double y) { this->y = y; }
};

#endif