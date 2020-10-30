//
//  Contents.hpp
//  epomeStreame_amako
//
//  Created by Makoto Amano on 2020/09/30.
//

#ifndef Contents_hpp
#define Contents_hpp

#include <stdio.h>
#include "ofxColorMorph.h"
#include "ofGraphics.h"
#include "of3dGraphics.h"

using namespace ofx::colorMorph::morph;
using vec_col = std::deque<std::pair<glm::vec3, ofColor>>;

namespace contents{
class Contents{
public:
    Contents();
    void update();
    void draw();
    void createVertex(std::vector<glm::vec3> vec, std::vector<ofColor> col);
    std::vector<ofColor> morph(std::vector<ofColor> col1, std::vector<ofColor> col2, int typeNum);
    void generate(vec_col vertex, int typeNum);
    
    int getRange(){return range;};
    int getSplit(){return split;};
    
    vec_col colorPalette;
    
private:
    const float range = 8.5;//size
    const int split = 15;
    const int minX  = -1*range*split/2.;
    const int minY  = -1*range*split/2.;
    const int minZ  = -1*range*split/2.;
    const int maxX  = minX+range*split;
    const int maxY  = minY+range*split;
    const int maxZ  = minZ+range*split;
    
    std::vector<glm::vec3> pos_{
        glm::vec3{minX, minY, minZ},
        glm::vec3{maxX, minY, minZ},
        glm::vec3{minX, maxY, minZ},
        glm::vec3{maxX, maxY, minZ},
        glm::vec3{minX, minY, maxZ},
        glm::vec3{maxX, minY, maxZ},
        glm::vec3{minX, maxY, maxZ},
        glm::vec3{maxX, maxY, maxZ}
    };
    std::vector<ofColor> offsetCol{
        ofColor{  0, 208,  29},
        ofColor{  0, 250, 255},
        ofColor{232,  12,  34},
        ofColor{188, 255,  46},
        ofColor{ 40,   0, 255},
        ofColor{231,   0,  13},
        ofColor{ 56, 160, 131},
        ofColor{212,   0, 255}
    };
    
    std::vector<ofColor> destinationCol{
        ofColor{188, 255,  46},
        ofColor{188, 255,  46},
        ofColor{188, 255,  46},
        ofColor{188, 255,  46},
        ofColor{188, 255,  46},
        ofColor{188, 255,  46},
        ofColor{188, 255,  46},
        ofColor{188, 255,  46}
    };
    
    std::vector<ofColor> buf;
    vec_col vertex;
    
    std::vector<std::string> types;
    int typeNum = 8;
    
    int t = 0;
    bool reverse = false;
    glm::vec3 count = {1,0,0};
};

};//namespace contents

#endif /* Contents_hpp */
