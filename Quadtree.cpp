#include "Quadtree.h"

#include <cmath>
#include <iostream>
#include <string>

#include "Node.h"

Quadtree::Quadtree(Node* first_node) {
    // default constructor points to nothing
    this->head = first_node;
}

// just testing, need to fix
void Quadtree::print(Node* trav) {
    // base case 1: head does not exist yet
    if (trav == nullptr) {
        return;
    }

    // base root not reached, keep printing
    if (trav->get_top_left() != nullptr || trav->get_bottom_left() != nullptr ||
        trav->get_bottom_right() != nullptr || trav->get_top_right() != nullptr) {
        print(trav->get_top_left());
        print(trav->get_bottom_left());
        print(trav->get_bottom_right());
        print(trav->get_top_right());
    }

    // reached end node? print
    std::cout << "(";
    std::cout << trav->get_x0() << ", ";
    std::cout << trav->get_y0() << ", ";
    std::cout << trav->get_x1() << ", ";
    std::cout << trav->get_y1() << "";
    std::cout << ") ";
    if (trav->get_points() != nullptr) {
        std::cout << " contains ";
        for (int i = 0, n = trav->get_arr_size(); i < n; ++i) {
            std::cout << "(";
            std::cout << trav->get_points()[i].get_x() << ", " << trav->get_points()[i].get_y();
            std::cout << ") ";
        }
        std::cout << std::endl;
    } else {
        std::cout << " no longer contains points." << std::endl;
    }

    return;
}

void Quadtree::search(Node* p_trav, double x, double y, double d) {
    // Base case: reached leaf, see if any point exists in this region
    if (p_trav->get_bottom_left() == nullptr || p_trav->get_bottom_right() == nullptr ||
        p_trav->get_top_left() == nullptr || p_trav->get_top_right() == nullptr) {
        bool point_exists = p_trav->get_arr_size() != 0 ? true : false;
        std::cout << "point exists? " << point_exists << std::endl;

        // Check if any points within the leaf node fall within the radius
        for (int i = 0; i < p_trav->get_arr_size(); ++i) {
            double point_x = p_trav->get_points()[i].get_x();
            double point_y = p_trav->get_points()[i].get_y();

            double distance = std::sqrt(std::pow((point_x - x), 2) + std::pow((point_y - y), 2));

            if (distance <= d) {
                std::cout << "Point within radius: (" << point_x << ", " << point_y << ")" << std::endl;
            }
        }

        return;
    }

    // Otherwise, direct to the children nodes
    double x_mid = 0.5 * (p_trav->get_x1() + p_trav->get_x0());
    double y_mid = 0.5 * (p_trav->get_y1() + p_trav->get_y0());

    // Recursively search all child nodes
    if (x <= x_mid && y >= y_mid) {
        search(p_trav->get_top_left(), x, y, d);
        if (std::abs(x - x_mid) >= d) {
            search(p_trav->get_top_right(), x, y, d);
        }
        if (std::abs(y - y_mid) >= d) {
            search(p_trav->get_bottom_left(), x, y, d);
        }
        if (std::abs(x - x_mid) >= d && std::abs(y - y_mid) >= d) {
            search(p_trav->get_bottom_right(), x, y, d);
        }
    } else if (x <= x_mid && y < y_mid) {
        search(p_trav->get_bottom_left(), x, y, d);
        if (std::abs(x - x_mid) >= d) {
            search(p_trav->get_top_left(), x, y, d);
        }
        if (std::abs(y - y_mid) >= d) {
            search(p_trav->get_bottom_right(), x, y, d);
        }
        if (std::abs(x - x_mid) >= d && std::abs(y - y_mid) >= d) {
            search(p_trav->get_top_right(), x, y, d);
        }
    } else if (x > x_mid && y < y_mid) {
        search(p_trav->get_bottom_right(), x, y, d);
        if (std::abs(x - x_mid) >= d) {
            search(p_trav->get_top_right(), x, y, d);
        }
        if (std::abs(y - y_mid) >= d) {
            search(p_trav->get_bottom_left(), x, y, d);
        }
        if (std::abs(x - x_mid) >= d && std::abs(y - y_mid) >= d) {
            search(p_trav->get_top_left(), x, y, d);
        }
    } else if (x > x_mid && y >= y_mid) {
        search(p_trav->get_top_right(), x, y, d);
        if (std::abs(x - x_mid) >= d) {
            search(p_trav->get_top_left(), x, y, d);
        }
        if (std::abs(y - y_mid) >= d) {
            search(p_trav->get_bottom_right(), x, y, d);
        }
        if (std::abs(x - x_mid) >= d && std::abs(y - y_mid) >= d) {
            search(p_trav->get_bottom_left(), x, y, d);
        }
    }
}

