FLAGS = -g -Wall -pedantic
LIBRARYDIR = src/libbrightness/
INCLUDEDIR = include/
BINDIR = bin/
LIBRARY = libbrightness
LIBRARYSRC = $(LIBRARYDIR)$(LIBRARY).c
LIBRARYCMP = $(LIBRARY).a
APPLET = brightness-qt
APPLETSRC = src/brightness-qt.cpp src/brightness.cpp
OBJECTS = $(PROJECT).o

all: $(OBJECTS) $(LIBRARYCMP) $(APPLET)

$(OBJECTS): $(LIBRARYSRC)
	gcc $(FLAGS) -c -o $(OBJECTS) $(LIBRARYSRC)

$(LIBRARYCMP): $(OBJECTS)
	ar rcs $(LIBRARYCMP) $(OBJECTS)

$(APPLET): $(APPLETSRC)
	g++ $(FLAGS) `pkg-config --cflags --libs Qt5Widgets` -fPIC $(APPLETSRC) -o $(APPLET) -ludev -L. -lbrightness

clean:
	rm -r $(OBJECTS)

remove: clean
	rm -r $(LIBRARYCMP)
	rm -r $(APPLET)
