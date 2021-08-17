obj-m     := char_driver3.o
KERNELDIR := /lib/modules/$(shell uname -r)/build	
PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
		
