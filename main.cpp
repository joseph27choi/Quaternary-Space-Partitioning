#include <iostream>
#include <string>

#include "Node.cpp"
#include "Point.h"
#include "Quadtree.cpp"

int Node::m = 4;

int main() {
    std::cout << "Welcome to the Quaternary Space Partitioning Tree. " << std::endl;

    double user_x0;
    double user_y0;
    double user_x1;
    double user_y1;

    // prompt user for points
    std::cout << "First, enter your boundary points" << std::endl;
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

    std::string stop = "EXIT";
    std::string inp_str = "";

    while (inp_str.compare("EXIT") != 0) {
        std::cout << "Enter 'I' to insert points, 'S' to search if a point exists, 'EXIT' to exit: ";
        std::cin >> inp_str;

        if (inp_str.compare("I") == 0) {
            double user_x;
            double user_y;
            char cont;
            while (cont != 'n') {
                std::cout << "enter x: ";
                std::cin >> user_x;
                std::cout << "enter y: ";
                std::cin >> user_y;

                if (user_x < user_x0 || user_y < user_y0 || user_x > user_x1 || user_y > user_y1) {
                    std::cout << "outside boundary. quitting program" << std::endl;
                    return 1;
                }

                tree.insert(tree.get_head(), user_x, user_y);

                std::cout << "continue? ";
                std::cin >> cont;
                std::cout << std::endl;
            }
        }
        else if (inp_str.compare("S") == 0) {
            std::cout << "Searching is still in production. Please try again later. " << std::endl;
        }
    }

    tree.print(tree.get_head());

    std::cout << std::endl;
    std::cout << "end of program" << std::endl;
    return 0;
}
