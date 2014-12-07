CC=g++-4.8
CFLAGS=-Wall -std=c++11 -c
BUILDDIR=build/
SRC=src/
HEAD=src/headers/
TARGET=MD5AwSum

all: build md5lib md5hash pugixml RainbowTable RepositoryManager input_parser md5awsum main $(TARGET)

$(TARGET): $(BUILDDIR)md5lib.o $(BUILDDIR)Md5Hash.o $(BUILDDIR)pugixml.o $(BUILDDIR)RainbowTable.o $(BUILDDIR)RepositoryManager.o $(BUILDDIR)input_parser.o $(BUILDDIR)md5awsum.o $(BUILDDIR)main.o
	@printf 'building executable...\t\t'
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)Md5Hash.o $(BUILDDIR)pugixml.o $(BUILDDIR)RainbowTable.o $(BUILDDIR)RepositoryManager.o $(BUILDDIR)input_parser.o $(BUILDDIR)md5awsum.o $(BUILDDIR)main.o -o $(TARGET)
	@mv MD5AwSum md5awsum
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

md5hash: build $(SRC)md5hash.cpp $(HEAD)md5hash.h $(HEAD)md5lib.h
	@printf 'building md5hash...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5hash.cpp -o $(BUILDDIR)md5hash.o
	@echo 'complete.'

pugixml: build $(SRC)pugixml.cpp $(HEAD)pugixml.hpp
	@printf 'building pugixml...\t\t'
	@$(CC) $(CFLAGS) $(SRC)pugixml.cpp -o $(BUILDDIR)pugixml.o
	@echo 'complete.'

RainbowTable: build $(SRC)RainbowTable.cpp $(HEAD)RainbowTable.h $(HEAD)pugixml.hpp
	@printf 'building RainbowTable...\t'
	@$(CC) $(CFLAGS) $(SRC)RainbowTable.cpp -o $(BUILDDIR)RainbowTable.o
	@echo 'complete.'

RepositoryManager: build $(SRC)RepositoryManager.cpp $(HEAD)RepositoryManager.h $(HEAD)RainbowTable.h $(HEAD)md5hash.h
	@printf 'building RepositoryManager...\t'
	@$(CC) $(CFLAGS) $(SRC)RepositoryManager.cpp -o $(BUILDDIR)RepositoryManager.o
	@echo 'complete.'

input_parser: build $(SRC)input_parser.cpp $(HEAD)md5awsum.h
	@printf 'building input_parser...\t\t'
	@$(CC) $(CFLAGS) $(SRC)input_parser.cpp -o $(BUILDDIR)input_parser.o
	@echo 'complete.'

md5awsum: build $(SRC)md5awsum.cpp $(HEAD)md5awsum.h $(HEAD)RainbowTable.h $(HEAD)md5hash.h $(HEAD)RepositoryManager.h
	@printf 'building md5awsum...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5awsum.cpp -o $(BUILDDIR)md5awsum.o
	@echo 'complete.'

main: build $(SRC)main.cpp $(HEAD)md5awsum.h $(SRC)input_parser.cpp
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
	@mv md5awsum /usr/bin
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
