#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <ncurses.h>
#include <sstream>
#include "book.h"
using namespace std;

//Comparators
//TODO: should they be case insensitive or sensitive??
bool alpha_title(Book a, Book b);
bool rev_alpha_title(Book a, Book b);
bool alpha_author(Book a, Book b);
bool rev_alpha_author(Book a, Book b);
bool alpha_genre(Book a, Book b);
bool rev_alpha_genre(Book a, Book b);
bool asc_year(Book a, Book b);
bool desc_year(Book a, Book b);
bool asc_rating(Book a, Book b);
bool desc_rating(Book a, Book b);

string to_lower(const string& s);


struct matches_t;

class Database {
private: 
    vector<Book> books;    
public:
    
//Helpers
    //generates a string into a vector of substrings
    vector<string> generate_substrs(const string& s) const;

    //checks if a string is in a substrings. It is case/character insensitive
    //Possible bug: contains_substr("Land", "lan!!!!d") = true
    bool contains_substr(const string& field, const string& target) const;

    //Used for reading in stuff
    Book create_book(const string& s);

    void print_book(const Book& b) const;

    //prints a vector of given books
    void print_multi_books(const vector<Book>& b) const;

    //
    bool already_exists(const Book& b) const;
//Constructor   <--read from database.txt
    Database();
//Destructor
    ~Database();

//Add book
    void add_book();

//Find Book

    //Menus
    //Find menu will be in menu.h
    void find_string_menu();

    //Trim leading and trailing spaces
    int begin_index(const string& s) const;
    int end_index(const string& s) const;
    string trimmed(const string& s) const;

    //Search and print all possible matches
    
    void print_matches(const matches_t& matches) const;

    matches_t gen_title_matches(const string& t) const;
    void search_title() const;

    matches_t gen_author_matches(const string& a) const;
    void search_author() const;

    matches_t gen_genre_matches(const string& g) const;
    void search_genre() const;
    
    //TODO: create a return type for numbers too, so can use for delete

    vector<Book> search_year_exact() const;

    vector<Book> search_year_range() const;
    

    void search_year() const;

    vector<Book> search_rating_exact() const;
    vector<Book> search_rating_range() const;
    void search_rating() const;
    

//Delete book   
    //std::vector::erase(books.begin() + i);
    bool is_same(const Book& a, const Book& b) const;

    vector<int> deleted_indexes(const vector<Book>& b) const;
    int delete_answer() const;
    int delete_options() const;
    void trash_records(const vector<int>& indexes);
    void delete_records(const matches_t& matches);    
    
    void delete_by_title();
    void delete_by_author();
    void delete_by_genre();

    vector<Book> year_exact_no_print(const int& yr) const;
    vector<Book> year_range_no_print(const int& l1, const int& l2) const;
    void delete_by_year();

    vector<Book> rating_exact_no_print(const int& rt) const;
    vector<Book> rating_range_no_print(const int& l1, const int& l2) const;
    void delete_by_rating();

//List book 
    //Options/user input
    int alpha_options();
    int num_options();

    //Title
    void list_title_alpha();
    void list_title_rev_alpha();
    //Author
    void list_author_alpha();
    void list_author_rev_alpha();
    //Genre
    void list_genre_alpha();
    void list_genre_rev_alpha();
    //Year
    void list_year_ascending();
    void list_year_descending();
    //Rating
    void list_rating_ascending();
    void list_rating_descending();

//Override database.txt
    string convert_to_string(const Book& b) const;
    void write_to() const;
};
#endif