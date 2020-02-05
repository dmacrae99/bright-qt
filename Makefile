FLAGS = -g -Wall -pedantic
LIBRARYDIR = src/libbacklight/
LIBRARY = libbacklight
LIBRARYSRC = $(LIBRARYDIR)$(LIBRARY).c
LIBRARYCMP = lib/$(LIBRARY).a
OBJECTS = build/$(LIBRARY).o
APP = sbacklight
APPSRC = src/$(APP).c

all: $(OBJECTS) $(LIBRARYCMP) $(APP) install

$(OBJECTS): $(LIBRARYSRC)
	gcc $(FLAGS) -c -o $(OBJECTS) $(LIBRARYSRC)

$(LIBRARYCMP): $(OBJECTS)
	ar rcs $(LIBRARYCMP) $(OBJECTS)

$(APP): $(APPSRC)
	gcc $(APPSRC) $(FLAGS) -o bin/sbacklight -Llib -lbacklight -ludev

install: 
	@echo "Root access is needed to move the udev rule and executable"
	@sudo cp 90-backlight.rules /etc/udev/rules.d/90-backlight.rules
	@sudo cp bin/sbacklight /usr/bin/sbacklight
	@echo "Successfully installed sbacklight: To use type 'sbacklight -h'"

clean: 
	rm -r $(OBJECTS)
	rm -r build
	rm -r bin
	rm -r lib

folders:
	mkdir build
	mkdir bin
	mkdir lib
