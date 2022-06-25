Welcome, this is a comprehensive database tool for reading in book data and prompting user input records. This program is implemented for Linux OS via bash terminal. 

Instructions for Compiling and Running
--------------------------------------
Commands for this makefile that can be typed at the command line (bash terminal):

    make
        Build the executable program main_test

    make -j
        Build main_test possibly a little quickly. The "-j" option tells
        make to try to use multiple CPUs when compiling two, or more, files.

    make clean
        Delete main_test, and all the .o object files.

    make <name>
        Compiles a specific file, where <name> is the name of one of the rules
        listed in the makefile below, i.e. database, book, menu, main, and main_test

Known Bugs (work in progress)
----------
    {Ncurses}
        - As a result of implementing ncurses, the menus will have outputting errors as not all the 
        sub-menus were implemented with ncurses. However, the features still work, it's just that the 
        outputting has some bugs especially with the indenting and repeated characters that were 
        supposed to be refreshed. 
        - While program is running, the display will switch between the terminal and the ncurses screen as
        the program is inconsistent with its displaying methods 
    {Reading in records}
        - In database.txt, DO NOT enter a BLANK field. ALL fields must be entered with something.
        - DO NOT ENTER "{" "}" in database.txt <--will cause an error as those are seperators 
        example: 
            THIS IS NOT OKAY
                {} {} {} {} {} 
            THIS IS NOT OKAY
                {} {Author} {} {} {4}
            THIS IS NOT OKAY
                {xyc} {wef} {aewf} {1231} <--missing a field (cannot miss any fields!)
            This is okay 
                {Title} {Author} {Genre} {2001} {5}

Extra Features (Work in progress)
--------------

