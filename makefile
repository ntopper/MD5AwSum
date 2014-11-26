CC=g++-4.8
CFLAGS=-Wall -std=c++11 -c
BUILDDIR=build/
SRC=src/
HEAD=src/headers/
TARGET=MD5AwSum

all: build md5lib Md5Hash pugixml RainbowTable RepositoryManager inputParser md5awsum main $(TARGET)

$(TARGET): $(BUILDDIR)md5lib.o $(BUILDDIR)Md5Hash.o $(BUILDDIR)pugixml.o $(BUILDDIR)RainbowTable.o $(BUILDDIR)RepositoryManager.o $(BUILDDIR)inputParser.o $(BUILDDIR)md5awsum.o $(BUILDDIR)main.o
	@printf 'building executable...\t\t'
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)Md5Hash.o $(BUILDDIR)pugixml.o $(BUILDDIR)RainbowTable.o $(BUILDDIR)RepositoryManager.o $(BUILDDIR)inputParser.o $(BUILDDIR)md5awsum.o $(BUILDDIR)main.o -o $(TARGET)
	@echo 'complete.'
	@echo 'Enjoy your program!!'

build:
	@printf 'creating build directory...\t'
	@mkdir $(BUILDDIR)
	@echo 'complete.'

md5lib: build $(SRC)md5lib.cpp $(HEAD)md5lib.h
	@printf	'building md5lib...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5lib.cpp -o $(BUILDDIR)md5lib.o
	@echo 'complete.'

Md5Hash: build $(SRC)Md5Hash.cpp $(HEAD)Md5Hash.h $(HEAD)md5lib.h
	@printf 'building Md5Hash...\t\t'
	@$(CC) $(CFLAGS) $(SRC)Md5Hash.cpp -o $(BUILDDIR)Md5Hash.o
	@echo 'complete.'

pugixml: build $(SRC)pugixml.cpp $(HEAD)pugixml.hpp
	@printf 'building pugixml...\t\t'
	@$(CC) $(CFLAGS) $(SRC)pugixml.cpp -o $(BUILDDIR)pugixml.o
	@echo 'complete.'

RainbowTable: build $(SRC)RainbowTable.cpp $(HEAD)RainbowTable.h $(HEAD)pugixml.hpp
	@printf 'building RainbowTable...\t'
	@$(CC) $(CFLAGS) $(SRC)RainbowTable.cpp -o $(BUILDDIR)RainbowTable.o
	@echo 'complete.'

RepositoryManager: build $(SRC)RepositoryManager.cpp $(HEAD)RepositoryManager.h $(HEAD)RainbowTable.h $(HEAD)Md5Hash.h
	@printf 'building RepositoryManager...\t'
	@$(CC) $(CFLAGS) $(SRC)RepositoryManager.cpp -o $(BUILDDIR)RepositoryManager.o
	@echo 'complete.'

inputParser: build $(SRC)inputParser.cpp
	@printf 'building inputParser...\t\t'
	@$(CC) $(CFLAGS) $(SRC)inputParser.cpp -o $(BUILDDIR)inputParser.o
	@echo 'complete.'

md5awsum: build $(SRC)md5awsum.cpp $(HEAD)md5awsum.h $(HEAD)RainbowTable.h $(HEAD)Md5Hash.h $(HEAD)RepositoryManager.h $(SRC)inputParser.cpp
	@printf 'building md5awsum...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5awsum.cpp -o $(BUILDDIR)md5awsum.o
	@echo 'complete.'

main: build $(SRC)main.cpp $(HEAD)md5awsum.h $(SRC)inputParser.cpp
	@printf 'building main...\t\t'
	@$(CC) $(CFLAGS) $(SRC)main.cpp -o $(BUILDDIR)main.o
	@echo 'complete.'

md5libtest: build tempfiles $(SRC)md5libtest.cpp $(HEAD)md5lib.h
	@printf 'building md5libtest...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5libtest.cpp -o $(BUILDDIR)md5libtest.o
	@echo 'complete.'
	@printf 'building testmd5 executable...\t'
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)md5libtest.o -o testmd5
	@echo 'complete.'

tempfiles:
	@printf 'building testfiles...\t\t'
	@echo 'this is a test file!!!' > /tmp/.testfile
	@perl -e 'for (my $$i=0; $$i <= 1000000; $$i++) { print "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\n"; }' > /tmp/.testfile
	@printf '' > /tmp/.emptyfile
	@echo 'complete.'

install:
	@printf 'installing MD5AwSum in /usr/bin... '
	@mv MD5AwSum /usr/bin
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
