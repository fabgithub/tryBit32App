
all : FakeThreadStackOperation_x86.o

TEST_SUITE_HEADER_FILES = \
	testFakeThreadWrap.h

FakeThreadStackOperation_x86.o : FakeThreadStackOperation_x86.s makefile
	./nasm -f macho32 -o FakeThreadStackOperation_x86.o FakeThreadStackOperation_x86.s

clean :
	rm -f *.o
