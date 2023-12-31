#include <iostream>
#include <string>

#include "Node.cpp"
#include "Point.h"
#include "Quadtree.cpp"

int Node::m = 6;

int main() {
    double user_x0;
    double user_y0;
    double user_x1;
    double user_y1;

    // prompt user for points
    std::cout << "enter your boundary" << std::endl;
    std::cout << "x0: ";
    std::cin >> user_x0;
    std::cout << "y0: ";
    std::cin >> user_y0;
    std::cout << "x1: ";
    std::cin >> user_x1;
    std::cout << "y1: ";
    std::cin >> user_y1;

    Node* head = new Node(user_x0, user_y0, user_x1, user_y1);
    Quadtree tree = Quadtree(head);

    std::string s;
    std::string stop = "stop";

    double user_x;
    double user_y;
    do {
        std::cout << "enter x: ";
        std::cin >> user_x;
        std::cout << "enter y: ";
        std::cin >> user_y;

        if (user_x < user_x0 || user_y < user_y0 || user_x > user_x1 || user_y > user_y1)
        {
            std::cout << "outside boundary. quitting program" << std::endl;
            return 1;
        }

        tree.insert(tree.get_head(), user_x, user_y);
    } while (s.compare(stop) != 0);

    

    tree.print(tree.get_head());
    return 0;
}
