#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	room.setup(5, 1);
}

//--------------------------------------------------------------
void ofApp::update()
{
	
	if (ofGetFrameNum() % 60 == 0)
	{
		
		room.sendSpi_single(0, 0x04, 0);
		room.sendSpi_single(0, 0x00, 0);

		room.sendSpi_single(0, 0x04, 1);
		room.sendSpi_single(0, 0xFF, 1);

		room.sendSpi_single(0, 0x04, 2);
		room.sendSpi_single(0, 0xFF, 2);
	}

	if (ofGetFrameNum() % 60 == 20)
	{
		room.sendSpi_single(0, 0x04, 0);
		room.sendSpi_single(0, 0xFF, 0);

		room.sendSpi_single(0, 0x04, 1);
		room.sendSpi_single(0, 0x00, 1);

		room.sendSpi_single(0, 0x04, 2);
		room.sendSpi_single(0, 0x00, 2);
	}
//
//	if (ofGetFrameNum() % 60 == 40)
//	{
//		room.sendSpi_single(0, 0x04, 0);
//		room.sendSpi_single(0, 0xFF, 0);
//
//		room.sendSpi_single(0, 0x04, 1);
//		room.sendSpi_single(0, 0xFF, 1);
//
//		room.sendSpi_single(0, 0x04, 2);
//		room.sendSpi_single(0, 0x00, 2);
//	}
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
