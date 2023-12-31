#include "Quadtree.h"

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
    std::cout << "promise fulfilled" << std::endl;
    std::cout << trav->get_x0() << ", ";
    std::cout << trav->get_y0() << ", ";
    std::cout << trav->get_x1() << ", ";
    std::cout << trav->get_y1() << " and ";
    std::cout << trav->get_points()[0].get_x() << trav->get_points()[0].get_y() << std::endl;

    return;
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
        
        // see if able to add point
        if (p_trav->get_arr_size() == p_trav->get_m())
        {
            std::cout << "must expand before adding" << std::endl;
            p_trav->expand();
            return;
        }

        p_trav->add_point(x,y);
        std::cout << "successfully added point" << std::endl;
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

    // base case 2: next pointers are nullptrs
    std::cout << p_trav->get_x0() << ", ";
    std::cout << p_trav->get_y0() << ", ";
    std::cout << p_trav->get_x1() << ", ";
    std::cout << p_trav->get_y1() << std::endl;
    // delete the array in there as well
    delete[] p_trav->get_points();
    delete p_trav;
    p_trav = nullptr;

    return;
}
