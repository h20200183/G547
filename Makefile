obj-m += adxl.o
#obj-m += adxl34x.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o usrapp userapp.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
