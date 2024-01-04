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
    std::cout << std::endl;

    std::cout << "x0: ";
    std::cin >> user_x0;
    std::cout << "y0: ";
    std::cin >> user_y0;
    std::cout << "x1: ";
    std::cin >> user_x1;
    std::cout << "y1: ";
    std::cin >> user_y1;

    std::cout << std::endl;

    Node* head = new Node(user_x0, user_y0, user_x1, user_y1);
    Quadtree tree = Quadtree(head);

    std::string inp_str = "";

    while (inp_str.compare("EXIT") != 0) {
        std::cout << "Enter 'I' to insert points, 'S' to search for points, 'P' to print, 'EXIT' to exit: " << std::endl;
        std::cin >> inp_str;
        std::cout << std::endl;

        if (inp_str.compare("I") == 0) {
            std::cout << "INSERTING NOW" << std::endl;
            std::cout << std::endl;
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

                std::cout << "continue? 'y' or 'n': ";
                std::cin >> cont;
                std::cout << std::endl;
            }
        } else if (inp_str.compare("S") == 0) {
            std::cout << "SEARCHING NOW" << std::endl;
            std::cout << std::endl;

            std::cout << "enter the point you want to search" << std::endl;
            double user_x;
            double user_y;
            double radius;
            std::cout << "enter x: ";
            std::cin >> user_x;
            std::cout << "enter y: ";
            std::cin >> user_y;
            std::cout << "enter the radius of search: ";
            std::cin >> radius;
            tree.search(tree.get_head(), user_x, user_y, radius);
            std::cout << std::endl;
        }

        else if (inp_str.compare("P") == 0) {
            std::cout << "PRINTING NOW" << std::endl;
            std::cout << std::endl;
            tree.print(tree.get_head());
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "end of program" << std::endl;
    return 0;
}
