# Executable
NAME := a.out


# Directories
SDIR := src
ODIR := obj
DDIR := dep
IDIR := includes
LDIR := libs

BREWIDIR := $(HOME)/.brew/include
ifdef DEBUG
	NAME := catch_build
	ODIR := test_obj
endif

# Files
SRC := $(shell find $(SDIR) -name "*.cpp" -type f)
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))
DEP := $(patsubst $(SDIR)/%.cpp,$(DDIR)/%.d,$(SRC))
HDF := $(shell find $(IDIR) -name "*.hpp" -type f)

# Compilation
CC = clang++
IFLAGS = -I$(IDIR)
LFLAGS =
CFLAGS = -Wall -Wextra -Werror -Wno-unused -Wno-unused-parameter

ifeq ($(shell uname -s),Linux)
	DFLAGS := -O0 -g -fsanitize=address -fsanitize=leak
else
	IFLAGS += -I$(BREWIDIR)
	DFLAGS := -O0 -g -fsanitize=address
endif

ifdef DEBUG
	CFLAGS += -std=c++11 -pedantic -g3 -DDEBUG=1
else
	CFLAGS += -std=c++98 -pedantic -g3
endif


RM = /bin/rm -f

# Rules
.PHONY: all
all: $(NAME)

# Compilation
$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LFLAGS)
$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)
$(DDIR)/%.d: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CC) $< -MM -MF $@ -MT $(ODIR)/$*.o $(IFLAGS)

# Cleanup
.PHONY: clean fclean re cleanall
clean:
	$(RM) -r $(ODIR)
	$(RM) -r $(DDIR)
ifndef DEBUG
fclean: clean
	$(MAKE) fclean DEBUG=1
	$(RM) $(NAME)
else
fclean: clean
	$(RM) $(NAME)
endif
re: fclean
	$(MAKE) all

# Debug
.PHONY: catch
catch:
	$(MAKE) all DEBUG=1

-include $(DEP)
