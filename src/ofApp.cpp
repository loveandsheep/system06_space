#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	room.setup(5, 1);
	
	spiSender::init();
}

//--------------------------------------------------------------
void ofApp::update()
{
	
	if (ofGetFrameNum() % 60 == 0)
	{
		spiSender::trTest();
		
//		unsigned char bt = 154;
//		room.setSSPin(0, true);
//		usleep(5000);
//		spiSender::transfer(&bt);
//		room.setSSPin(0, false);
//
//		cout << "signal :" << int(bt) << endl;

		int i = 0;

		room.sendSpi_single(0, 0x04, i);
		room.sendSpi_single(0, 0xFF, i);

		usleep(10000);
		room.sendSpi_single(0, 0x02, i);

		usleep(300000);
		room.sendSpi_single(0, 0x03, i);
		
		usleep(10000);
		room.sendSpi_single(0, 0x04, i);
		room.sendSpi_single(0, 0x00, i);

		
		cout << "out :" << i << endl;
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
