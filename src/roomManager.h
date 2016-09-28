//
//  roomManager.h
//  system06_space
//
//  Created by Ovis aries on 2016/09/25.
//
//

#ifndef roomManager_h
#define roomManager_h

#include "ofMain.h"
#include "ofxWiringPi.h"

#define SSPIN_A 8
#define SSPIN_B 10
#define SSPIN_C 10
#define SSPIN_D 10
#define SSPIN_E 10

class rmUnit{
public:
	
	void pop();
	
	int curAnalog;
	bool ballStat;
};

class roomManager{
public:
	
	void setup(int row, int column);
	
	void update();
	void draw();
	
	int getNumRow();
	int getNumColumn();
	rmUnit const & getUnit(int row, int column);
	
	vector <vector<rmUnit> > units;
	
	void sendSpi_single(int ss, unsigned char dat, int num);
	
	void sendSpi_chain(int ss, unsigned char* bytes, int num);
	void inputSpi_chain(int ss, unsigned char* dst, int num);
	
	void setSSPin(int num, bool val);
};

#endif /* roomManager_h */
