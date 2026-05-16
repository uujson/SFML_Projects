#include "quadtree.h"
#include "object.h"

quadtree::quadtree(int n){
    objectCount = n*n;
    vertices.setPrimitiveType(sf::PrimitiveType::Points);
    vertices.resize(n*n);
    int temp = int(ceil(sqrtf32(float(n*n))));
    int space = windowHeight/(n+1);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            std::shared_ptr<object> obj(new object({float(j+1)*space,float(i+1)*space}));
            elements.push_back(obj);
        }
    }
}

void quadtree::update(){
    for (int i = 0; i < objectCount; i++){
        for (int j = i+1; j < objectCount; j++){
            if (elements[i]->estimate(*elements[j])){
                if (elements[i]->collision(*elements[j])){
                    elements[i]->collide(*elements[j]);
                }
            }
        }
    }
    for (auto i : elements){ i->update(); }
    for (int i = 0; i < objectCount; i++){ vertices[i].position = elements[i]->getPosition(); }
}

void quadtree::draw(sf::RenderTarget &target, sf::RenderStates state) const{
    target.draw(vertices);
}