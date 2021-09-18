include make_settings/src_files.mk
include make_settings/settings.mk

.PHONY: all
all: $(NAME)

# Compilation
$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ)
$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(IFLAGS) -g3
$(DDIR)/%.d: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $< -MM -MF $@ -MT $(ODIR)/$*.o $(CXXFLAGS) $(IFLAGS)

# Cleaning
clean:
	$(RM) -r $(ODIR)
fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(DDIR)
re: fclean
	$(MAKE) all

# Catch compilation rule
.PHONY: catch catch_std
catch:
	$(MAKE) all USING_CATCH=1
catch_std:
	$(MAKE) all USING_CATCH=1 USING_STD=1

-include $(DEP)
