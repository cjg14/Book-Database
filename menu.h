#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <ncurses.h>
#include "database.h"
using namespace std;

//Main menu 
class Menu { 
private:
    char main_c;
    char add_c;
    char find_c;
    char delete_c;
    char list_c;

    char list_string_c;
    char list_num_c;
public: 
    //Construtor
    Menu(); 
    ~Menu();
    
    //Main menu
    char main_ans(const char& c);
    char main_menu() const;
    
    //Find menu
    char find_ans(const char& c);
    char find_menu() const;
    
    //Delete menu
    char delete_ans(const char& c);
    char delete_menu() const;

    //List menu
    char list_ans(const char& c);
    char list_menu() const;

    char string_ans(const char& c);
    char list_string_options() const;

    char num_ans(const char& c);
    char list_number_options() const;


};
#endif
