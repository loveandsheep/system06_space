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

#ifndef TARGET_OSX
#include <wiringPi.h>
#endif

#define SSPIN_A 5
#define SSPIN_B 6
#define SSPIN_C 13
#define SSPIN_D 19
#define SSPIN_E 26

class rmUnit{
public:
	
	void pop();
	
	int curAnalog;
	bool ballStat;
};

class roomManager{
public:
	
	//ROW...SPIで接続されたユニット(短辺)
	//column...デイジーチェーンのユニット
	constexpr static const int brokenCh[] = {0, 2, 3};

	void setup(int row, int column);
	
	void update();
	void draw();
	
	void bang(int row, int column);

	int getNumRow();
	int getNumColumn();
	rmUnit const & getUnit(int row, int column);
	
	
	vector <vector<rmUnit> > units;
	
	void sendSpi_single(int ss, unsigned char dat, int num);
	void sendSpi_chain (int ss, unsigned char* bytes, int num);
	void inputSpi_chain(int ss, unsigned char* dst, int num);
	
	void setSSPin(int num, bool val);
};

#endif /* roomManager_h */
