#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	spiSender::init();
	room.setup(5, 1);
}

//--------------------------------------------------------------
void ofApp::update()
{
	
	if (ofGetFrameNum() % 60 == 0)
	{
		unsigned char bts[] = {0x04, 0x00, 0x04, 0xFF};
		unsigned char bt = bts[(ofGetFrameNum() / 60) % 4];
		cout << "signal :" << int(bt) << endl;
		room.setSSPin(0, true);
		usleep(5000);
		spiSender::transfer(&bt);
		room.setSSPin(0, false);

	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofPushMatrix();
	ofTranslate(50, 50);
	room.draw();
	ofPopMatrix();
}

void ofApp::exit()
{
	cout << "called exit. " << endl;
	spiSender::exit();
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

}
