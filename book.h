#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>


using namespace std;

int begin_index(const string& s);
int end_index(const string& s);
string trimmed(const string& s);

class Book {
private:
    string title;
    string author;
    string genre;
    int pub_year;
    int rating; //review out of five stars (invalid input: anything that's less than 0 or more than 5)  
public:
    //Constructor 
    Book(); 
    ~Book();

    //Helpers:
    bool is_integer(const string& s);
    int begin_index(const string& s);
    int end_index(const string& s);
    bool has_curl_brack(const string& s);
    string trimmed(const string& s);

    //Setting fields
    void set_title(const string& t);
    void set_author(const string& a);
    void set_genre(const string& g);
    void set_year(const int& y);
    void set_rating(const int& r);

    //User input
    void enter_title();      
    void enter_author();
    void enter_genre();
    void enter_year();
    void enter_rating();

    //Getters
    string get_title() const;
    string get_author() const;
    string get_genre() const;
    int get_year() const;
    int get_rating() const;
};

/*
    Seperate Compilation: March 1, March 3
*/

#endif