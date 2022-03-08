CXX 		= g++
CXXFLAGS	= -Wall
GDB			= gdb
GDBFLAGS	= -O0 -ggdb
INCLIB		= -I $(BOOSTDIR) -I $(FPDIR) -I $(RANDDIR)
BOOSTDIR	= ./../boost_1_77_0
FPDIR	 	= ./fixed_point
RANDDIR		= ./test/other_testing_stuff
TESTDIR		= ./test
TESTOUTDIR	= $(TESTDIR)/out_files
CPPFILES	= $(TESTDIR)/*.cpp $(RANDDIR)/*.cpp
SINGLECOMP	= -D SINGLE_TEST

# Create the output folder for test files
create_out_dir:
	if [ ! -d "$(TESTOUTDIR)" ]; then mkdir $(TESTOUTDIR) ; fi

# Execute the tests
exec: compile
	$(TESTOUTDIR)/unit_test 

# Compile the project
compile: create_out_dir
	$(CXX) $(CXXFLAGS) $(INCLIB) $(CPPFILES) -o $(TESTOUTDIR)/unit_test

compile_single: create_out_dir
	$(CXX) $(CXXFLAGS) $(INCLIB) $(TESTDIR)/$(TESTNAME).cpp $(RANDDIR)/*.cpp -o $(TESTOUTDIR)/$(TESTNAME) $(SINGLECOMP)

# Compile adding debug flags
compile_debug: create_out_dir
	$(CXX) $(CXXFLAGS) $(GDBFLAGS) $(INCLIB) $(CPPFILES) -o $(TESTOUTDIR)/unit_test

# Run the debugger
debug: compile_debug
	$(GDB) $(TESTOUTDIR)/unit_test

# Clean all the out files produced by the compilation process
clean:
	rm -r $(TESTOUTDIR)