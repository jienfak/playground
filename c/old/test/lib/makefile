# Compiler and program name
TARGET          = target
LIB             = lib
CC              = cc
SYS_LIB_DIR     = /usr/lib
INCLUDE_DIR     = include
PROGRAM_DIR     = bin/rls
LIB_DIR         = bin/lib
SRC_DIR         = src
LIB_SRC_DIR     = $(SRC_DIR)/lib
OBJ_DIR         = bin/obj
SRC_LIB_DIR     = src/lib
SRC_MODULES_DIR = src/modules

IN_EXT          = c
OUT_EXT         = o
INCLUDE_EXT     = h

INCLUDE_DIR_FLAG= -I
LIB_DIR_FLAG    = -L
LIB_NAMES_FLAG  = -l
LIB_CFLAGS      = -shared



LIB_EXT         = so
LIB_SUF         =
LIB_PRE         = lib


SRCS            = $(wildcard $(SRC_DIR)/*.$(IN_EXT))\
                  		$(wildcard $(SRC_MODULES_DIR)/*.$(IN_EXT))
OBJS            = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.$(IN_EXT)=.$(OUT_EXT))))
INCLUDES        = $(wildcard $(INCLUDE_DIR)/*.$(INCLUDE_EXT))

# Library things.
LIB_SRCS        = $(wildcard $(SRC_LIB_DIR)/*.$(IN_EXT))

LIB_OBJS        = $(addprefix $(OBJ_DIR)/, $(notdir $(LIB_SRCS:.$(IN_EXT)=.$(OUT_EXT))))
LIB_S_OBJ       = $(LIB_DIR)/$(LIB_PRE)$(LIB)$(LIB_SUF).$(LIB_EXT)

CFLAGS = $(LIB_NAMES_FLAG) $(LIB) $(LIB_DIR_FLAG) $(LIB_DIR) $(INCLUDE_DIR_FLAG) $(INCLUDE_DIR)

all:DBG $(TARGET)

install_libs:
	install $(LIB_DIR)/$(LIBS) $(SYS_LIB_DIR)/

lib:$(LIB_S_OBJ)

lib_objs:$(LIB_OBJS)

objs:$(OBJS)

DBG:
	@echo Program sources      - \'$(SRCS)\'
	@echo Program object files - \'$(OBJS)\'
	@echo Library sources      - \'$(LIB_SRCS)\'
	@echo Library object files - \'$(LIB_OBJS)\'
	@echo Library shared object files - \'$(LIB_S_OBJ)\'
	@echo Libraries = \'$(LIB)\'

$(TARGET): $(OBJS)  $(LIB_S_OBJ)
	@echo "Making target...[$(TARGET)]"
	$(CC) $(CFLAGS) $(OBJS)  -o $(TARGET)

# Compiling to object file.
$(OBJ_DIR)/%.o : $(LIB_SRC_DIR)%.c
	$(CC) $(CFLAGS) -c  $< -o $@



# Make of just object file shared thing.
$(LIB_S_OBJ): $(LIB_OBJS)
	@echo "Making shared library object...[$(LIB_S_OBJ)]"
	$(CC) $(LIB_CFLAGS) $(LIB_OBJS) -o $(LIB_S_OBJ)

#$(LIB_OBJS): $(LIB_SRCS)
#	@echo "Making library object...[]"
#	$(CC) -c $< -o $@

#$(LIB_S_OBJS):
#	$(CC) $(LIB_CFLAGS) $< -o $(LIB_DIR)/$(notdir $@)
#.$(OUT_EXT).$(LIB_EXT):
#$(CC) $(LIB_CFLAGS) $(OBJ_DIR)/$< -o $(LIB_DIR)/$@

