/* gpio.h
 */

#ifndef _GPIO_H
#define _GPIO_H

#include <linux/ioctl.h>

typedef struct gpio {
    volatile unsigned int *port;
    volatile unsigned int *ctrl;
} gpio_t;

#define GPIO0   0x48E07000
#define GPIO1   0x4804c000
#define GPIO2   0x481AC000
#define GPIO3   0x481AE000

#define	OE		(0x134/4)
#define	DATIN	(0x138/4)
#define DATOUT	(0x13c/4)
#define	CLR     (0x190/4)
#define SET     (0x194/4)

#define CONTRL	0x44e10000
#define AD12    (0x830/4)
#define AD13    (0x834/4)

#define	DEVICE_NAME		"/dev/gpio_led"

#define		LEDIOSET	_IOW(221, 0, int)
#define		LEDIOGET	_IOR(221, 0, int)

#endif      /* _GPIO_H */
