//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//


// Access from ARM Running Linux

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <bcm2835.h>
#include <unistd.h>

int read_gpio(int pin);

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Please select a valid GPIO pin #\n");
		return 2;
	}

	int dhtpin = atoi(argv[1]);
	if (dhtpin <= 0) {
		printf("Please select a valid GPIO pin #\n");
		return 3;
	}

	printf("Using pin #%d\n", dhtpin);

	if (!bcm2835_init())
		return 1;

	if (read_gpio(dhtpin) == 1) {
		printf("sound\n");
	} else {
		printf("no sound\n");
	}

	return 0;
}


int read_gpio(int pin) {
	int i;

	bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
	for (i=0; i<10; i++) {
		if (bcm2835_gpio_lev(pin) == 0) {
//			printf("sound\n");
			return 1;
		}
		usleep(100000);
	}
	return 0;
}

