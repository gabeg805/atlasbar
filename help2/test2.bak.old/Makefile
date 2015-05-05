CC      = g++
LIBS    = gtkmm-3.0 # gtk+-3.0 gdk-3.0
CFLAGS  = -g -Wall
CFLAGS += `pkg-config $(LIBS) --cflags --libs`

PROGRAM = atlas
NAMES   = $(PROGRAM) # bat date bright tags vol wifi util Statusbar
# NAMES   = $(PROGRAM) bat date bright tags vol wifi util Statusbar
SOURCES = $(addprefix ./src/, $(addsuffix .cpp, $(NAMES)))
HEADERS = $(addprefix ./hdr/, $(addsuffix .h, $(NAMES)))
OBJECTS = $(addprefix ./obj/, $(addsuffix .o, $(NAMES)))

all: $(PROGRAM)

./obj/%.o: ./src/%.cpp
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
