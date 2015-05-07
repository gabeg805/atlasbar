CC      = g++
LIBS    = gtkmm-3.0
CFLAGS  = -g -Wall -O0 
CFLAGS += `pkg-config $(LIBS) --cflags --libs`

PROGRAM = atlas
NAMES  = $(PROGRAM) StatusBar StatusWatcher StatusItem StatusMulti Battery Wifi Volume Brightness Date Workspace 
SOURCES = $(addprefix ./src/, $(addsuffix .cc, $(NAMES)))
HEADERS = $(addprefix ./hdr/, $(addsuffix .hpp, $(NAMES)))
OBJECTS = $(addprefix ./obj/, $(addsuffix .o, $(NAMES)))

all: $(PROGRAM)

./obj/%.o: ./src/%.cc
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) \
		-o $(PROGRAM) $(OBJECTS)

.PHONY: clean
clean : 
	@rm -v -f $(OBJECTS)
	@rm -v -f $(PROGRAM)
