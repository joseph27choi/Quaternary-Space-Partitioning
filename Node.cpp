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

    // next pointers
    this->top_left = this->bottom_left = this->bottom_right = this->top_right = nullptr;
}

void Node::add_point(double& x, double& y) {
    // add point to the end of the array
    if (this->arr_size == m) {
        std::cout << "didn't add, need to expand tree" << std::endl;
        return;
    }

    // package point
    Point descartes = Point(x, y);

    this->points[this->arr_size] = descartes;
    ++this->arr_size;

    return;
}

void Node::expand() {
    std::cout << "on void expanding" << std::endl;

    // add the four children node with quarter the size
    double x_mid = 0.5 * (this->x1 + this->x0);
    double y_mid = 0.5 * (this->y1 + this->y0);

    Node* nthGenTL = new Node(this->x0, y_mid, x_mid, this->y1);
    Node* nthGenBL = new Node(this->x0, this->y0, x_mid, y_mid);
    Node* nthGenBR = new Node(x_mid, this->y0, this->x1, y_mid);
    Node* nthGenTR = new Node(x_mid, y_mid, this->x1, this->y1);

    // append to current node
    this->top_left = nthGenTL;
    this->bottom_left = nthGenBL;
    this->bottom_right = nthGenBR;
    this->top_right = nthGenTR;

    // distribute the points to the children
    std::cout << "iterating through array, if there is segmentation, the arr was exceeding. On void Node::expand" << std::endl;
    for (int i{0}; i < m; ++i) {
        std::cout << "iterating" << points[i].get_x() << ", " << points[i].get_y() << std::endl;
        if (points[i].get_x() <= x_mid && points[i].get_y() >= y_mid) {
            std::cout << "gave point to top left" << std::endl;
        } else if (points[i].get_x() <= x_mid && points[i].get_y() < y_mid) {
            std::cout << "gave point to bottom left" << std::endl;
        } else if (points[i].get_x() > x_mid && points[i].get_y() < y_mid) {
            std::cout << "gave point to bottom right" << std::endl;
        } else if (points[i].get_x() > x_mid && points[i].get_y() >= y_mid) {
            std::cout << "gave point to top right" << std::endl;
        } else {
            std::cout << "error value: " << points[i].get_x() << points[i].get_y() << std::endl;
        }
        
        Point temp(0,0);
        points[i] = temp;
    }

}
