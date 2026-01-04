all:
	gcc jtime.c -o jtime -lncurses

install:
	install -m 755 jtime /usr/local/bin/jtime

clean:
	rm -f jtime
