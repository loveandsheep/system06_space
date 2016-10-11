
//
//  roomManager.cpp
//  system06_space
//
//  Created by Ovis aries on 2016/09/25.
//
//

#include "roomManager.h"

void roomManager::setup(int row, int column)
{
	for (int i = 0;i < row;i++)
	{
		vector<rmUnit> un;
		for (int j = 0;j < column;j++)
		{
			un.push_back(rmUnit());
		}
		units.push_back(un);
	}

	spiSender::init();
	
	if (row == 3 && column == 3)
	{
		swap(SSPIN_B, SSPIN_D);
	}

#ifndef TARGET_OSX
	int speed = 50000;
	
	if (wiringPiSetupGpio() == -1)
	{
		printf("GPIO ERROR! \n");
	}
	pinMode(SSPIN_A, OUTPUT);
	pinMode(SSPIN_B, OUTPUT);
	pinMode(SSPIN_C, OUTPUT);
	pinMode(SSPIN_D, OUTPUT);
	pinMode(SSPIN_E, OUTPUT);
#endif

	for (int i = 0;i < getNumRow();i++)
	{
		for (int j = 0;j < getNumColumn();j++)
		{
			unsigned char sig[getNumColumn()];

			for (int o = 0;o < getNumColumn();o++) sig[o] = 0x04;
			sendSpi_chain(i, sig, getNumColumn());

			for (int o = 0;o < getNumColumn();o++) sig[o] = 0xFF;
			sendSpi_chain(i, sig, getNumColumn());

			for (int o = 0;o < getNumColumn();o++) sig[o] = 0x03;
			sendSpi_chain(i, sig, getNumColumn());
		}
	}

	receiver.setup(12400);
	
	currentMode = MODE_TEST;
}

void roomManager::close()
{
	for (int i = 0;i < getNumRow();i++)
	{
		for (int j = 0;j < getNumColumn();j++)
		{
			unsigned char sig[getNumColumn()];
			
			for (int o = 0;o < getNumColumn();o++) sig[o] = 0x04;
			sendSpi_chain(i, sig, getNumColumn());
			
			for (int o = 0;o < getNumColumn();o++) sig[o] = 0xFF;
			sendSpi_chain(i, sig, getNumColumn());
			
			for (int o = 0;o < getNumColumn();o++) sig[o] = 0x03;
			sendSpi_chain(i, sig, getNumColumn());
		}
	}
}

void roomManager::popManage()
{
	
}

void roomManager::update()
{
	
	while (receiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		receiver.getNextMessage(m);
		
		if (m.getAddress() == "/bang")
			bang(m.getArgAsInt(0), m.getArgAsInt(1));
		
		if (m.getAddress() == "/mode")
			currentMode = m.getArgAsInt(0);
	}
	
	if (currentMode == MODE_STAY)
	{
		for (int i = 0;i < getNumRow();i++)
		{
			for (int j = 0;j < getNumColumn();j++)
			{
				unsigned char sig[getNumColumn()];
				
				for (int o = 0;o < getNumColumn();o++) sig[o] = 0x04;
				sendSpi_chain(i, sig, getNumColumn());
				
				for (int o = 0;o < getNumColumn();o++) sig[o] = 0xFF;
				sendSpi_chain(i, sig, getNumColumn());
				
				for (int o = 0;o < getNumColumn();o++) sig[o] = 0x03;
				sendSpi_chain(i, sig, getNumColumn());
			}
		}
	}
	if (currentMode == MODE_REGULAR)
	{
		popManage();
	}
	if (currentMode == MODE_MANUAL)
	{
		
	}
	if (currentMode == MODE_TEST)
	{
		//analog status update
		for (int i = 0;i < getNumRow();i++)
		{
			unsigned char sig[getNumColumn()];
			
			for (int o = 0;o < getNumColumn();o++) sig[o] = 0x01;
			
			sendSpi_chain (i, sig, getNumColumn());
			inputSpi_chain(i, sig, getNumColumn());
			
			for (int j = 0;j < getNumColumn();j++)
			{
				unsigned char val = sig[j];
				if ((val != 128) && (val != 129))
					units[i][j].curAnalog = val;
				
				if (units[i][j].curAnalog > analog_thr)
				{
					units[i][j].ballStat = true;
					sendSpi_single(i, 0x04, j);
					sendSpi_single(i, 0x34, j);
				}
				
			}
		}

		static int step = 3;
		if (ofGetFrameNum() % step == 0)
		{
			static int cnt = 0;
			cnt++;
			int r = cnt % getNumRow();
			int c = cnt / getNumRow() % getNumColumn();
			
			if (units[r][c].curAnalog > analog_thr)
			{
				bang(r, c);
			}
		}
	}
	


}

void roomManager::draw()
{
	for (int i = 0;i < getNumRow();i++)
	{
		for (int j = 0;j < getNumColumn();j++)
		{
			ofDrawCircle(i * 50, j * 50, 15);
		}
	}
}

void roomManager::bang(int row, int column)
{
	sendSpi_single(row, 0x04, column);
	sendSpi_single(row, 0x20, column);
	
	sendSpi_single(row, 0x02, column);
	usleep(3000);
	sendSpi_single(row, 0x03, column);

	sendSpi_single(row, 0x04, column);
	sendSpi_single(row, 0xFF, column);
}

int roomManager::getNumRow()
{
	return units.size();
}

int roomManager::getNumColumn()
{
	return units[0].size();
}

rmUnit const & roomManager::getUnit(int row, int column)
{
	return units[row][column];
}

void roomManager::sendSpi_single(int ss, unsigned char dat, int num)
{
	unsigned char bts[getNumColumn()];
	for (int i = 0;i < getNumColumn();i++)
	{
		bts[i] = (i == num ? dat : 0x00);
	}

	sendSpi_chain(ss, bts, getNumColumn());
}

void roomManager::sendSpi_chain(int ss, unsigned char* bytes, int num)
{
	usleep(500);
	setSSPin(ss, true);
	usleep(1000);
	for (int i = 0;i < num;i++)
	{
		spiSender::transfer(&bytes[i]);
	}
	usleep(1000);
	setSSPin(ss, false);
	usleep(500);
}

void roomManager::inputSpi_chain(int ss, unsigned char *dst, int num)
{
	usleep(500);
	setSSPin(ss, true);
	usleep(1000);
	for (int i = 0;i < num;i++)
	{
		dst[i] = 0x00;
		spiSender::transfer(&dst[i]);
	}
	usleep(1000);
	setSSPin(ss, false);
	usleep(500);
}

void roomManager::setSSPin(int num, bool val)
{
	int pins[] = {SSPIN_A, SSPIN_B, SSPIN_C, SSPIN_D, SSPIN_E};
#ifndef TARGET_OSX
	digitalWrite(pins[num], val);
#endif
}