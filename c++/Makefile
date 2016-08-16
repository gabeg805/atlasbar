# Compiler
CC        = g++
LIBS      = gtkmm-3.0
CFLAGS    = -g -Wall -O0
CPPFLAGS  = $(CFLAGS) -std=c++11 `pkg-config $(LIBS) --cflags --libs`

# Program source files
PROGRAM     = atlas
MEMMAP_FILE = /dev/shm/atlas-shm
LOG_FILE    = /tmp/atlas.log

# Directories used
ROOT_DIR = .
OBJ_DIR  = $(ROOT_DIR)/obj
SRC_DIR  = $(ROOT_DIR)/src
INC_DIR  = $(ROOT_DIR)/include

# Determine source and object files
CSRC   = $(wildcard $(SRC_DIR)/*.c)
CPPSRC = $(wildcard $(SRC_DIR)/*.cc)
COBJ   = $(addprefix $(OBJ_DIR)/, $(notdir $(CSRC:.c=.o)))
CPPOBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(CPPSRC:.cc=.o)))
OBJ    = $(COBJ) $(CPPOBJ)

# Compiler include flags
CINC = -I $(INC_DIR) -lX11

# Makefile actions
all: $(PROGRAM)
	@rm -v -f $(MEMMAP_FILE)
	@rm -v -f $(LOG_FILE)

$(PROGRAM): $(OBJ)
	$(CC) $(CPPFLAGS) \
		-o $(PROGRAM) $(OBJ) \
		$(CINC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) \
		-c $< \
		-o $@ \
		$(CINC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) \
		-c $< \
		-o $@ \
		$(CINC)

.PHONY: clean
clean: 
	@rm -v -f $(OBJ_DIR)/*.o
	@rm -v -f $(PROGRAM)
	@rm -v -f $(MEMMAP_FILE)
	@rm -v -f $(LOG_FILE)
