PREFIX = /usr
CFLAGS = -Wall -O2

build: commands_empty.c
	gcc $(CFLAGS) mpdummy.c -lpthread -o mpdummy

commands_empty.c:
	gperf -m 100 commands_empty.gperf.c > commands_empty.c

install:
	install -m 0755 mpdummy $(PREFIX)/bin

test: build
	./test.sh
