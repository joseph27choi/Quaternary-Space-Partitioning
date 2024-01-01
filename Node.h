#pragma once
#ifndef NODE_H
#define NODE_H

#include "Point.h"

class Node {
   private:
    static int m;

    double x0, y0, x1, y1;
    Node *top_left, *bottom_left, *bottom_right, *top_right;

    // dynamic memory allocation of size m
    Point *points = new Point[m];
    int arr_size;

   public:
    Node() {};
    Node(double x0, double y0, double x1, double y1);

    double get_x0() { return this->x0; }
    double get_y0() { return this->y0; }
    double get_x1() { return this->x1; }
    double get_y1() { return this->y1; }

    Node *get_top_left() { return top_left; }
    Node *get_bottom_left() { return bottom_left; }
    Node *get_bottom_right() { return bottom_right; }
    Node *get_top_right() { return top_right; }

    void set_top_left(Node *child) { this->top_left = child; }
    void set_bottom_left(Node *child) { this->bottom_left = child; }
    void set_bottom_right(Node *child) { this->bottom_right = child; }
    void set_top_right(Node *child) { this->top_right = child; }

    static int get_m() { return m; }

    Point *get_points() { return this->points; }
    void add_point(double x, double y);

    int get_arr_size() { return this->arr_size; }
    void increment_arr_size() { ++this->arr_size; }

    void expand();
};

#endif