void Quadtree::insert(Node* p_trav, double x, double y) {
    // base case: no tree
    if (p_trav == nullptr) {
        std::cout << "no tree to insert to" << std::endl;
        return;
    }

    // base case: all children are nullpointers
    if (p_trav->get_bottom_left() == nullptr || p_trav->get_bottom_right() == nullptr ||
        p_trav->get_top_left() == nullptr || p_trav->get_top_right() == nullptr) {
        p_trav->add_point(x, y);
        std::cout << "successfully added point" << std::endl;
        std::cout << "(";
        std::cout << p_trav->get_x0() << ", ";
        std::cout << p_trav->get_y0() << ", ";
        std::cout << p_trav->get_x1() << ", ";
        std::cout << p_trav->get_y1() << "";
        std::cout << ") has " << p_trav->get_arr_size() << " elements" << std::endl;

        // if array is full, expand and redistribute
        if (p_trav->get_arr_size() == p_trav->get_m()) {
            std::cout << std::endl;
            std::cout << "must expand" << std::endl;
            p_trav->expand();
            std::cout << std::endl;

            std::cout << "current working tree..." << std::endl;
            print(p_trav);
            std::cout << std::endl
                      << std::endl;
            return;
        }

        return;
    }

    // otherwise, direct recursion to correct node
    double x_mid = 0.5 * (p_trav->get_x1() + p_trav->get_x0());
    double y_mid = 0.5 * (p_trav->get_y1() + p_trav->get_y0());

    if (x <= x_mid && y >= y_mid) {
        std::cout << "called top left" << std::endl;
        insert(p_trav->get_top_left(), x, y);
    } else if (x <= x_mid && y < y_mid) {
        std::cout << "called bottom left" << std::endl;
        insert(p_trav->get_bottom_left(), x, y);
    } else if (x > x_mid && y < y_mid) {
        std::cout << "called bottom right" << std::endl;
        insert(p_trav->get_bottom_right(), x, y);
    } else if (x > x_mid && y >= y_mid) {
        std::cout << "called top right" << std::endl;
        insert(p_trav->get_top_right(), x, y);
    } else {
        std::cout << "intruiging value: " << x << y << std::endl;
    }

    return;
}

Quadtree::~Quadtree() {
    // recursively destroy
    Node* p_trav = this->head != nullptr ? this->head : nullptr;
    if (p_trav != nullptr) {
        std::cout << "destructor started" << std::endl;
        destroy(p_trav);
    }
}

void Quadtree::destroy(Node* p_trav) {
    // base case: no tree existed in the first place
    if (p_trav == nullptr) {
        return;
    }

    // if next pointer is still not null, make a promise with the next nodes
    if (p_trav->get_top_left() != nullptr && p_trav->get_bottom_left() != nullptr &&
        p_trav->get_bottom_right() != nullptr && p_trav->get_top_right() != nullptr) {
        destroy(p_trav->get_top_left());
        destroy(p_trav->get_bottom_left());
        destroy(p_trav->get_bottom_right());
        destroy(p_trav->get_top_right());
    }

    // delete the node
    if (p_trav->get_points() != nullptr) {
        delete[] p_trav->get_points();
    }
    delete p_trav;
    p_trav = nullptr;

    return;
}