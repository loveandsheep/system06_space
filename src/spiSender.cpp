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
	fd = open(spi_device, O_RDWR);
	if (fd < 0) cout << "spi initialize failed. " << endl;
	int ret;
	
#ifndef TARGET_OSX
	ret = ioctl(fd, SPI_IOC_WR_MODE, &spi_mode);
	if (ret == -1)
		pabort("can't set spi mode");
	
	ret = ioctl(fd, SPI_IOC_RD_MODE, &spi_mode);
	if (ret == -1)
		pabort("can't get spi mode");
	
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits);
	if (ret == -1)
		pabort("can't set bits per word");
	
	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bits);
	if (ret == -1)
		pabort("can't get bits per word");
	
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
	if (ret == -1)
		pabort("can't set max speed hz");
	
	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
	if (ret == -1)
		pabort("can't get max speed hz");
#endif
}

void spiSender::transfer(unsigned char *byte)
{
	uint8_t rx;
	uint16_t delay;
#ifndef TARGET_OSX
	struct spi_ioc_transfer tr = {
		.tx_buf = (*byte),
		.rx_buf = &rx,
		.len = 1,
		.delay_usecs = delay;
		.speed_hz = spi_speed,
		.bits_per_word = spi_bits,
	};
	
	int ret;
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1) cout << "spi send failed" << endl;
	
	byte = rx;
#endif
}

void spiSender::exit()
{
	close(fd);
}