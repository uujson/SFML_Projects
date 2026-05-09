#pragma once

#include "../settings/settings.h"

struct quadNode{
    int32_t 
};

template<typename T>
class quadTree : public sf::Drawable{
    private:
        std::vector<quadNode> nodes;
        std::vector<std::shared_ptr<T>> elements;
    public:
};