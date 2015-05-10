CC      = g++
LIBS    = gtkmm-3.0
CFLAGS  = -g -Wall -O0 
CFLAGS += `pkg-config $(LIBS) --cflags --libs`

PROGRAM = atlas
NAMES   = $(PROGRAM) 
NAMES  += Config Statusbar StatusSimple StatusMulti StatusWatcher 
NAMES  += Battery Wifi Volume Brightness Date Workspace 
# NAMES  += StatusWidget 
SOURCES = $(addprefix ./src/, $(addsuffix .cc, $(NAMES)))
OBJECTS = $(addprefix ./obj/, $(addsuffix .o, $(NAMES)))
HEADERS = $(addprefix ./hdr/, $(addsuffix .h, $(NAMES)))

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
