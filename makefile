##############################################################################
#
# Makefile for Final Project of CMPT 135 Spring 2021, SFU Surrey.
#
# Commands for this makefile that can be typed at the command line:
#
#   make
#      Build the executable program main_test
#
#   make -j
#      Build main_test possibly a little quickly. The "-j" option tells
#      make to try to use multiple CPUs when compiling two, or more, files.
#
#   make clean
#      Delete main_test, and all the .o object files.
#
#   make <name>
#      Compiles a specific file, where <name> is the name of one of the rules
#      listed in the makefile below, i.e. database, book, menu, main, and main_test
#
##############################################################################

# Set the C++ compiler options:
#   -std=c++17 compiles using the C++17 standard (or at least as 
#    much as is implemented by the compiler, e.g. for g++ see
#    http://gcc.gnu.org/projects/cxx0x.html)
#   -Wall turns on all warnings
#   -Wextra turns on even more warnings
#   -Werror causes warnings to be errors 
#   -Wfatal-errors stops the compiler after the first error 
#   -Wno-sign-compare turns off warnings for comparing signed and 
#    unsigned numbers
#   -Wnon-virtual-dtor warns about non-virtual destructors
#   -g puts debugging info into the executables (makes them larger)
CPPFLAGS = -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

main_test: database.o book.o menu.o main.o 
	g++ -o main_test database.o book.o menu.o main.o -lncurses

database:
	g++ -c $(CPPFLAGS) database.cpp

book:
	g++ -c $(CPPFLAGS) book.cpp

menu:
	g++ -c $(CPPFLAGS) menu.cpp

main:
	g++ -c $(CPPFLAGS) main.cpp

clean:
	rm -f main_test database.o book.o menu.o main.o