ifndef SETTINGS_MK
SETTINGS_MK = 1

NAME = a.out

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(IDIR)

CXXFLAGS += -std=c++98 -pedantic
# Debugging
DFLAGS = -g3 -fsanitize=address
# CXXFLAGS += $(DFLAGS)

endif # SETTINGS_MK
