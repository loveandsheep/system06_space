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
	fd = open("/dev/spidev0.0", O_RDWR);
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
	uint8_t tx[8] = {byte[0]};
	uint8_t rx[8];
	uint16_t delay;
#ifndef TARGET_OSX
	struct spi_ioc_transfer tr;
	
	tr.tx_buf = (unsigned long)tx;
	tr.rx_buf = (unsigned long)rx;
	tr.len = 1;
	tr.delay_usecs = delay;
	tr.speed_hz = spi_speed;
	tr.bits_per_word = spi_bits;
	
	int ret;
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	
	if (ret < 1) cout << "spi send failed" << endl;
	
	*byte = rx[0];
#endif
}

void spiSender::exit()
{
	close(fd);
}