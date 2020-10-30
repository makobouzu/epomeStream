#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "Contents.hpp"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void render();

    void keyPressed(int key);
        
private:
    const int Width  = 1600;
    const int Height = 960;
    const int W = 4;
    const int H = 4;

    const int posTotal = 16;
    float pos = 0;
    
    ofEasyCam cam;
    const int camDis  = 1230;
    float camDeg;
    const float camPos = -233;
    
    ofFbo fbo;
    ofTexture tex;
    ofPixels pix;
    ofImage img;
    
    //Lighting
    ofLight frontLight;
    ofLight backLight;
    glm::vec3 frontLightPos = {0,500,1000};
    glm::vec3 backLightPos  = {0,-500,1000};
    
    float rotateX = 0;
    float rotateY = 35.26;
    float rotateZ = 45;
    
    const float positionX = 0;
    const float positionY = 7.34;
    const float positionZ = 4;

    contents::Contents contents;
    
    //Gui
    ofxImGui::Gui gui;
    bool window;

};
