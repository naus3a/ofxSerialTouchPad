// ofxSerialTouchPad
// an openframeworks addon to receive input from custom touch sensors
//
// author: enrico<naus3a>viola
// 2015
// MIT licence

#pragma once
#include "ofMain.h"

class ofxSerialTouchPad{
public:
    enum TouchState{
        TOUCH_DOWN,
        TOUCH_UP,
        TOUCH_HELD
    };
    
    ofxSerialTouchPad();
    ~ofxSerialTouchPad();
    vector<ofSerialDeviceInfo> lookForArduino();
    vector<ofSerialDeviceInfo> getAvailableDevices();
    bool isConnected();
    inline bool isEnabled(){return bEnabled;}
    void disconnect();
    void connect(string port);
    void tryAutoConnect();
    
    template<class TClass, typename TMethodDown, typename TMethodUp>
    void registerTouchEvents(TClass * listenerClass, TMethodDown methodDown, TMethodUp methodUp){
        if(!bSomeoneListening){
            ofAddListener(evTouchDown, listenerClass, methodDown);
            ofAddListener(evTouchUp, listenerClass, methodUp);
            bSomeoneListening = true;
        }
    }
    
    template<class TClass, typename TMethodDown, typename TMethodUp>
    void unregisterTouchEvents(TClass * listenerClass, TMethodDown methodDown, TMethodUp methodUp){
        if(bSomeoneListening){
            ofRemoveListener(evTouchDown, listenerClass, methodDown);
            ofRemoveListener(evTouchUp, listenerClass, methodUp);
            bSomeoneListening = false;
        }
    }
    
    void enable();
    void disable();
    void update(ofEventArgs & args);
    
    void decodePacket(unsigned char _pkt);
    
protected:
    ofEvent<int> evTouchDown;
    ofEvent<int> evTouchUp;
    ofSerial serial;
    string curPort;
    bool bConnected;
    bool bEnabled;
    bool bSomeoneListening;
};