#
#  File name: Makefile
#
#  Author: 2024 Fall Semester AED Team
#
#  Release date: 2024/10/21
#
#  Description: Makefile for the individual evaluation lab (LAI) code
#
#  Usage:
#
#     1)  To generate the executable file for the program compBN, run
#         $ make compBN
#
#     3) To clean all object files and the executable file, run
#         $ make clean
#
#     4) Some test run targets are included, e.g. tb1
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic

#  Sources
SOURCES =  bignum.c bignum.h compBN.c

#  Objects
OBJECTS3 = bignum.o compBN.o

compBN: $(OBJECTS3)
	$(CC) -g -o $@ $(OBJECTS3)

bignum.o: bignum.h bignum.c
	$(CC) -g -c bignum.c

compBN.o: bignum.h compBN.c
	$(CC) -g -c compBN.c

%.o : %.c

clean::
	rm -f *.o core a.out compBN *~

depend::
	makedepend $(SOURCES)

# Tests for p3

tb1:	compBN
	echo 1 0 | ./compBN

tb2:	compBN
	echo 8888888888888888888888 -27 | ./compBN

N=9876543210987654321098765432109876543210987654321098765432109876543210
M=39

tb3:	compBN
	echo $N $M | ./compBN


# DO NOT DELETE
