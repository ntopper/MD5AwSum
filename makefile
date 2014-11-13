CC=g++
CFLAGS=-Wall -std=c++11 -c
BUILDDIR=build/
TARGET=testmd5

all: $(TARGET)

$(TARGET): build md5lib.o md5libtest.o
	@printf 'building executable... '
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)md5libtest.o -o $(TARGET)
	@echo 'complete.'
	@echo 'Enjoy your program!!'

build:
	@printf 'building build directory... '
	@mkdir $(BUILDDIR)
	@echo 'complete.'

md5lib.o: md5lib.cpp md5lib.h
	@printf	'building md5lib... '
	@$(CC) $(CFLAGS) md5lib.cpp -o $(BUILDDIR)md5lib.o
	@echo 'complete.'

md5libtest.o: md5libtest.cpp md5lib.h
	@printf 'building md5libtest... '
	@$(CC) $(CFLAGS) md5libtest.cpp -o $(BUILDDIR)md5libtest.o
	@echo 'complete.'

clean:
	@printf 'deleting .o files... '
	@rm $(BUILDDIR)*.o
	@echo 'complete.'
	@printf 'deleting build directory... '
	@rm -r $(BUILDDIR)
	@echo 'complete.'
	@printf 'deleting executable... '
	@rm $(TARGET)
	@echo 'complete.'