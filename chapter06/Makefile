# Makefile (!not makefile)
ifneq ($(KERNELRELEASE),)
MODULE_NAME := example
#$(MODULE_NAME)-y := example.o
obj-m := $(MODULE_NAME).o
else
KDIR := /lib/modules/`uname -r`/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
endif
