//
//  spiSender.cpp
//  system06_space
//
//  Created by Ovis aries on 2016/09/28.
//
//

#include "spiSender.h"

void spiSender::init()
{
	fd = open("/dev/spidev1.1", O_RDWR);
	if (fd < 0) cout << "spi initialize failed. " << endl;
	int ret;
	
#ifndef TARGET_OSX
	ret = ioctl(fd, SPI_IOC_WR_MODE, &spi_mode);
	
	ret = ioctl(fd, SPI_IOC_RD_MODE, &spi_mode);
	
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits);
	
	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bits);
	
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
	
	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
#endif
}

void spiSender::transfer(unsigned char *byte)
{
//	uint8_t rx;
	uint16_t delay;
#ifndef TARGET_OSX
	struct spi_ioc_transfer tr;
	
	uint8_t tx[] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
		0xF0, 0x0D,
	};
	uint8_t rx[ARRAY_SIZE(tx)] = {0, };
	
	tr.tx_buf = (unsigned long)tx;
	tr.rx_buf = (unsigned long)rx;
	tr.len = ARRAY_SIZE(tx);
	tr.delay_usecs = delay;
	tr.speed_hz = spi_speed;
	tr.bits_per_word = spi_bits;
	
	int ret;
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1) cout << "spi send failed" << endl;
	
//	*byte = rx;
#endif
}

void spiSender::exit()
{
	close(fd);
}