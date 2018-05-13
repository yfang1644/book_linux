##########################################
# Makefile (!not makefile)
#ifneq ($(KERNELRELEASE),)
MODULE_NAME := gpio
#$(MODULE_NAME)-y = main.o read.o
obj-m       := $(MODULE_NAME).o
#else
KDIR        := /home/beagle/linux-4.4
PWD         := `pwd`
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
#endif

