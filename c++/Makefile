# Compiler
CC      = g++
LIBS    = gtkmm-3.0
CFLAGS  = -g -Wall -O0 -std=c++11
CFLAGS += `pkg-config $(LIBS) --cflags --libs`
# CINC (c-include) defined below

# Program source files
PROGRAM = atlas

# Directories used
CORE_DIR     = .
USR_DIR      = $(CORE_DIR)/usr
OBJ_DIR      = $(CORE_DIR)/obj
USR_SRC_DIR  = $(USR_DIR)/src
USR_INC_DIR  = $(USR_DIR)/include
CORE_SRC_DIR = $(CORE_DIR)/src
CORE_INC_DIR = $(CORE_DIR)/include

# Determine source and object files
USR_SRC  = $(wildcard $(USR_SRC_DIR)/*.cc)
CORE_SRC = $(wildcard $(CORE_SRC_DIR)/*.cc)
SRC      = $(USR_SRC) $(CORE_SRC)
OBJ      = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cc=.o)))

# Compiler include flags
CINC = -I $(USR_INC_DIR) -I $(CORE_INC_DIR)

# Makefile actions
all: $(PROGRAM)

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

.PHONY: clean
clean : 
	@rm -v -f $(OBJ)
	@rm -v -f $(PROGRAM)
