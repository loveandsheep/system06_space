
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

#ifndef TARGET_OSX
	int speed = 500000;
	
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
	unsigned char bts[getNumRow()];
	for (int i = 0;i < getNumRow();i++)
	{
		bts[i] = (i == num ? dat : 0x00);
	}

	sendSpi_chain(ss, bts, getNumRow());
}

void roomManager::sendSpi_chain(int ss, unsigned char* bytes, int num)
{
	setSSPin(ss, true);
	usleep(5000);
	for (int i = 0;i < num;i++)
	{
		usleep(1000);
		spiSender::transfer(&bytes[i]);
	}
	setSSPin(ss, false);
	usleep(5000);
}

void roomManager::inputSpi_chain(int ss, unsigned char *dst, int num)
{
	setSSPin(ss, true);
	usleep(1000);
	for (int i = 0;i < num;i++)
	{
		dst[i] = 0x00;
		spiSender::transfer(&dst[i]);
	}
	usleep(1000);
	setSSPin(ss, false);
	usleep(5000);
}

void roomManager::setSSPin(int num, bool val)
{
	int pins[] = {SSPIN_A, SSPIN_B, SSPIN_C, SSPIN_D, SSPIN_E};
#ifndef TARGET_OSX
	digitalWrite(pins[num], val);
#endif
}