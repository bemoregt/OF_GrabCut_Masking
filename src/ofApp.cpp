#include "ofApp.h"

using namespace ofxCv;
using namespace cv;
using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowTitle("Grab Mask");

    //set to Image size
    ww = 512;
    hh = 512;
    
    ofSetWindowShape(ww, hh);
    
    ofSetBackgroundColor(90);
    
    // Load the image
    image.load("/Users/user1/Documents/0309_graphCut/NG(99)(449) (1).png");
    
    // Set the initial values for the bounding box
    startX = 0;
    startY = 0;
    endX = 0;
    endY = 0;
    dragging = false;

    // Initialize overlay
    overlay.allocate(ww, hh, OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw the original image
    ofSetColor(255);
    image.draw(0, 0, ww, hh);
    
    // Draw the overlay
    ofSetColor(255, 255, 255, 128);  // Semi-transparent white
    overlay.draw(0, 0, ww, hh);
    
    // Draw the bounding box
    ofSetColor(255,0,0);
    ofNoFill();
    ofDrawRectangle(startX, startY, endX - startX, endY - startY);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // When the mouse is pressed, set the start point of the bounding box
    startX = x;
    startY = y;
    dragging = true;
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
    // When the mouse is dragged, update the end point of the bounding box
    if (dragging) {
        endX = x;
        endY = y;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    // GrabCut
    cv::Rect bbox(startX, startY, abs(endX-startX), abs(endY-startY));
    ofLog() << "bbox = " <<bbox;
    
    cv::Mat src = toCv(image);
    cv::Mat mask = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    cv::Mat bgModel, fgModel;
    
    unsigned int iteration = 9;
    
    cv::grabCut(src, mask, bbox, bgModel, fgModel, iteration, GC_INIT_WITH_RECT);
    cv::Mat mask2 = (mask == 1) + (mask == 3);
    
    cv::Mat dest;
    src.copyTo(dest, mask2);
    
    // Convert the result to ofImage
    ofImage result;
    toOf(dest, result);
    result.update();
    
    // Create overlay
    overlay.setFromPixels(result.getPixels());
    for(int y = 0; y < overlay.getHeight(); y++) {
        for(int x = 0; x < overlay.getWidth(); x++) {
            ofColor c = overlay.getColor(x, y);
            if(c.a > 0) {
                c.a = 128;  // Set alpha to 128 for semi-transparency
            }
            overlay.setColor(x, y, c);
        }
    }
    overlay.update();
    
    // Save the result
    result.save("seg_mask.jpg");
 
    // When the mouse is released, stop dragging
    dragging = false;
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    if( dragInfo.files.size() > 0 ){
        image.load(dragInfo.files[0]);
        image.setImageType(OF_IMAGE_COLOR);
    }
    ww = image.getWidth();
    hh = image.getHeight();
    ofSetWindowShape(ww, hh);
    
    // Reset the overlay
    overlay.allocate(ww, hh, OF_IMAGE_COLOR_ALPHA);
    overlay.clear();
    
    // Set the initial values for the bounding box
    startX = 0;
    startY = 0;
    endX = 0;
    endY = 0;
    dragging = false;
}