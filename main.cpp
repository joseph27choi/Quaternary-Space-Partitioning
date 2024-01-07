#include <iostream>
#include <string>

#include "Node.cpp"
#include "Point.h"
#include "Quadtree.cpp"

int Node::m = 4;

// declarations
void set_boundary(double&, double&, double&, double&);
void handle_input(Quadtree& tree, char& cont, double& user_x0, double& user_y0, double& user_x1, double& user_y1);
void handle_search(Quadtree& tree);
void handle_print(Quadtree& tree);
int main();

// definitions
int main() {
    std::cout << "Welcome to the Quaternary Space Partitioning Tree. " << std::endl;

    double user_x0, user_y0, user_x1, user_y1;

    set_boundary(user_x0, user_y0, user_x1, user_y1);

    Node* head = new Node(user_x0, user_y0, user_x1, user_y1);
    Quadtree tree = Quadtree(head);

    std::string inp_str = "";
    while (inp_str.compare("EXIT") != 0) {
        std::cout << "Enter 'I' to insert points, 'S' to search for points, 'P' to print, 'EXIT' to exit: " << std::endl;
        std::cin >> inp_str;
        std::cout << std::endl;

        if (inp_str.compare("I") == 0) {
            char cont;
            handle_input(tree, cont, user_x0, user_y0, user_x1, user_y1);
            cont = 0;
        } else if (inp_str.compare("S") == 0) {
            handle_search(tree);
        } else if (inp_str.compare("P") == 0) {
            handle_print(tree);
        }
    }

    std::cout << std::endl;
    std::cout << "end of program" << std::endl;
    return 0;
}

void set_boundary(double& user_x0, double& user_y0, double& user_x1, double& user_y1) {
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
}

void handle_input(Quadtree& tree, char& cont, double& user_x0, double& user_y0, double& user_x1, double& user_y1) {
    std::cout << "INSERTING NOW" << std::endl;
    std::cout << std::endl;
    double user_x;
    double user_y;
    while (cont != 'n') {
        std::cout << "enter x: ";
        std::cin >> user_x;
        std::cout << "enter y: ";
        std::cin >> user_y;

        if (user_x < user_x0 || user_y < user_y0 || user_x > user_x1 || user_y > user_y1) {
            std::cout << "outside boundary. quitting program" << std::endl;
            exit(1);
        }

        tree.insert(tree.get_head(), user_x, user_y);

        std::cout << "continue? 'y' or 'n': ";
        std::cin >> cont;
        std::cout << std::endl;
    }
}

void handle_search(Quadtree& tree) {
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

void handle_print(Quadtree& tree) {
    std::cout << "PRINTING NOW" << std::endl;
    std::cout << std::endl;
    tree.print(tree.get_head());
    std::cout << std::endl;
    std::cout << "." << std::endl;
    std::cout << "." << std::endl;
    std::cout << "." << std::endl;
    std::cout << std::endl;
}