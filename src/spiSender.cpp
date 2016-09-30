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

void spiSender::trTest()
{
	int ret;
	uint16_t delay = 0;
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

#ifndef TARGET_OSX
	
	struct spi_ioc_transfer tr;
	
	memset(&tr, 0, sizeof(tr));
	tr.tx_buf = (unsigned long)tx;
	tr.rx_buf = (unsigned long)rx;
	tr.len = ARRAY_SIZE(tx);
	tr.delay_usecs = delay;
	tr.speed_hz = spi_speed;
	tr.bits_per_word = spi_bits;

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		cout << "can't send spi message" << endl;
	
	cout << "spi :" << spi_speed << endl;
	cout << "bits:" << spi_bits << endl;
	
	for (ret = 0; ret < ARRAY_SIZE(tx); ret++) {
		if (!(ret % 6))
			puts("");
		printf("%.2X ", rx[ret]);
	}
	puts("");
#endif
}

void spiSender::transfer(unsigned char *byte)
{
	uint8_t tx[1] = {byte[0]};
	uint8_t rx[1];
	uint16_t delay = 0;
#ifndef TARGET_OSX
	struct spi_ioc_transfer tr;
	
	memset(&tr, 0, sizeof(tr));
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