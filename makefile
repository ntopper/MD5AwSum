CC=g++
CFLAGS=-Wall -std=c++11 -c
BUILDDIR=build/
SRC=src/
HEAD=src/headers/
TARGET=MD5AwSum

all: $(TARGET)

$(TARGET): build md5lib Md5Hash RainbowTable RepositoryManager inputParser md5awsum
	@printf 'building executable...\t\t'
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)Md5Hash.o $(BUILDDIR)RainbowTable.o $(BUILDDIR)RepositoryManager.o $(BUILDDIR)inputParser.o $(BUILDDIR)md5awsum.o -o $(TARGET)
	@echo 'complete.'
	@echo 'Enjoy your program!!'

build:
	@printf 'creating build directory...\t'
	@mkdir $(BUILDDIR)
	@echo 'complete.'

md5lib: $(SRC)md5lib.cpp $(HEAD)md5lib.h
	@printf	'building md5lib...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5lib.cpp -o $(BUILDDIR)md5lib.o
	@echo 'complete.'

Md5Hash: $(SRC)Md5Hash.cpp $(HEAD)Md5Hash.h $(HEAD)md5lib.h
	@printf 'building Md5Hash...\t\t'
	@$(CC) $(CFLAGS) $(SRC)Md5Hash.cpp -o $(BUILDDIR)Md5Hash.o
	@echo 'complete.'

RainbowTable: $(SRC)RainbowTable.cpp $(HEAD)RainbowTable.h
	@printf 'building RainbowTable...\t'
	@$(CC) $(CFLAGS) $(SRC)RainbowTable.cpp -o $(BUILDDIR)RainbowTable.o
	@echo 'complete.'

RepositoryManager: $(SRC)RepositoryManager.cpp $(HEAD)RepositoryManager.h $(HEAD)RainbowTable.h $(HEAD)Md5Hash.h
	@printf 'building RepositoryManager...\t'
	@$(CC) $(CFLAGS) $(SRC)RepositoryManager.cpp -o $(BUILDDIR)RepositoryManager.o
	@echo 'complete.'

inputParser: $(SRC)inputParser.cpp
	@printf 'building inputParser...\t\t'
	@$(CC) $(CFLAGS) $(SRC)inputParser.cpp -o $(BUILDDIR)inputParser.o
	@echo 'complete.'

md5awsum: $(SRC)md5awsum.cpp $(HEAD)md5awsum.h $(HEAD)RainbowTable.h $(HEAD)Md5Hash.h $(HEAD)RepositoryManager.h
	@printf 'building md5awsum...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5awsum.cpp -o $(BUILDDIR)md5awsum.o
	@echo 'complete.'

md5libtest: tempfiles $(SRC)md5libtest.cpp $(HEAD)md5lib.h
	@printf 'building md5libtest...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5libtest.cpp -o $(BUILDDIR)md5libtest.o
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
