UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Linux)
PORT = $(shell ls /dev/ttyUSB*)
endif

ifeq ($(UNAME_S),Darwin)
PORT = $(shell ls /dev/tty.usbserial-*)
endif

build:
	idf.py build

flash:
	idf.py -p $(PORT) flash

monitor:
	idf.py -p $(PORT) monitor

config:
	idf.py menuconfig

size:
	idf.py size

size-components:
	idf.py size-components

size-files:
	idf.py size-files

flash_and_monitor:
	idf.py -p $(PORT) flash monitor

clean:
	$(RM) -r build/ sdkconfig

re: clean build

compiledb: build
	cp build/compile_commands.json .

cppcheck:
	cppcheck --quiet --enable=warning,style,performance,portability main components

.PHONY: build flash monitor flash_monitor config size size-components size-files clean re compiledb cppcheck
