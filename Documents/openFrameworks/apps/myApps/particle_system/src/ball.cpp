//
//  ball.cpp
//  particle_system
//
//  Created by Joselyn McDonald  on 2/20/14.
//
//

#include "ball.h"


Ball::Ball(){
    
    //color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    
    xPos = ofRandom(ofGetWindowWidth());
    
    yPos = ofRandom( ofGetWindowHeight() );
    
    speedX = ofRandom(-1, 1);           // and random speed and direction
    speedY = ofRandom(-1, 1);
    
}

void Ball:: moveTo(){
   
    if(xPos < 0 ){
        xPos = 0;
        speedX *= -1;
    } else if(xPos > ofGetWidth()){
        xPos = ofGetWidth();
        speedX *= -1;
    }
    
    if(yPos < 0 ){
        yPos = 0;
        speedY *= -1;
    } else if(yPos > ofGetHeight()){
        yPos = ofGetHeight();
        speedY *= -1;
    }
    
    xPos+=speedX;
    yPos+=speedY;
    
    if (speedX == 0){
        speedX = .5; 
        
    }
    
    if (speedY == 0){
        speedY = .5;
        
    }
}
    

void Ball::draw() {
    
    //ofFill();
    //ofSetColor(ofRandom(200), ofRandom(0), ofRandom(200));

    ofCircle( xPos, yPos, 30);
   

}



