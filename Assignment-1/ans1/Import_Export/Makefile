
obj-m = impexp.o
split-objs = import.o export.o

split.ko: import.c export.c
	make -C /lib/modules/$$(uname -r)/build M=$$(pwd) modules

clean:
	make -C /lib/modules/$$(uname -r)/build M=$$(pwd) clean

.PHONY: clean
