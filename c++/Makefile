# Compiler
CC      = g++
LIBS    = gtkmm-3.0
CFLAGS  = -g -Wall -O0 -std=c++11
CFLAGS += `pkg-config $(LIBS) --cflags --libs`
# CINC (c-include) defined below

# Program source files
PROGRAM     = atlas
MEMMAP_FILE = /tmp/atlasmap

# Directories used
CORE_DIR      = .
USR_DIR       = $(CORE_DIR)/usr
EXTRA_DIR     = $(CORE_DIR)/extra
OBJ_DIR       = $(CORE_DIR)/obj
USR_SRC_DIR   = $(USR_DIR)/src
USR_INC_DIR   = $(USR_DIR)/include
CORE_SRC_DIR  = $(CORE_DIR)/src
CORE_INC_DIR  = $(CORE_DIR)/include
EXTRA_SRC_DIR = $(EXTRA_DIR)/src
EXTRA_INC_DIR = $(EXTRA_DIR)/include

# Determine source and object files
USR_SRC   = $(wildcard $(USR_SRC_DIR)/*.cc)
CORE_SRC  = $(wildcard $(CORE_SRC_DIR)/*.cc)
SRC       = $(USR_SRC) $(CORE_SRC)
EXTRA_OBJ = $(OBJ_DIR)/atlasipc.o
OBJ       = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cc=.o))) $(EXTRA_OBJ)

# Compiler include flags
CINC = -I $(USR_INC_DIR) -I $(CORE_INC_DIR) -I $(EXTRA_INC_DIR)
EXTRA_CINC = $(CINC) -I X11

# Makefile actions
all: $(PROGRAM)
	@rm -v -f $(MEMMAP_FILE)

$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) \
		-o $(PROGRAM) $(OBJ) \
		$(CINC)

$(OBJ_DIR)/%.o: $(USR_SRC_DIR)/%.cc
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@ \
		$(CINC)

$(OBJ_DIR)/%.o: $(CORE_SRC_DIR)/%.cc
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@ \
		$(CINC)

$(OBJ_DIR)/%.o: $(EXTRA_SRC_DIR)/%.c
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@ \
		$(EXTRA_CINC)

.PHONY: clean ipc
clean: 
	@rm -v -f $(OBJ_DIR)/*.o
	@rm -v -f $(PROGRAM)

ipc: $(EXTRA_OBJ)
