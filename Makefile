CC=clang
CCFLAGS=-O2

all: passwordhandler

passwordhandler:
	 gcc `pkg-config --cflags gtk+-3.0` $CCFLAGS -o bin/passwordhandler src/passwordhandler.c `pkg-config --libs gtk+-3.0`
