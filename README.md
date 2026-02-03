## USB-driver for linux systeam

device driver build and tested on 6.14.0-37-generic kernel version.

### How to compile ?

### Requirements
```
sudo apt get make
sudo apt-get install linux-headers-$(uname -r)
sudo apt install build-essential
sudo apt install gcc-13
sudo apt install g++-13
```
### 1. Build using make
make

### 2. insert kernel object file into systeam
sudo insmod usb_driver.ko

### 3. check dmesg for kernel logs
sudo dmesg

### 4. for removing module use following command
sudo rmmod usb_driver

### 5. check which usb driver is being used
lsusb -t
