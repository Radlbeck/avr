all: install

build:
	avr-g++ main.cc -o main.elf -Os -DF_CPU=1200000 -mmcu=attiny85

convert: build
	avr-objcopy -O ihex main.elf main.hex

install: build convert
	avrdude -P usb -c avrisp2 -p attiny85 -U flash:w:main.hex
