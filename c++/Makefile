## Compiler
CC      = g++
LIBS    = gtkmm-3.0
CFLAGS  = -g -Wall -O0 -std=c++11
CFLAGS += `pkg-config $(LIBS) --cflags --libs`
CINC    =

## Program source files
PROGRAM = atlas
APP     = AtlasUserApp
COMMON  = AtlasCommand AtlasConfig
CORE    = $(PROGRAM) Statusbar AtlasApple AtlasAppGeneric AtlasEvent
NAMES   = $(APP) $(COMMON) $(CORE)

## Directories used
APP_DIR    = ./src/app
COMMON_DIR = ./src/common
CORE_DIR   = ./src/core
SRC_DIR = src
INC_DIR = include
OBJ_DIR = ./obj

## Determine source and object files
APP_SRC    = $(addprefix $(APP_DIR)/$(SRC_DIR)/,    $(addsuffix .cc, $(APP)))
COMMON_SRC = $(addprefix $(COMMON_DIR)/$(SRC_DIR)/, $(addsuffix .cc, $(COMMON)))
CORE_SRC   = $(addprefix $(CORE_DIR)/$(SRC_DIR)/,   $(addsuffix .cc, $(CORE)))
OBJ        = $(addprefix $(OBJ_DIR)/,               $(addsuffix .o,  $(NAMES)))

## Update compiler include flags
CINC += -I $(APP_DIR)/$(INC_DIR)
CINC += -I $(COMMON_DIR)/$(INC_DIR)
CINC += -I $(CORE_DIR)/$(INC_DIR)

## Makefile actions
all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) \
		-o $(PROGRAM) $(OBJ) \
		$(CINC)

$(OBJ_DIR)/%.o: $(APP_DIR)/$(SRC_DIR)/%.cc
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@ \
		$(CINC)

$(OBJ_DIR)/%.o: $(COMMON_DIR)/$(SRC_DIR)/%.cc
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@ \
		$(CINC)

$(OBJ_DIR)/%.o: $(CORE_DIR)/$(SRC_DIR)/%.cc
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@ \
		$(CINC)

.PHONY: clean
clean : 
	@rm -v -f $(OBJ)
	@rm -v -f $(PROGRAM)
