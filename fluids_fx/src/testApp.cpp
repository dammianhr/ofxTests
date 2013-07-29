#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
  
    
    width = 1024;
    height = 768;

    // Initial Allocation
    //
    fluid.allocate(width, height, 0.5);
    
    // Seting the gravity set up & injecting the background image
    //
    fluid.dissipation = 0.99;
    fluid.velocityDissipation = 0.99;
    
    fluid.setGravity(ofVec2f(0.0,0.0));
//    fluid.setGravity(ofVec2f(0.0,0.0098));
    
    //  Set obstacle
    //
    fluid.begin();
    ofSetColor(255);
    ofCircle(width*0.5, height*0.35, 40);
    fluid.end();
    
    // Adding constant forces
    //
    fluid.addConstantForce(ofPoint(width*0.5,height*0.85), ofPoint(0,-2), ofFloatColor(0.5,0.1,0.0), 10.f);
    
    //ofSetWindowShape(width, height);
    
    tuioClient.start(3333);
    
    ofAddListener(tuioClient.cursorAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.cursorRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.cursorUpdated,this,&testApp::tuioUpdated);
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    tuioClient.getMessage();
    
    // Adding temporal Force
    //
    ofPoint m = ofPoint(mouseX,mouseY);
    ofPoint d = (m - oldM)*10.0;
    oldM = m;
    ofPoint c = ofPoint(640*0.5, 480*0.5) - m;
    c.normalize();
    fluid.addTemporalForce(m, d, ofFloatColor(c.x,c.y,0.5),3.0f);
    
    
    
    // TUIOcursors
    list<ofxTuioCursor*>cursorList = tuioClient.getTuioCursors();
    for(list<ofxTuioCursor*>::iterator it=cursorList.begin(); it != cursorList.end(); it++) {
        ofxTuioCursor *tcur = (*it);
        
        ofPoint loc = ofPoint(tcur->getX()*ofGetWidth(),tcur->getY()*ofGetHeight());
        
        ofPoint vel = ofPoint(tcur->getXSpeed() * tuioCursorSpeedMult,tcur->getYSpeed() * tuioCursorSpeedMult);
        if(vel.x == 0 && vel.y == 0) {
            vel.x = ofRandom(-tuioStationaryForce, tuioStationaryForce);
            vel.y = ofRandom(-tuioStationaryForce, tuioStationaryForce);
        }
        
        ofPoint d1 = (loc - oldLoc)*10.0;
        oldLoc = loc;
        
        ofPoint c1 = ofPoint(640*0.5, 480*0.5) - loc;
        c1.normalize();
        
        fluid.addTemporalForce(loc, d1, ofFloatColor(c1.x,c1.y,0.5),3.0f);
    }
    
    /*
    //TUIOobjects
    list<ofxTuioObject*>objectList = tuioClient.getTuioObjects();
    for(list<ofxTuioObject*>::iterator it=objectList.begin(); it != objectList.end(); it++) {
        ofxTuioObject *tobj = (*it);
        
        ofPoint loc = ofPoint(tobj->getX()*ofGetWidth(),tobj->getY()*ofGetHeight());
        
        ofPoint vel = ofPoint(tobj->getXSpeed() * tuioCursorSpeedMult,tobj->getYSpeed() * tuioCursorSpeedMult);
        if(vel.x == 0 && vel.y == 0) {
            vel.x = ofRandom(-tuioStationaryForce, tuioStationaryForce);
            vel.y = ofRandom(-tuioStationaryForce, tuioStationaryForce);
        }
        
        cout << "ObjRotation" << tobj->getAngleDegrees() << " add at " << loc << endl;
        
        float angForce = tobj->getAngleDegrees()/36;
        
        ofPoint d1 = (loc - oldLoc)*10.0;
        oldLoc = loc;
        
        ofPoint c1 = ofPoint(640*0.5, 480*0.5) - loc;
        c1.normalize();
        
        fluid.addTemporalForce(loc, d1, ofFloatColor(c1.x,c1.y,0.5),angForce);
    }
     */ 

    //  Update
    fluid.update();
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    tuioClient.drawCursors();
    tuioClient.drawObjects();
    
    fluid.draw();
}



void testApp::tuioAdded(ofxTuioCursor &tuioCursor){
	//ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	//cout << "Point n" << tuioCursor.getSessionId() << " add at " << loc << endl;
}

void testApp::tuioUpdated(ofxTuioCursor &tuioCursor){
    //ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
    //cout << "Point n" << tuioCursor.getSessionId() << " updated at " << loc << endl;
}

void testApp::tuioRemoved(ofxTuioCursor &tuioCursor){
	//ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	//cout << "Point n" << tuioCursor.getSessionId() << " remove at " << loc << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if( key == 'p')
        bPaint = !bPaint;
    if( key == 'o')
        bObstacle = !bObstacle;
    if( key == 'b')
        bBounding = !bBounding;
    if( key == 'c')
        bClear = !bClear;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}