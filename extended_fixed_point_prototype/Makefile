CC         = g++
CFLAGS     = -Wall -O0 -g -I $(BOOSTDIR) -I $(EFPDIR)
BOOSTDIR   = /home/user/LLVM_STUFF/boost/boost_1_74_0
EFPDIR     = ./extended_fixed_point
TESTDIR    = ./test/test_files
CPPSOURCES = ./test/*.cpp

compile:
	if [ ! -d "$(TESTDIR)" ]; then \
		mkdir $(TESTDIR) ; \
	fi
	for CPPFILE in $(CPPSOURCES) ; do \
		echo Compiling: $$CPPFILE ; \
		OBJ=$$(basename $$CPPFILE .cpp) ; \
		$(CC) $(CFLAGS) $$CPPFILE -o $(TESTDIR)/$$OBJ ; \
	done
	
exec:
	for OBJFILE in $(TESTDIR)/* ; do \
		echo Test executed: $$OBJFILE ; \
		$$OBJFILE ; \
	done
	
clean:
	rm -r $(TESTDIR)

