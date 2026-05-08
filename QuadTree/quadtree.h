#pragma once

#include "settings.h"
#include "object.h"

#define MAX_OBJECTS 8



class node{
    private:
        node* nodes;
        sf::Vector2f position;
        sf::Vector2f dimensions;
        std::vector<std::shared_ptr<object>> elements;
        bool isLeaf;
        void split();
        bool contains(std::shared_ptr<object> element);
        void insert(std::shared_ptr<object> element);
    public:
        node();
        node(sf::Vector2f xy, sf::Vector2f dims);
        void add(std::shared_ptr<object> element);
        void update();
};

class quadtree: public sf::Drawable, public sf::Transformable{
    private:
        // node* root;
        sf::VertexArray vertices;
        int objectCount;
        std::vector<std::shared_ptr<object>> elements;
    public:
        quadtree(int n);
        // void addElement(std::shared_ptr<object> element);
        void update();
        void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};

// 