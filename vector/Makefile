# Executable
NAME := a.out

# Directories
SDIR := src
ODIR := obj
DDIR := dep
IDIR := includes
LDIR := libs

ifeq ($(shell uname),Darwin)
	DEBUG_SYM = *.dSYM
endif

# FOR CATCH
CATCH_DEFINE = CATCH_TEST_ENABLED
STD_VECTOR_TEST_DEFINE = STD_VECTOR_TESTS

BREWIDIR := $(HOME)/.brew/include
ifdef DEBUG
	ifdef $(STD_VECTOR_TEST_DEFINE)
		NAME := catch_build_std.exe
		ODIR := obj/test_obj2
		DDIR := dep/test_obj2
	else
		NAME := catch_build.exe
		ODIR := obj/test_obj
		DDIR := dep/test_obj
	endif
endif

# Files
SRC := $(shell find $(SDIR) -name "*.cpp" -type f)
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))
DEP := $(patsubst $(SDIR)/%.cpp,$(DDIR)/%.d,$(SRC))
HDF := $(shell find $(IDIR) -name "*.hpp" -type f)

# Compilation
CXX = clang++
IFLAGS = -I$(IDIR) -I./$(IDIR)/reimplemented
LFLAGS =
CXXFLAGS = -Wall -Wextra -Werror

# Optional Flags
UNUSED_FLAGS := -Wno-unused -Wno-unused-parameter
SANITIZER_FLAGS := -fsanitize=address
CXXFLAGS += $(UNUSED_FLAGS) -g3
# CXXFLAGS += $(SANITIZER_FLAGS)


ifeq ($(shell uname -s),Linux)
	DFLAGS := -O0 -g -fsanitize=address -fsanitize=leak
else
	IFLAGS += -I$(BREWIDIR)
	DFLAGS := -O0 -g -fsanitize=address
endif

ifdef DEBUG
	CXXFLAGS += -std=c++11 -pedantic -g3 -D$(CATCH_DEFINE) 
	ifdef $(STD_VECTOR_TEST_DEFINE)
		CXXFLAGS += -D$(STD_VECTOR_TEST_DEFINE)
	endif
else
	CXXFLAGS += -std=c++98 -pedantic
endif


RM = /bin/rm -f

# Rules
.PHONY: all
all: $(NAME)

# Compilation
$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(CXXFLAGS) $(LFLAGS)
$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(IFLAGS)
$(DDIR)/%.d: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $< -MM -MF $@ -MT $(ODIR)/$*.o $(IFLAGS)

obj/test_obj/catch_tests.o: includes/vector.hpp

# Cleanup
.PHONY: clean fclean re cleanall
clean:
	$(RM) -r $(ODIR)
	$(RM) -r $(DDIR)
ifndef DEBUG
fclean:
	$(MAKE) fclean DEBUG=1
	$(MAKE) fclean DEBUG=1 $(STD_VECTOR_TEST_DEFINE)=1
	$(MAKE) clean
	$(RM) $(NAME)
else
fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(DEBUG_SYM)
endif
re: fclean
	$(MAKE) all

# Debug
.PHONY: catch
catch:
	$(MAKE) all DEBUG=1
catch_std:
	$(MAKE) all DEBUG=1 $(STD_VECTOR_TEST_DEFINE)=1

-include $(DEP)
