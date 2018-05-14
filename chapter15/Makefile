CC  	= arm-linux-gcc

all: alsa_play alsa_record

# /home/beagle/target 是 alsa-lib 的安装目录

CFLAGS = -I/home/beagle/target/usr/include
LDFLAGS = -L/home/beagle/target/usr/lib -lasound

%: %.c
	$(CC) -o $@ $< $(CFLAGS)  $(LDFLAGS) -lm
