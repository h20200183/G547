Download the main.c sample.txt and Makefile

Go to directory and use make command

use sudo insmod main.ko to load the module

check if module is loaded using lsmod command

Check the partition info using the command fdisk -l /dev/dof

2 partitions should be displayed

Use command "sudo dd if=sample.txt of=/dev/dof count=1" to copy the contents of sample.txt file into the disk.

to write into disk use cat > /dev/dof press enter
type something
pres ctrl+d to exit

to read back from the disk on command line use command xxd /dev/dof| less

To check MBR details use the command sudo hd -n 512 /dev/dof

remove the module using sudo rmmod main.ko

