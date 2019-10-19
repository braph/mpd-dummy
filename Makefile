PREFIX = /usr
CFLAGS = -Wall -Os

build: commands.c
	gcc $(CFLAGS) mpdummy.c -lpthread -o mpdummy
	strip mpdummy

commands.c:
	gperf -m 100 commands.gperf.c > commands.c

install:
	install -m 0755 mpdummy $(PREFIX)/bin

test: build
	./test.sh
