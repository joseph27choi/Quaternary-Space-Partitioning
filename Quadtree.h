#pragma once
#include "Node.h"
#ifndef QUADTREE_H
#define QUADTREE_H

class Quadtree {
   private:
    Node *head;

   public:
    Quadtree(Node*);
    ~Quadtree();

    void print(Node*);
    void insert(Node*, double, double);
    void search(Node*, double, double, double);

    void destroy(Node *p_trav);

    void traverse(Node*);

    Node *get_head() { return this->head; }
};

#endif