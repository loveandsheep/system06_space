#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	int tgRow = 1;
	int tgColumn = 1;
	
	FILE *fp;
	char num[128];
	
	if ((fp = fopen(ofToDataPath("settings").c_str(), "r")) != NULL)
	{
		fgets(num, 128, fp);
		tgRow = ofToInt(num);
		fgets(num, 128, fp);
		tgColumn = ofToInt(num);
	}
	
	room.setup(tgRow, tgColumn);
}

//--------------------------------------------------------------
void ofApp::update()
{

	room.update();
	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(30);
	ofPushMatrix();
	ofTranslate(50, 50);
	room.draw();
	ofPopMatrix();
}

void ofApp::exit()
{
	cout << "called exit. " << endl;
	
	room.close();
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
