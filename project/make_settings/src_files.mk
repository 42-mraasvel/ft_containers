ifndef SRC_FILES_MK
SRC_FILES_MK = 1

SDIR = src
ODIR = obj
IDIR = includes
DDIR = dep

SRC = $(shell find $(SDIR) -type f -name "*.cpp")
OBJ = $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))
DEP = $(patsubst $(SDIR)/%.cpp,$(DDIR)/%.d,$(SRC))

endif # SRC_FILES_MK
