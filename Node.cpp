#include "Node.h"

#include <iostream>
#include <string>

#include "Point.h"

// a new node represents a grid section
Node::Node(double x0, double y0, double x1, double y1) {
    // boundaries
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;

    arr_size = 0;
    // initialize array
    this->points = new Point[m];

    // next pointers
    this->top_left = this->bottom_left = this->bottom_right = this->top_right = nullptr;
}

void Node::add_point(double x, double y) {
    // package point
    Point descartes = Point(x, y);

    this->points[this->arr_size] = descartes;
    ++this->arr_size;

    return;
}

void Node::expand() {
    // add the four children node with quarter the size
    double x_mid = 0.5 * (this->x1 + this->x0);
    double y_mid = 0.5 * (this->y1 + this->y0);

    Node* nthGenTL = new Node(this->x0, y_mid, x_mid, this->y1);
    if (nthGenTL == nullptr) {
        std::cout << "cannot expand tree" << std::endl;
        exit(1);
    }
    Node* nthGenBL = new Node(this->x0, this->y0, x_mid, y_mid);
    if (nthGenBL == nullptr) {
        std::cout << "cannot expand tree" << std::endl;
        exit(1);
    }
    Node* nthGenBR = new Node(x_mid, this->y0, this->x1, y_mid);
    if (nthGenBR == nullptr) {
        std::cout << "cannot expand tree" << std::endl;
        exit(1);
    }
    Node* nthGenTR = new Node(x_mid, y_mid, this->x1, this->y1);
    if (nthGenTR == nullptr) {
        std::cout << "cannot expand tree" << std::endl;
        exit(1);
    }

    // append to current node
    this->top_left = nthGenTL;
    this->bottom_left = nthGenBL;
    this->bottom_right = nthGenBR;
    this->top_right = nthGenTR;

    // distribute the points to the children
    for (int i = 0; i < m; i++) {
        std::cout << "adding point " << points[i].get_x() << ", " << points[i].get_y() << " to ";
        if (this->points[i].get_x() <= x_mid && points[i].get_y() >= y_mid) {
            std::cout << "top left" << std::endl;
            this->top_left->add_point(points[i].get_x(), points[i].get_y());
        } else if (points[i].get_x() <= x_mid && points[i].get_y() < y_mid) {
            std::cout << "bottom left" << std::endl;
            this->bottom_left->add_point(points[i].get_x(), points[i].get_y());
        } else if (points[i].get_x() > x_mid && points[i].get_y() < y_mid) {
            std::cout << "bottom right" << std::endl;
            this->bottom_right->add_point(points[i].get_x(), points[i].get_y());
        } else if (points[i].get_x() > x_mid && points[i].get_y() >= y_mid) {
            std::cout << "top right" << std::endl;
            this->top_right->add_point(points[i].get_x(), points[i].get_y());
        } else {
            std::cout << "error value: " << points[i].get_x() << points[i].get_y() << std::endl;
        }
    }

    // free the array from the parent pointer because it is no longer needed and points to null
    if (this->points != nullptr) {
        delete[] this->points;
    }
    this->points = nullptr;
}