//
//  Contents.cpp
//  epomeStreame_amako
//
//  Created by Makoto Amano on 2020/09/30.
//

#include "Contents.hpp"

namespace contents{

Contents::Contents(){
    createVertex(pos_, offsetCol);
    generate(vertex, typeNum);
    
    types = {"RGB", "HSL", "HSV", "HSB", "LUV", "LAB", "HunterLAB", "LCH", "CMY", "CMYK", "YXY", "XYZ"};
}

void Contents::update(){
    if(t == 5){
        buf = morph(offsetCol, destinationCol, typeNum);
        createVertex(pos_, buf);
        generate(vertex,typeNum);
        t = 0;
    }
    t++;
}

void Contents::draw(){
    
    ofPushMatrix();
    for(auto&& c : colorPalette){
        ofSetColor(c.second);
        ofDrawBox(c.first, range);
    }
    ofPopMatrix();
}

void Contents::createVertex(std::vector<glm::vec3> vec, std::vector<ofColor> col){
    vertex.clear();
    for(auto i = 0; i < vec.size(); ++i){
        vertex.push_back(std::make_pair(vec[i], col[i]));
    }
}

std::vector<ofColor> Contents::morph(std::vector<ofColor> col1, std::vector<ofColor> col2, int typeNum){
    std::vector<ofColor> output;
    glm::vec3 col1Pos = {0,0,0};
    glm::vec3 col2Pos = {300,0,0};
    for(auto i = 0; i < col1.size(); ++i){
        glm::vec3 pos = count;
        ofColor col = colorMorph(pos, col1Pos, col1[i], col2Pos, col2[i], static_cast<type>(typeNum));
        output.push_back(col);
    }
    if(count.x == col2Pos.x){
        reverse = true;
    }else if(count.x == col1Pos.x){
        reverse = false;
    }
    
    if(reverse){
        if(count.x >= col2Pos.x/2){
            count.x -= 10;
        }else if(count.x >= col2Pos.x/3 && count.x < col2Pos.x/2){
            count.x -= 5;
        }else{
            count.x --;
        }
    }else{
        if(count.x >= col2Pos.x/2){
            count.x += 10;
        }else if(count.x >= col2Pos.x/3 && count.x < col2Pos.x/2){
            count.x += 5;
        }else{
            count.x ++;
        }
    }
    return output;
}

void Contents::generate(vec_col vertex, int typeNum){
    colorPalette.clear();
    
    for(auto i = 0; i < split; ++i){
        glm::vec3 pos1 = {minX+i*range, minY, minZ};
        ofColor   col1 = colorMorph(pos1, vertex[0].first, vertex[0].second, vertex[1].first, vertex[1].second, static_cast<type>(typeNum));
        glm::vec3 pos2 = {minX+i*range, maxY, minZ};
        ofColor   col2 = colorMorph(pos2, vertex[2].first, vertex[2].second, vertex[3].first, vertex[3].second, static_cast<type>(typeNum));
        
        glm::vec3 pos4 = {minX+i*range, minY, maxZ};
        ofColor   col4 = colorMorph(pos4, vertex[4].first, vertex[4].second, vertex[5].first, vertex[5].second, static_cast<type>(typeNum));
        glm::vec3 pos5 = {minX+i*range, maxY, maxZ};
        ofColor   col5 = colorMorph(pos5, vertex[6].first, vertex[6].second, vertex[7].first, vertex[7].second, static_cast<type>(typeNum));
        
        for(auto j = 0; j < split; ++j){
            glm::vec3 pos3 = {minX+i*range, minY+j*range, minZ};
            ofColor   col3 = colorMorph(pos3, pos1, col1, pos2, col2, static_cast<type>(typeNum));
            glm::vec3 pos6 = {minX+i*range, minY+j*range, maxZ};
            ofColor   col6 = colorMorph(pos6, pos4, col4, pos5, col5, static_cast<type>(typeNum));
            for(auto k = 0; k < split; ++k){
                glm::vec3 pos7 = {minX+i*range, minY+j*range, minZ+k*range};
                ofColor   col7 = colorMorph(pos7, pos3, col3, pos6, col6, static_cast<type>(typeNum));
                colorPalette.push_back(std::make_pair(pos7, col7));
            }
        }
    }
}

};//namespace contents
