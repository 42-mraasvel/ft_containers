include make_settings/src_files.mk
include make_settings/settings.mk

.PHONY: all
all: $(NAME)

# Compilation
$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ)
$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(IFLAGS)
$(DDIR)/%.d: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $< -MM -MF $@ -MT $(ODIR)/$*.o $(IFLAGS)

# Cleaning
clean:
	$(RM) -r $(ODIR)
fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(DDIR)
re: fclean
	$(MAKE) all

-include $(DEP)
