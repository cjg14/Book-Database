#include "book.h"
using namespace std;
//Definitions for class "Book"

//Constructor
Book::Book() {} 
Book::~Book() {}

bool Book::has_curl_brack(const string& s) {
    for (char c : s) {
        if (c == '}' || c == '{') {
            return true;
        }
    }
    return false;
}
bool Book::is_integer(const string& s) {
    if (s.size() == 0) {
        return false;
    }
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
int Book::begin_index(const string& s) {
    int index = 0;
    for (int i = 0; i < s.size(); i++) {
        if (isspace(s.at(i))) {
            index++;
        } else {
            break;
        }
    }
    return index;
}
int Book::end_index(const string& s) {
    int index = s.size() - 1;
    for (int i = s.size() - 1; i > 0; i--) {
        if (isspace(s.at(i))) {
            index--;
        } else {
            break;
        }
    }
    return index;
}
string Book::trimmed(const string& s) {
    int begin = begin_index(s);
    int limit2 = end_index(s);
    return s.substr(begin, limit2 - begin + 1);
}

void Book::set_title(const string& t) {
    title = t;
}
void Book::set_author(const string& a) {
    author = a;
}
void Book::set_genre(const string& g) {
    genre = g;
}
void Book::set_year(const int& y) {
    pub_year = y;
}
void Book::set_rating(const int& r) {
    rating = r;
}

//User input
void Book::enter_title() {
    string nm;
    cout << "Enter Book Title: ";
    getline(cin, nm); 
    while (has_curl_brack(nm)) {
        cout << "Cannot include \"{\" or \"}\": ";
        getline(cin, nm);
    }
    set_title(trimmed(nm));
}
void Book::enter_author() {
    string auth;
    cout << "Enter Book Author: ";
    getline(cin, auth);
    while (has_curl_brack(auth)) {
        cout << "Cannot include \"{\" or \"}\": ";
        getline(cin, auth); 
    }
    set_author(trimmed(auth));
    
}
void Book::enter_genre() {
    string gen;
    cout << "Enter Book Genre: ";
    getline(cin, gen);
    while (has_curl_brack(gen)) {
        cout << "Cannot include \"{\" or \"}\": ";
        getline(cin, gen);
    }
    set_genre(trimmed(gen));
}

void Book::enter_rating() {
    cout << "Enter the rating (rating is subjective): ";
    string rev;
    getline(cin, rev);
    while (!is_integer(trimmed(rev))) {
        cout << "Please enter a valid rating: ";
        getline(cin, rev);
    } 
    set_rating(stoi(trimmed(rev)));
    
}

void Book::enter_year() {
    string yr;
    cout << "Enter the year of publication: ";
    getline(cin, yr);
    while(!is_integer(trimmed(yr))) {
        cout << "Please enter a valid year: ";
        getline(cin, yr);
    } 
    set_year(stoi(trimmed(yr)));
}

//Getters
string Book::get_title() const{
    return title;
}
string Book::get_author() const{
    return author;
}
string Book::get_genre() const {
    return genre;
}
int Book::get_year() const{
    return pub_year;
}
int Book::get_rating() const {
    return rating;
}