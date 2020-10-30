#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofHideCursor();
    ofSetFrameRate(60);
    ofRectMode(OF_RECTMODE_CENTER);
    
    //Gui
    gui.setup();
    window = false;

    ofEnableDepthTest();
    cam.setDistance(camDis);
    cam.setFov(10.0f);
    fbo.allocate(Width/W, Height/H); //(400, 240)
    ofSetBackgroundAuto(false);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    pos = 0;
    ofClear(50);
    contents.update();
    rotateX++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    //draw
    for(int i = 0; i <= posTotal; i++){
        
        fbo.begin();
        ofBackground(0);
        
        camDeg = 360/posTotal*int(pos);
        cam.orbitDeg(0,camDeg,camDis,{camPos,0,0});
        const float degree = -10.0;
        const glm::vec3 vec = {0.0,cos(camDeg*PI/180),sin(camDeg*PI/180)};
        cam.rotate(degree, vec);
        
        cam.begin();
        
        //Lighting
        frontLight.setAmbientColor(ofFloatColor(0.1));
        frontLight.setPosition(frontLightPos);
        frontLight.enable();
        
        backLight.setAmbientColor(ofFloatColor(0.1));
        backLight.setPosition(backLightPos);
        backLight.enable();
        
        //Contents Draw
        ofPushMatrix();
        ofRotateDeg(rotateX, 1, 0, 0);
        ofRotateDeg(rotateY, 0, 1, 0);
        ofRotateDeg(rotateZ, 0, 0, 1);
        ofTranslate(positionX,positionY,positionZ);
        contents.draw();
        ofPopMatrix();
        
        frontLight.disable();
        backLight.disable();
        
        cam.end();
        fbo.end();
        
        //image render
        render();
        
        pos++;
    }
    
    gui.begin();
    if(window){
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Once);
        ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiSetCond_Once);
        ImGui::Begin("Gui", &window);
        ImGui::SliderFloat("frontLightX", &frontLightPos.x, -1500, 1500);
        ImGui::SliderFloat("frontLightY", &frontLightPos.y, -500, 500);
        ImGui::SliderFloat("frontLightZ", &frontLightPos.z, -1000, 1000);
        ImGui::SliderFloat("backLightX",  &backLightPos.x, -1500, 1500);
        ImGui::SliderFloat("backLightY",  &backLightPos.y, -500, 500);
        ImGui::SliderFloat("backLightZ",  &backLightPos.z, -1000, 1000);
        ImGui::SliderFloat("rotateX", &rotateX, 0, 180);
        ImGui::SliderFloat("rotateY", &rotateY, 0, 180);
        ImGui::SliderFloat("rotateZ", &rotateZ, 0, 180);
        
        ImGui::End();
    }
    gui.end();
    
}

void ofApp::render(){
    fbo.readToPixels(pix);
    img.setFromPixels(pix);
    
    ofSetColor(1000);
    if(pos < H){
        img.draw(0, (H-1-int(pos))*Height/H, Width/W , Height/H);
    }else if(H <= pos && pos < 2*H){
        img.draw(Width/W, (H-1-int(pos)%H)*Height/H, Width/W , Height/H);
    }else if(2*H <= pos && pos < 3*H){
        img.draw(2*Width/W, (H-1-int(pos)%H)*Height/H, Width/W , Height/H);
    }else if(3*H <= pos && pos < 4*H){
        img.draw(3*Width/W, (H-1-int(pos)%H)*Height/H, Width/W , Height/H);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'z'){
        window = !window;
    }
}
