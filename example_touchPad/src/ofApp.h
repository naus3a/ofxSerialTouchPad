#pragma once

#include "ofMain.h"
#include "ofxSerialTouchPad.h"

class Pad : public ofRectangle{
public:
    inline Pad(float _x, float _y, float _w, float _h, ofColor _col){
        set(_x,_y,_w,_h);
        color = _col;
        active=false;
    }
    inline void draw(){
        if(active){
            ofPushStyle();
            ofSetColor(color);
            ofRect(x,y,width,height);
            ofPopStyle();
        }
    }
    ofColor color;
    bool active;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        void onTouchDown(int & pin);
        void onTouchUp(int & pin);
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

    ofxSerialTouchPad touch;
	vector<Pad> pads;
};


