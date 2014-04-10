#all:
#	avr-g++ main.cc robotio.cc -o main.elf -Os -DF_CPU=8000000 -mmcu=atmega644
#	avr-objcopy -O ihex main.elf main.hex
#	sudo avrdude -P usb -c avrisp2 -p atmega644 -U flash:w:main.hex
#
build:
	avr-g++ main.cc -o main.elf -Os -DF_CPU=8000000 -mmcu=attiny85

convert: build
	avr-objcopy -O ihex main.elf main.hex

install: build convert
	avrdude -P usb -c avrisp2 -p attiny85 -U flash:w:main.hex
