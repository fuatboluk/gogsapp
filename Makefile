all: gogsapp

gogsapp: gogsapp.c
	gcc `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0` -o gogsapp $^

.PHONY: clean

clean:
	rm -f gogsapp

install:
	mkdir -p /opt/GogsApp
	mv -f gogsapp /opt/GogsApp
	cp -f gogs-logo.png /opt/GogsApp
	cp -f gogsapp.desktop /usr/share/applications
