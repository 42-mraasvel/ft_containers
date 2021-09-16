ifndef SRC_FILES_MK
SRC_FILES_MK = 1

ifdef USING_CATCH
	include make_settings/catch_src.mk
else
	include make_settings/normal_src.mk
endif # USING_CATCH

SDIR = src
IDIR = includes
ODIR = obj
DDIR = dep
ifdef USING_STD
	ODIR = obj/std
	DDIR = dep/std
endif # catch_src

OBJ = $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))
DEP = $(patsubst $(SDIR)/%.cpp,$(DDIR)/%.d,$(SRC))

endif # SRC_FILES_MK
