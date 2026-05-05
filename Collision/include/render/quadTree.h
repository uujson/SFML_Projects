#pragma once

#include "../settings/settings.h"
#include "../object/object.h"

#define NW 0
#define NE 1
#define SE 2
#define SW 3

class Node : sf::Drawable, sf::Transformable{
    private:
        Node *subnodes[4];
        bool isLeaf;
        sf::Vector2f dim;
        sf::Vector2f pos;
        std::vector<std::shared_ptr<object>> objects;
        void split();
    public:
        Node(sf::Vector2f size, sf::Vector2f p);
        Node();
        void add(object o, int id);
        void clear();
        void contains(std::shared_ptr<object> o);
        bool operator>(Node &other);
        inline bool contains(int id);
};

class quadTree : sf::Drawable, sf::Transformable{
    private:
        Node *tree;
};