ARCH := x86_64
KBUILD_SRC := /lib/modules/$(shell uname -r)/build

obj-m = hello.o
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
