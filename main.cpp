#include "book.h"
#include "database.h"
#include "menu.h"
using namespace std;

int main () {
    Database d;

    Menu m;
    while (true) {
       
        char mc = m.main_ans(m.main_menu());
        if (mc == 'a') {
            d.add_book();
            cout << "\nPress enter to return to main menu! ";
            cout << "\n-------------------------------------\n\n";
            cin.get();
        }
        if (mc == 'f') {
            char fc = m.find_ans(m.find_menu());
            if (fc == 't') {
                d.search_title();
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
            if (fc == 'a') {
                d.search_author(); 
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
            if (fc == 'g') {
                d.search_genre();
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
            if (fc == 'y') {
                d.search_year();
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
            if (fc == 'r') {
                d.search_rating();  
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
                
            }   
        }
        if (mc == 'd') {
            char dc = m.delete_ans(m.delete_menu());
            if (dc == 't') {
                d.delete_by_title();  
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin(); 
            }
            if (dc == 'a') {
                d.delete_by_author();  
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin(); 
            }
            if (dc == 'g') {
                d.delete_by_genre();  
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();              
            }
            if (dc == 'y') {
                d.delete_by_year();
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
            if (dc == 'r') {
                d.delete_by_rating();
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
        }
        if (mc == 'l') {
            char lc = m.list_ans(m.list_menu());
            if (lc == 't') {
                char string_c = m.string_ans(m.list_string_options());
                if (string_c == 'a') {
                    d.list_title_alpha();
                }
                if (string_c == 'r') {
                    d.list_title_rev_alpha();
                }   
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();             
            }
            if (lc == 'a') {
                char string_c = m.string_ans(m.list_string_options());
                if (string_c == 'a') {
                    d.list_author_alpha();
                }
                if (string_c == 'r') {
                    d.list_author_rev_alpha();
                }     
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();          
            }
            if (lc == 'g') {
                char string_c = m.string_ans(m.list_string_options());
                if (string_c == 'a') {
                    d.list_genre_alpha();
                }
                if (string_c == 'r') {
                    d.list_genre_rev_alpha();
                }
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
            if (lc == 'y') {
                char num_c = m.num_ans(m.list_number_options());
                if (num_c == 'a') {
                    d.list_year_ascending();
                }
                if (num_c == 'd') {
                    d.list_year_descending();
                }
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
            if (lc == 'r') {
                char num_c = m.num_ans(m.list_number_options());
                if (num_c == 'a') {
                    d.list_rating_ascending();
                }
                if (num_c == 'd') {
                    d.list_rating_descending();
                }
                cout << "\nPress enter to return to main menu! ";
                cout << "\n-------------------------------------\n\n";
                cin.get();
                endwin();
            }
        }
        if (mc == 'q') {
            cout << "Database ended.\n";
            d.write_to();
            return 0;
        }
        endwin();
    }
}

