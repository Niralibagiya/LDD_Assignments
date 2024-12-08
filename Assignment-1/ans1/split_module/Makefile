
obj-m = split.o
split-objs = init.o exit.o

split.ko: init.c exit.c
	make -C /lib/modules/$$(uname -r)/build M=$$(pwd) modules

clean:
	make -C /lib/modules/$$(uname -r)/build M=$$(pwd) clean

.PHONY: clean