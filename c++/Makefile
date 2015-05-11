## Compiler
CC      = g++
LIBS    = gtkmm-3.0
CFLAGS  = -g -Wall -O0 
CFLAGS += `pkg-config $(LIBS) --cflags --libs`

## Program source files
PROGRAM = atlas
NAMES   = $(PROGRAM) 
NAMES  += Config Statusbar 
NAMES  += Battery Wifi Volume Brightness Date Workspace 

## File extensions used
SRC_EXT = .cc
HDR_EXT = .h
OBJ_EXT = .o

## Directories used
SRC_DIR = ./src
HDR_DIR = ./hdr
OBJ_DIR = ./obj

## Add extension to file names
SRC = $(addprefix $(SRC_DIR)/, $(addsuffix $(SRC_EXT), $(NAMES)))
HDR = $(addprefix $(HDR_DIR)/, $(addsuffix $(HDR_EXT), $(NAMES)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix $(OBJ_EXT), $(NAMES)))

## Makefile actions
all: $(PROGRAM)

$(OBJ_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(SRC_EXT)
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@

$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) \
		-o $(PROGRAM) $(OBJ)

.PHONY: clean
clean : 
	@rm -v -f $(OBJ)
	@rm -v -f $(OBJ_DIR)/*
	@rm -v -f $(PROGRAM)
