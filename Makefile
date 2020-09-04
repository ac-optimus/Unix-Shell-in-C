all: build shell

CC=gcc
DST=build
SRC=src
HOME=$(shell pwd)
BINARIES=$(HOME)/build

build:
	mkdir build

shell: $(SRC)/shell.c myrm mygrep mydir myls mymv mycat mychmod mycp $(SRC)/mycd.h $(SRC)/mypwd.h
	gcc  -DHOME='"$(HOME)"' -DBINARIES='"$(BINARIES)"'  $(SRC)/shell.c  -o shell

# rm
myrm: $(SRC)/myrm.c $(SRC)/mymkdir.h $(SRC)/isDir.h
	gcc $(SRC)/myrm.c -o $(DST)/myrm

#grep
mygrep: $(SRC)/mygrep.c
	gcc $(SRC)/mygrep.c -o $(DST)/mygrep

#mkdir
mydir: $(SRC)/mymkdir.c $(SRC)/mymkdir.h $(SRC)/isDir.h
	gcc $(SRC)/mymkdir.c -o $(DST)/mymkdir

#ls
myls: $(SRC)/myls.c
	gcc $(SRC)/myls.c -o $(DST)/myls

#cp
mycp: $(SRC)/mycp.c $(SRC)/mymkdir.h $(SRC)/mycp_utils.h
	gcc $(SRC)/mycp.c -o $(DST)/mycp
#mv
mymv: $(SRC)/mymv.c $(SRC)/isDir.h
	gcc $(SRC)/mymv.c -o $(DST)/mymv

#cat
mycat: $(SRC)/mycat.c
	gcc $(SRC)/mycat.c -o $(DST)/mycat

#chmod
mychmod: $(SRC)/mychmod.c
	gcc $(SRC)/mychmod.c -o $(DST)/mychmod

clean:
	rm -r build shell