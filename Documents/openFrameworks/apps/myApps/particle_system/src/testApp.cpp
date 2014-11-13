#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofEnableSmoothing(); // smoothes edges
    
    ofSetFrameRate(30);
    
    
    image.loadImage("images.jpg"); 
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    for(int i=0; i<numBalls; i++){
        
        theBall[i].moveTo();
    }
    
    // We calculate the x and y distance
    // of the ball to the mouse position and
    // add a little portion of it to the x and y
    // variables

}

//--------------------------------------------------------------
void testApp::draw(){
    
    //ofBackgroundGradient(ofColor::gray,ofColor(30, 10, 30), OF_GRADIENT_CIRCULAR);
    ofNoFill();
    image.draw(0,0, ofGetWidth()+300, ofGetHeight());
    //ofSetColor(200,200,125);
    //ofFill();
    
    for(int i=0; i<numBalls; i++){
        
        theBall[i].draw();
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    


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
