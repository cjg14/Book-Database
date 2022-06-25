#include "menu.h" 
using namespace std;
//Definitions for class "Menu"
//Constructor
Menu::Menu() {}
Menu::~Menu() {}

//Main menu

char Menu::main_ans(const char& c) {
    main_c = c;
    return main_c;
}
char Menu::main_menu() const {
    initscr();

    move(1,1);
    printw("Welcome to the Book Database\n");
    move(2,1);
    printw("-------------------------------\n\n");
    move(3,5);
    printw("(A)dd a book.\n");
    move(4,5);
    printw("(F)ind a book.\n");
    move(5,5);
    printw("(D)elete a book.\n");
    move(6,5);
    printw("(L)ist books.\n");
    move(7,5);
    printw("(Q)uit\n\n");
    move(8,1);
    printw("Enter the letter of your choice: ");

    refresh();

    char option;
    cin >> option;

    if(option != 'a' && option != 'f' && option != 'd' && option != 'l' && option != 'q')
    {
        move(6,8);
        printw("Please enter a valid choice! ");
        endwin();
        option = main_menu();
    } else {
        endwin();
    }
    
    return option;
}

char Menu::find_ans(const char& c) {
    find_c = c;
    return find_c;
} 
char Menu::find_menu() const
{
    initscr();

    move(1,1);
    printw("Find a book\n");
    move(2,1);
    printw("------------\n");
    move(3, 1);
    printw("You can search by:\n\n");
    move(4,5);
    printw("(T)itle of the book.\n");
    move(5,5);
    printw("(A)uthor who wrote the book.\n");
    move(6,5);
    printw("(G)enre of the book.\n");
    move(7,5);
    printw("(Y)ear the book was published.\n");
    move(8,5);
    printw("(R)ating of the book.\n");
    move(9,5);
    printw("(B)ack to the main menu.\n\n");
    move(10,1);
    printw("Enter the letter of your choice: ");

    refresh();

    char letter;
    cin >> letter;

    if(letter != 't' && letter != 'a' && letter != 'g' && letter != 'y' && letter != 'r' && letter != 'b')
    {
        move(11,8);
        printw("Please enter a valid choice! ");
        endwin();

        letter = find_menu();
    } else {
        endwin();
    }
    
    return letter;
}
char Menu::delete_ans(const char& c) {
    delete_c = c;
    return delete_c;
}
char Menu::delete_menu() const
{
    initscr();

    move(1,1);
    printw("Delete a book\n");
    move(2,1);
    printw("------------\n");
    move(3, 1);
    printw("You can search by:\n\n");
    move(4,5);
    printw("(T)itle of the book.\n");
    move(5,5);
    printw("(A)uthor who wrote the book.\n");
    move(6,5);
    printw("(G)enre of the book.\n");
    move(7,5);
    printw("(Y)ear the book was published.\n");
    move(8,5);
    printw("(R)ating of the book.\n");
    move(9,5);
    printw("(B)ack to the main menu.\n\n");
    move(10,1);
    printw("Enter the letter of your choice: ");

    refresh();

    char letter;
    cin >> letter;

    if(letter != 't' && letter != 'a' && letter != 'g' && letter != 'y' && letter != 'r' && letter != 'b')
    {
        move(11,8);
        printw("Please enter a valid choice! ");
        endwin();

        letter = delete_menu();
    } else {
        endwin();
    }
    
    return letter;
}
char Menu::list_ans(const char& c) {
    list_c = c;
    return list_c;
}
char Menu::list_menu() const
{
    initscr();

    move(1,1);
    printw("List Records\n");
    move(2,1);
    printw("-------------\n");
    move(3,5);
    printw("You can list by:\n\n");
    move(4,5);
    printw("(T)itle of the book.\n");
    move(5,5);
    printw("(A)uthor who wrote the book.\n");
    move(6,5);
    printw("(G)enre of the book.\n");
    move(7,5);
    printw("(Y)ear the book was published.\n");
    move(8,5);
    printw("(R)ating of the book.\n");
    move(9,5);
    printw("(B)ack to the main menu.\n\n");
    move(10,1);
    printw("Enter the letter of your choice: ");
    
    refresh();

    char letter;
    cin >> letter;

    if(letter != 't' && letter != 'a' && letter != 'g' && letter != 'y' && letter != 'r' && letter != 'b')
    {
        move(11,8);
        printw("Please enter a valid choice! ");
        endwin();

        letter = list_menu();
    } else {
        endwin();
    }
    
    return letter;
}

char Menu::string_ans(const char& c) {
    list_string_c = c;
    return list_string_c;
}
char Menu::list_string_options() const
{
    initscr();

    move(1,1);
    printw("Choose the listing format:\n\n");
    move(2,5);
    printw("(A)lphabetical order.\n");
    move(3,5);
    printw("(R)everse alphabetical order.\n");
    move(5,5);
    printw("Enter the letter of your choice: ");
    
    refresh();

    char option;
    cin >> option;

    if (option != 'a' && option != 'r') {
        move(6, 8);
        printw("Please enter a correct choice! ");
        endwin();

        option = list_string_options();
    } else {
        endwin();
    }
    return option;
}

char Menu::num_ans(const char& c) {
    list_num_c  = c;
    return list_num_c;
}
char Menu::list_number_options() const
{
    
    initscr();

    move(1, 1);
    printw("Choose the listing format:");
    move(2, 5);
    printw("(A)scending order.");
    move(3, 5);
    printw("(D)escending order.");
    move(4, 5);
    printw("Enter the letter of your choice: ");

    refresh();

    char option;
    cin >> option;

    if (option != 'a' && option != 'd') {
        move(6, 8);
        printw("Please enter a correct choice! ");
        endwin();

        option = list_number_options();
    } else {
        endwin();
    }
    
    return option;
}

