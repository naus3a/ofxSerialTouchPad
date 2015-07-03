#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    touch.registerTouchEvents(this, &ofApp::onTouchDown, &ofApp::onTouchUp);
    touch.enable();
    
    int nPads = 12;
    float w = ofGetWidth()/nPads;
    float h = ofGetHeight();
    for(int i=0;i<nPads;i++){
        pads.push_back(Pad(i*w,0,w,h,ofColor(ofMap(i, 0, nPads, 100, 200))));
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i=0;i<pads.size();i++){
        pads[i].draw();
    }
}

void ofApp::onTouchDown(int &pin){
    pads[(int)(ofClamp(pin, 0, pads.size()))].active=true;
    cout<<"Pin "<<pin<<" down"<<endl;
}

void ofApp::onTouchUp(int &pin){
    pads[(int)(ofClamp(pin, 0, pads.size()))].active=false;
    cout<<"Pin "<<pin<<" up"<<endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
