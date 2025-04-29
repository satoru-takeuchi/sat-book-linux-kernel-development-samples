obj-m := timer-remaining-msecs.o
obj-m += timer-remaining-msecs-dir.o
obj-m += timer-remaining-msecs-dir-rw.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
