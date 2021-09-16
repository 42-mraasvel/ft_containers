ifndef SETTINGS_MK
SETTINGS_MK = 1

ifdef USING_CATCH
	NAME = catch.exe
	ifdef USING_STD
		NAME = catch_std.exe
	endif # USING_CATCH
else
	NAME = a.out
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
