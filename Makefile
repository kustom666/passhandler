CC=clang
CCFLAGS=-O2 -std=c++11
LDFLAGS=-lssl -lcrypto -lstdc++

all: passwordhandler

passwordhandler:
	 ${CC} -o bin/passhandler src/passhandler.cc `pkg-config gtkmm-3.0 --cflags --libs` ${CCFLAGS} ${LDFLAGS}
