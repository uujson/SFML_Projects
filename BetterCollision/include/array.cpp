#include "array.h"

array::array(){
    number = 10;
    cellSize = windowHeight/MAXGRIDS;
    grids = new grid*[MAXGRIDS];
    for (int i = 0; i < MAXGRIDS; i++){
        grids[i] = new grid[MAXGRIDS];
        for(int j = 0; j < MAXGRIDS; j++){
            grids[i][j] = grid(cellSize, i, j);
        }
    }
    initialize(number);
}

array::array(int n){
    number = n;
    cellSize = windowHeight/MAXGRIDS;
    grids = new grid*[MAXGRIDS];
    for (int i = 0; i < MAXGRIDS; i++){
        grids[i] = new grid[MAXGRIDS];
        for(int j = 0; j < MAXGRIDS; j++){
            grids[i][j] = grid(cellSize, i, j);
        }
    }
    initialize(n);
}

void array::gridUpdate(std::shared_ptr<object> o){
    for (int i = 0; i < MAXGRIDS; i++){
        for (int j = 0; j < MAXGRIDS; j++){
            if (grids[i][j].contains(o)){
                grids[i][j].insert(o);
            }
        }
    }
    // vector2f temp = o->getPosition();
    // int tempX = int(temp.x/cellSize);
    // int tempY = int(temp.y/cellSize);
    // int x[3] = {std::max(0,tempX-1), tempX, std::min(MAXGRIDS-1, tempX+1)};
    // int y[3] = {std::max(0,tempY-1), tempY, std::min(MAXGRIDS-1, tempY+1)};
    // for (int i = 0; i < 3; i++){
    //     for (int j = 0; j < 3; j++){
    //         if (grids[x[i]][y[j]].contains(o)){
    //             grids[x[i]][y[j]].insert(o);
    //         }
    //     }
    // }
}

void array::initialize(int n){
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(n*n*24);
    float point = windowHeight/float(n+1);
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            sf::Vertex *triangle = &vertices[(i+j*n)*24];
            sf::Color color = sf::Color(rand()%256,rand()%256,rand()%256,128);
            float x = float(i+1)*point;
            float y = float(j+1)*point;
            std::shared_ptr<object> o(new object(x,y));
            gridUpdate(o);
            for (int k = 0; k < 24; k++){
                triangle[k].color = color;
            }

            objects.push_back(o);
        }
    }
}

void array::update(){
    for (int i = 0; i < MAXGRIDS; i++){
        for (int j = 0; j < MAXGRIDS; j++){
            if (!grids[i][j].isEmpty()){
                std::vector<std::shared_ptr<object>> o = grids[i][j].update();
                if (o.size() != 0){
                    for (int k = 0; k < o.size(); k++){ gridUpdate(o[k]); }
                }
            }
        }
    }
    for(int i = 0; i < objects.size(); i++){
        objects[i]->update();
        vector2f temp = objects[i]->getVelocity()*tickTime;
        sf::Vector2f transform(temp.x, temp.y);
        sf::Vertex *triangle = &vertices[(i)*24];
            float x = objects[i]->getPosition().x;
            float y = objects[i]->getPosition().y;
            float r = objects[i]->getRadius();

            float X[5] = {
                x-r, x-r*SQRT_TWO_INVERSE, x, x+r*SQRT_TWO_INVERSE, x+r
            };
            float Y[5] = {
                    y-r,
                y-r*SQRT_TWO_INVERSE,
                    y,
                y+r*SQRT_TWO_INVERSE,
                    y+r
            };
            sf::Vector2f points[9] = {
                                {X[2],Y[0]},
                        {X[1],Y[1]},      {X[3],Y[1]},
                {X[0],Y[2]},    {X[2],Y[2]},  {X[4],Y[2]},
                        {X[1],Y[3]},      {X[3],Y[3]},
                                {X[2],Y[4]},
            };
            //   0
            //  1 2
            // 3 4 5
            //  6 7
            //   8
            triangle[0].position = points[4];
            triangle[1].position = points[0];
            triangle[2].position = points[2];
            
            triangle[3].position = points[4];
            triangle[4].position = points[2];
            triangle[5].position = points[5];
    
            triangle[6].position = points[4];
            triangle[7].position = points[5];
            triangle[8].position = points[7];
        
            triangle[9].position = points[4];
            triangle[10].position = points[7];
            triangle[11].position = points[8];
            
            triangle[12].position = points[4];
            triangle[13].position = points[8];
            triangle[14].position = points[6];
            
            triangle[15].position = points[4];
            triangle[16].position = points[6];
            triangle[17].position = points[3];
            
            triangle[18].position = points[4];
            triangle[19].position = points[3];
            triangle[20].position = points[1];
            
            triangle[21].position = points[4];
            triangle[22].position = points[1];
            triangle[23].position = points[0];
    }
}

void array::draw(sf::RenderTarget &target, sf::RenderStates state) const{
    target.draw(vertices);
}