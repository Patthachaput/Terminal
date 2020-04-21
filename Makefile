#  Makefile for online auction program (project in CPE111) 
#
#
#  Project CPE111 Data structure - TEAM TERMINAL
#  Member: Natacha Punyathanasub       (Nut)       62070503415
#          Patthachaput Thanesmaneerat (Jui)       62070503432
#          Supakorn Srisawas           (Field)     62070503464
#          Narapathra Morakrant        (Foremost)  62070503464
#
#


ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= onlineAuction$(EXECEXT) 

all : $(EXECUTABLES)

validate.o :	validate.c validate.h
	gcc -c validate.c

fileManager.o :	fileManager.c mainAuction.h
	gcc -c fileManager.c

dataBuilder.o :	dataBuilder.c dataBuilder.h mainAuction.h
	gcc -c databuilder.c

interface.o :	interface.c validate.h dataBuilder.h
	gcc -c interface.c

onlineAuction$(EXECEXT) : interface.o validate.o dataBuilder.o fileManager.o
	gcc -o onlineAuction$(EXECEXT) interface.o validate.o dataBuilder.o fileManager.o


clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
