CXX         = g++
CXXFLAGS    = -Wall
GDBFLAGS	= -O0 -g
INCLIB      = -I $(BOOSTDIR) -I $(EFPDIR)
GROUPTEST   = -D GROUP_TEST
BOOSTDIR    = ../../boost/boost_1_74_0
EFPDIR      = ./extended_fixed_point
TESTDIR     = ./test
CPPSOURCES  = ./test/*.cpp

# Compile a single .cpp file specifying the name
# Usage: make single_compile FILENAME=x
single_compile:
	if [ ! -d "$(TESTDIR)/out_files" ]; then \
		mkdir $(TESTDIR)/out_files ; \
	fi
	$(CXX) $(CXXFLAGS) $(INCLIB) $(TESTDIR)/$(FILENAME).cpp -o $(TESTDIR)/out_files/$(FILENAME) 

# Execute a single .cpp file specifying the name
# Usage: make single_exec FILENAME=x
single_exec:
	$(TESTDIR)/out_files/$(FILENAME)


compile:
	if [ ! -d "$(TESTDIR)/out_files" ]; then \
		mkdir $(TESTDIR)/out_files ; \
	fi
	$(CXX) $(CXXFLAGS) $(INCLIB) $(TESTDIR)/*.cpp -o $(TESTDIR)/out_files/unit_test $(GROUP_TEST)
	
unit_test:
	$(TESTDIR)/out_files/unit_test
	
clean:
	rm -r $(TESTDIR)


# Old compiling stuff
# for CPPFILE in $(CPPSOURCES) ; do \
#	echo Compiling: $$CPPFILE ; \
#	OBJ=$$(basename $$CPPFILE .cpp) ; \
# $(CC) $(CFLAGS) $$CPPFILE -o $(TESTDIR)/$$OBJ ; \
# done
