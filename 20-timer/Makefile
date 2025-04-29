obj-m := oneshot-timer.o
# obj-m += buggy-oneshot-timer.o
obj-m += periodic-timer.o
obj-m += multiple-timers.o
# obj-m := old-oneshot-timer.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
