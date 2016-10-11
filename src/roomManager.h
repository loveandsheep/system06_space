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
#include "spiSender.h"
#include "ofxOsc.h"

#ifndef TARGET_OSX
#include <wiringPi.h>
#endif

class rmUnit{
public:
	int		curAnalog;
	int		onCount;
	bool	ballStat;
};

class roomManager{
public:
	
	int analog_thr = 10;
	
	//ROW...SPIで接続されたユニット(短辺)
	//column...デイジーチェーンのユニット

	void setup(int row, int column);
	
	void popManage();
	void update();
	void draw();
	
	void bang(int row, int column);

	void close();
	int getNumRow();
	int getNumColumn();
	rmUnit const & getUnit(int row, int column);
	
	
	vector <vector<rmUnit> > units;
	
	void sendSpi_single(int ss, unsigned char dat, int num);
	void sendSpi_chain (int ss, unsigned char* bytes, int num);
	void inputSpi_chain(int ss, unsigned char* dst, int num);
	
	void setSSPin(int num, bool val);

	ofxOscReceiver receiver;
	
	int currentMode = 0;
	
	int SSPIN_A = 5;
	int SSPIN_B = 6;
	int SSPIN_C = 19;
	int SSPIN_D = 13;
	int SSPIN_E = 26;
	
	static const int MODE_STAY		= 0;
	static const int MODE_REGULAR	= 1;
	static const int MODE_MANUAL	= 2;
	static const int MODE_TEST		= 3;
};

#endif /* roomManager_h */
