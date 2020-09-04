all: build shell

CC=gcc
DST=build
SRC=src
# path of project directory
HOME=$(shell pwd)
# path to the implementations
BINARIES=$(HOME)/build

build:
	mkdir build

shell: $(SRC)/shell.c myrm mygrep mydir myls mymv mycat mychmod mycp $(SRC)/mycd.h $(SRC)/mypwd.h
	@echo "Building shell..."
	@gcc  -DHOME='"$(HOME)"' -DBINARIES='"$(BINARIES)"'  $(SRC)/shell.c  -o shell

# rm
myrm: $(SRC)/myrm.c $(SRC)/mymkdir.h $(SRC)/isDir.h
	@echo "Building rm..."
	@gcc $(SRC)/myrm.c -o $(DST)/myrm

#grep
mygrep: $(SRC)/mygrep.c
	@echo "Building grep..."
	@gcc $(SRC)/mygrep.c -o $(DST)/mygrep

#mkdir
mydir: $(SRC)/mymkdir.c $(SRC)/mymkdir.h $(SRC)/isDir.h
	@echo "Building mkdir..."
	@gcc $(SRC)/mymkdir.c -o $(DST)/mymkdir

#ls
myls: $(SRC)/myls.c
	@echo "Building ls..."
	@gcc $(SRC)/myls.c -o $(DST)/myls

#cp
mycp: $(SRC)/mycp.c $(SRC)/mymkdir.h $(SRC)/mycp_utils.h
	@echo "Building cp..."
	@gcc $(SRC)/mycp.c -o $(DST)/mycp

#mv
mymv: $(SRC)/mymv.c $(SRC)/isDir.h
	@echo "Building mv..."
	@gcc $(SRC)/mymv.c -o $(DST)/mymv

#cat
mycat: $(SRC)/mycat.c
	@echo "Building cat..."
	@gcc $(SRC)/mycat.c -o $(DST)/mycat

#chmod
mychmod: $(SRC)/mychmod.c
	@echo "Building chmod..."
	@gcc $(SRC)/mychmod.c -o $(DST)/mychmod

clean:
	@echo "Cleaning..."
	@rm -r build shell