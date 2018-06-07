PREFIX = /usr

build:
	gcc -Wall -O2 mpdummy.c -lpthread -o mpdummy

install:
	install -m 0755 mpdummy $(PREFIX)/bin

test: build
	./test.sh
