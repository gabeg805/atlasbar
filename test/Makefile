CC      = gcc
LIBS    = gtk+-3.0 gdk-3.0
CFLAGS  = -g -Wall -lX11
CFLAGS += `pkg-config $(LIBS) --cflags --libs`

PROGRAM = atlas
# NAMES   = $(PROGRAM) frame bat bright date tags vol wifi util 
NAMES   = $(PROGRAM) bat date bright tags vol wifi util 
SOURCES = $(addprefix ./src/, $(addsuffix .c, $(NAMES)))
HEADERS = $(addprefix ./hdr/, $(addsuffix .h, $(NAMES)))
OBJECTS = $(addprefix ./obj/, $(addsuffix .o, $(NAMES)))

all: $(PROGRAM)

./obj/%.o: ./src/%.c 
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
