ifndef SETTINGS_MK
SETTINGS_MK = 1

DEF_EXEC = a.out
CATCH_EXEC = catch.exe
CATCH_STD_EXEC = catch_std.exe
EXECS = $(DEF_EXEC) $(CATCH_EXEC) $(CATCH_STD_EXEC)

ifdef USING_CATCH
	NAME = $(CATCH_EXEC)
	ifdef USING_STD
		NAME = $(CATCH_STD_EXEC)
	endif # USING_CATCH
else
	NAME = $(DEF_EXEC)
endif # USING_CATCH


CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(IDIR)

ifdef USING_CATCH
	CXXFLAGS += -std=c++14 -pedantic
	ifdef USING_STD
		CXXFLAGS += -DUSING_STD=1
	endif # USING_STD
else
	CXXFLAGS += -std=c++98 -pedantic
endif # USING_CATCH
CXXFLAGS += -O3

endif # SETTINGS_MK
