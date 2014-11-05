#include "testApp.h"

//--------------------------------------------------------------
ofMesh testApp::pixelManipulate(ofImage imageA, ofMesh meshA, float intensityThreshold, float sketchDepth){
    
    
    imageA.resize(200, 200);
    
    //create mesh with points as the primitive
    //meshA.setMode(OF_PRIMITIVE_POINTS);
    
    //create a mesh with lines
    meshA.setMode(OF_PRIMITIVE_TRIANGLES);
    
    //meshA.setMode(OF_PRIMITIVE_LINE_STRIP);
    
    int w = imageA.getWidth();
    
    int h = imageA.getHeight();
    
    //loop through each pixel in the image using image width & height
    for (int x=0; x<w; x++){
        for(int y=0; y<h; y++){
            
            //create the color object at that pixel
            //ofColor c = imageA.getColor(x, y);
            
            ofColor c = imageA.getColor(x, y);
            
            
            //check the intensity of the pixel's color
            float intensity = c.getLightness();
            
            //if the intensity exceeds the threshold, create a vertex at the location of the pixel
            //& color it with the pixel's color
            if (intensity >= intensityThreshold){
                
                //pushes brighter colors in the positive z direction
                //pushes whiter colors in the negative z direction
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -sketchDepth, sketchDepth);
                
                //the image is now 1/4 the size of the OF window, so multiply
                //the pixel location by 4 so that the mesh covers the OF window
                ofVec3f pos(5*x, 4*y, z);
                meshA.addVertex(pos);
                meshA.addColor(c);
            }
        }
    }
    
    return meshA;
}

//--------------------------------------------------------------
void testApp::setup(){
    
    //-----------------sound-----------------------
    soundStream.listDevices();
    int bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter= 0;
    drawCounter= 0;
    smoothedVol     = 0.0;
    scaledVol= 0.0;
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    //-----------------sound-----------------------
    
    //-------------------mesh----------------------------
    imageOne.loadImage("pink_geo_gem_only.png");
    //-------------------background----------------------------
    
    imageBack.loadImage("pink_geo_gem_only.png");
    
    // interaction sound
    
    music.loadSound("sounds/synth.wav");
    music.setVolume(0.75f);
    music.setMultiPlay(false);
    
    
    
    
    ofBackground(0);
    
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    //-----------------sound-----------------------
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 500.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    //-----------------sound-----------------------
    
    
}

//-------------------------------------------------------------
void testApp::draw(){
    
    
    //ofSetColor(255, 255, 255, 255);
    imageBack.draw(300, 0, 460, 717);
    
    
    //-----------------sound-----------------------
    
    easyCam.begin();
    ofPushMatrix();
    
    ofTranslate(-ofGetWidth()/2,  -ofGetHeight()/2);
    
    //real one ofTranslate(-ofGetWidth()/2,  -ofGetHeight()/2);
    
    meshOne = pixelManipulate(imageOne, meshPassOne,  10, scaledVol);
    meshOne.draw();
    
    
    ofPopMatrix();
    easyCam.end();
    //-------------------mesh----------------------------
    
    ofTriangle(0, 0, 10,0, 5, 10);
    
    //-----circle class
    
}
//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]= input[i*2]*0.5;
        right[i]= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
    
    //cout<< scaledVol << endl;
    
    //this is where I added a vector series
    scaledVolume.push_back(scaledVol);
    
    cout<< scaledVolume[200] << endl;
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if( key == 's' ){
        soundStream.start();
    }
    
    if( key == 'e' ){
        soundStream.stop();
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    if (x > ofGetWidth()/4 && x < ofGetWidth()-200 && y > ofGetHeight()/4 && y < ofGetHeight()-200){
        
        music.play();
        music.setSpeed( 0.1f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*5.5);
		music.setPan(ofMap(x, 0, ofGetWidth(), -1, 1, true));
        
    }
    
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


