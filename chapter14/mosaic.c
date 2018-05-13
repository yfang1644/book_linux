#include "graphics.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define	BLOCKSIZE 32

#define  RES_X  800
#define  RES_Y  480

struct coord
{
	int x, y;
};

void *drawblock(void *param)
{
	struct coord *p = (struct coord*)param;
	int i, j, color;

	while(1) {
		color = rand();
		for(i = 0; i < BLOCKSIZE; i++)
			for(j = 0; j < BLOCKSIZE; j++)
				drawpixel(p->x + i, p->y + j, color);
		usleep((unsigned)rand()/500);
	}
}

int main (int argc, char *argv[])
{
	int fd = 0;
	int i, j, k, color = 0;
	pthread_t threadId;
	struct coord xy[500];

    fd = fb_init("/dev/fb0");

	k = 0;
	for(i = 0; i < RES_X; i += BLOCKSIZE) {
		for(j = 0; j < RES_Y; j += BLOCKSIZE) {
			xy[k].x = i;
			xy[k].y = j;
			pthread_create (&threadId, NULL, drawblock, &xy[k]);
			k++;
		}
	}
	sleep(5);
	close (fd);

	return 0;
}

