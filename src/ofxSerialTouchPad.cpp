// ofxSerialTouchPad
// an openframeworks addon to receive input from custom touch sensors
//
// author: enrico<naus3a>viola
// 2015
// MIT licence

#include "ofxSerialTouchPad.h"

ofxSerialTouchPad::ofxSerialTouchPad(){
    curPort = "";
    bConnected = false;
    bEnabled = false;
    bSomeoneListening = false;
    tryAutoConnect();
}

ofxSerialTouchPad::~ofxSerialTouchPad(){
    disconnect();
}

void ofxSerialTouchPad::tryAutoConnect(){
    vector<ofSerialDeviceInfo> dd = lookForArduino();
    if(dd.size()>0){
        connect(dd[0].getDeviceName());
    }
}

vector<ofSerialDeviceInfo> ofxSerialTouchPad::getAvailableDevices(){
    return serial.getDeviceList();
}

vector<ofSerialDeviceInfo> ofxSerialTouchPad::lookForArduino(){
    //assuming you did an arduino based touch sensor, I'll look for something looking like an arduino
    vector<ofSerialDeviceInfo> canditates;
    string dn;
#ifdef TARGET_WIN32
    dn = "COM";
#elif defined(TARGET_OSX)
    dn = "tty.usbmodem";
#elif defined(TARGET_LINUX)
    dn = "ttyUSB";
#elif defined(TARGET_IPHONE)
    cout << "ofxSerialTouchPad has no mobile support"<< endl;
    return candidates;
#elif defined(TARGET_ANDROID)
    cout << "ofxSerialTouchPad has no mobile support"<< endl;
    return candidates;
#endif
    vector<ofSerialDeviceInfo> dd = getAvailableDevices();
    for(int i=0;i<dd.size();i++){
        if(ofStringTimesInString(dd[i].getDeviceName(), "tty.usbmodem")>0)
            canditates.push_back(dd[i]);
        
    }
    cout << "ofxSerialTouchPad: "<<canditates.size()<<" device candidates found"<<endl;
    return canditates;
}

bool ofxSerialTouchPad::isConnected(){
    return serial.isInitialized();
}

void ofxSerialTouchPad::disconnect(){
    if(isConnected()){
        curPort = "";
        serial.close();
        bConnected = false;
        cout<<"ofxSerialTouchPah: connection closed"<<endl;;
    }
}

void ofxSerialTouchPad::connect(string port){
    if(isConnected())disconnect();
    serial.setup(port, 9600);
    if(isConnected()){
        curPort = port;
        bConnected = true;
        cout<<"ofxSerialTouchPah: connected to "<<port<<endl;
    }
}

void ofxSerialTouchPad::enable(){
    if(!isEnabled()){
        ofAddListener(ofEvents().update, this, &ofxSerialTouchPad::update);
        bEnabled = true;
    }
}

void ofxSerialTouchPad::disable(){
    if(isEnabled()){
        ofRemoveListener(ofEvents().update, this, &ofxSerialTouchPad::update);
        bEnabled = false;
    }
}

void ofxSerialTouchPad::update(ofEventArgs &args){
    if(bConnected){
        int nPkts = serial.available();
        if(nPkts>0){
            unsigned char pkts[nPkts];
            serial.readBytes(pkts, nPkts);
            for(int i=0;i<nPkts;i++){
                decodePacket(pkts[i]);
            }
        }
    }
}

void ofxSerialTouchPad::decodePacket(unsigned char _pkt){
    //Serial protocol:
    // pin: 6bits (63)
    //[P][P][P][P][P][P][S][S]
    //                   state: 2bits (3 possibilities)
    
    unsigned int bitPin = (_pkt>>2);
    unsigned int bitSta = _pkt - (bitPin<<2);
    int pin = (int)(bitPin);
    ofxSerialTouchPad::TouchState ts = (ofxSerialTouchPad::TouchState)(bitSta);
    switch (ts) {
        case ofxSerialTouchPad::TOUCH_DOWN:
            ofNotifyEvent(evTouchDown, pin);
            break;
        case ofxSerialTouchPad::TOUCH_UP:
            ofNotifyEvent(evTouchUp, pin);
            break;
            
        default:
            break;
    }
}