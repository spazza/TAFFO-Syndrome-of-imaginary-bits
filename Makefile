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

# Compile the whole project
compile: create_out_dir
	$(CXX) $(CXXFLAGS) $(INCLIB) $(CPPFILES) -o $(TESTOUTDIR)/unit_test

# Execute all the tests of the project
exec: compile
	$(TESTOUTDIR)/unit_test 

# Compile a single test of the project
# Necessary to specify the variable TESTNAME in the command invocation
compile_single: create_out_dir
	$(CXX) $(CXXFLAGS) $(INCLIB) $(TESTDIR)/$(TESTNAME).cpp $(RANDDIR)/*.cpp -o $(TESTOUTDIR)/$(TESTNAME) $(SINGLECOMP)

# Execute a single test of the project
# Necessary to specify the variable TESTNAME in the command invocation
exec_single: compile_single
	$(TESTOUTDIR)/$(TESTNAME)

# Compile the whole project adding debug flags
compile_debug: create_out_dir
	$(CXX) $(CXXFLAGS) $(GDBFLAGS) $(INCLIB) $(CPPFILES) -o $(TESTOUTDIR)/unit_test

# Run the debugger on the whole project
debug: compile_debug
	$(GDB) $(TESTOUTDIR)/unit_test

# Compile a single test of the project adding debug flags
# Necessary to specify the variable TESTNAME in the command invocation
compile_single_debug: create_out_dir
	$(CXX) $(CXXFLAGS) $(GDBFLAGS) $(INCLIB) $(TESTDIR)/$(TESTNAME).cpp $(RANDDIR)/*.cpp -o $(TESTOUTDIR)/$(TESTNAME) $(SINGLECOMP)

# Run the debugger on a single test of the project
# Necessary to specify the variable TESTNAME in the command invocation
debug_single: compile_single_debug
	$(GDB) $(TESTOUTDIR)/$(TESTNAME)

# Clean all the out files produced by the compilation process
clean:
	rm -r $(TESTOUTDIR)