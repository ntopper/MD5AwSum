CC=g++
CFLAGS=-Wall -std=c++11 -c
BUILDDIR=build/
SRC=src/
HEAD=src/headers/
TARGET=testmd5

all: $(TARGET)

$(TARGET): build md5lib Md5Hash md5libtest
	@printf 'building executable...\t\t'
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)md5libtest.o $(BUILDDIR)Md5Hash.o -o $(TARGET)
	@echo 'complete.'
	@echo 'Enjoy your program!!'

build:
	@printf 'building build directory...\t'
	@mkdir $(BUILDDIR)
	@echo 'complete.'

md5lib: $(SRC)md5lib.cpp $(HEAD)md5lib.h
	@printf	'building md5lib...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5lib.cpp -o $(BUILDDIR)md5lib.o
	@echo 'complete.'

md5libtest: tempfiles $(SRC)md5libtest.cpp $(HEAD)md5lib.h
	@printf 'building md5libtest...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5libtest.cpp -o $(BUILDDIR)md5libtest.o
	@echo 'complete.'

Md5Hash: $(SRC)Md5Hash.cpp $(HEAD)Md5Hash.h
	@printf 'building Md5Hash...\t\t'
	@$(CC) $(CFLAGS) $(SRC)Md5Hash.cpp -o $(BUILDDIR)Md5Hash.o
	@echo 'complete.'

tempfiles:
	@printf 'building testfiles...\t\t'
	@echo 'this is a test file!!!' > /tmp/.testfile
	@perl -e 'for (my $$i=0; $$i <= 1000000; $$i++) { print "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\n"; }' > /tmp/.testfile
	@printf '' > /tmp/.emptyfile
	@echo 'complete.'

clean:
	@printf 'deleting .o files...\t\t'
	@rm $(BUILDDIR)*.o
	@echo 'complete.'
	@printf 'deleting build directory...\t'
	@rm -r $(BUILDDIR)
	@echo 'complete.'
	@printf 'deleting executable...\t\t'
	@rm $(TARGET)
	@echo 'complete.'
