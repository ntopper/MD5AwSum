CC=g++
CFLAGS=-Wall -std=c++11 -c
BUILDDIR=build/
TARGET=testmd5

all: $(TARGET)

$(TARGET): build md5lib md5libtest Md5Hash
	@printf 'building executable... '
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)md5libtest.o $(BUILDDIR)Md5Hash.o -o $(TARGET)
	@echo 'complete.'
	@echo 'Enjoy your program!!'

build:
	@printf 'building build directory... '
	@mkdir $(BUILDDIR)
	@echo 'complete.'

md5lib: md5lib.cpp md5lib.h
	@printf	'building md5lib... '
	@$(CC) $(CFLAGS) md5lib.cpp -o $(BUILDDIR)md5lib.o
	@echo 'complete.'

md5libtest: tempfiles md5libtest.cpp md5lib.h
	@printf 'building md5libtest... '
	@$(CC) $(CFLAGS) md5libtest.cpp -o $(BUILDDIR)md5libtest.o
	@echo 'complete.'

Md5Hash: Md5Hash.cpp Md5Hash.h
	@printf 'building Md5Hash... '
	@$(CC) $(CFLAGS) Md5Hash.cpp -o $(BUILDDIR)Md5Hash.o
	@echo 'complete.'

tempfiles:
	@printf 'building testfiles... '
	@echo 'this is a test file!!!' > /tmp/.testfile
	@perl -e 'for (my $$i=0; $$i <= 1000000; $$i++) { print "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\n"; }' > /tmp/.testfile
	@printf '' > /tmp/.emptyfile
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
