//
//  spiSender.h
//  system06_space
//
//  Created by Ovis aries on 2016/09/28.
//
//

#ifndef spiSender_h
#define spiSender_h

#include "ofMain.h"

#ifndef TARGET_OSX
	#include <getopt.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <linux/types.h>
	#include <linux/spi/spidev.h>
#endif


static char *spi_device = "/dev/spidev1.1";
static int fd;
static uint8_t spi_mode = 0;
static uint8_t spi_bits = 8;
static uint32_t spi_speed = 500000;

class spiSender
{
public:
	static void init();
	static void transfer(unsigned char* byte);
	static void exit();
};


#endif /* spiSender_h */
