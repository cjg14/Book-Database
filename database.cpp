#include "database.h" 
using namespace std;

//Helpers
vector<string> Database::generate_substrs(const string& s) const {
    vector<string> v;
    for (int l = 1; l <= s.size(); l++) {
        string temp;
        for (int i = 0; i <= s.size() - l; i++) {
            int j = i + l - 1;
            for (int k = i; k <= j; k++){
                temp += s.at(k);
            }
            v.push_back(temp);
            temp.clear();
        }
    }
    return v;
}
//Checks to see if a target is a substring of a field
bool Database::contains_substr(const string& field, const string& target) const {
    vector<string> substrs = generate_substrs(field);
    sort(substrs.begin(), substrs.end());
    if (binary_search(substrs.begin(), substrs.end(), target)) {
        return true;
    } 
    return false;
}
//Print a singular book 
void Database::print_book(const Book& b) const {
    cout << "[\"" << b.get_title() << "\", ";
    cout << b.get_author() << ", ";
    cout << b.get_genre() << ", ";
    cout << b.get_year() << ", ";
    cout << b.get_rating() << " stars.]\n";
}
//Prints a vector of books
void Database::print_multi_books(const vector<Book>& b) const{
    for (Book bk : b) {
        print_book(bk);
    }
    cout << endl;
}

//Creates a book when string is read in
//NOTE: You cannot enter a blank field in database.txt 
    //Example: {} {} {} {} {} <-- this is NOT allowed, it will crash the program
Book Database::create_book(const string& s) {
    Book b;
    if (s.size() == 0) {
        return b;
    }
    string t;
    string a;
    string g;
    string yr;
    string rt;
    vector<int> v;
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == '}' || s.at(i) == '{') {
            v.push_back(i);
        }
    }
    for (int i = v.at(0) + 1; i < v.at(1); i++) {
        t += s.at(i);
    }
    b.set_title(trimmed(t));
    for (int i = v.at(2) + 1; i < v.at(3); i++) {
        a += s.at(i);
    }
    b.set_author(trimmed(a));
    for (int i = v.at(4) + 1; i < v.at(5); i++) {
        g += s.at(i);
    }
    b.set_genre(trimmed(g));
    for (int i = v.at(6) + 1; i < v.at(7); i++) {
        yr += s.at(i);
    }
    b.set_year(stoi(trimmed(yr)));
    for (int i = v.at(8) + 1; i < v.at(9); i++) {
        rt += s.at(i);
    }
    b.set_rating(stoi(trimmed(rt)));
    return b;
}
//[Initilizing database] with the pre-written records in database.txt
Database::Database() {
    ifstream in_file("database.txt");
    if (in_file.fail()) {
        cout << "Failed to open file.\n";
        exit(EXIT_FAILURE);
    }
    while (true) {
        string line;
        getline(in_file, line);
        if (in_file.fail()) {
            break;
        }
        Book b = create_book(line);
        books.push_back(b);
    }
}

//Destructor
Database::~Database() {}

//Checks to see if a book already exists in memory
bool Database::already_exists(const Book& b) const {
    for (Book bk : books) {
        if (is_same(bk, b)) {
            return true;
        }
    }
    return false;
}
//[Add book]
void Database::add_book() {
    Book b;
    b.enter_title();
    b.enter_author();
    b.enter_genre();
    b.enter_year();
    b.enter_rating();
    if (already_exists(b)) {
        print_book(b);
        cout << "\t^Already exists in database! It will not be added.\n";        
    } else {
        books.push_back(b);
        print_book(b);
        cout << "\t^Successfully added!\n"; 
    }
}

//[Find book]
//A structure to handle matches
struct matches_t {
    //Matches that are exact! (word by word)
    vector<Book> exact_matches;
    //Mathces that are similar or exact (target is a substring!)
    vector<Book> similar_matches;
};

//Prints the matches
void Database::print_matches(const matches_t& matches) const{
    cout << "You can search by: \n";
    cout << "Substring (1)\n";
    cout << "Exact (2)\n";
    cout << "Enter the number of your choice: ";
    string ans;
    cin >> ans;
    while (ans != "1" && ans != "2") {
        cout << endl;
        cout << "Please enter a valid answer:\n";
        cout << "Substring (1)\n";
        cout << "Exact (2)\n";
        cout << "Enter the number of your choice: ";
        cin >> ans;
        cin.get();
    }
    cout << endl;
    if (ans == "1") {
        if (matches.exact_matches.size() != 0) {
            print_multi_books(matches.exact_matches);
        }
        if (matches.similar_matches.size() != 0) {
            print_multi_books(matches.similar_matches);
        }
        if (matches.similar_matches.size() == 0 && 
            matches.exact_matches.size() == 0) {
            cout << "No matches were found.\n";
        }
    } else {
        if (matches.exact_matches.size() == 0) {
            cout << "No matches were found.\n";
        } else {
            print_multi_books(matches.exact_matches);
        }
    } 
    cin.get();
}
//Helper functions for trimmed()
int Database::begin_index(const string& s) const{
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
int Database::end_index(const string& s) const{
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
//Trims a string to remove leading or trailing spaces
string Database::trimmed(const string& s) const{
    int begin = begin_index(s);
    int limit2 = end_index(s);
    return s.substr(begin, limit2 - begin + 1);
}

//Generates search macthes based on title
matches_t Database::gen_title_matches(const string& t) const{
    matches_t matches;
    for (Book b : books) {
        //if user input matches exactly with title (character by character)
        if (t == b.get_title()) {
            matches.exact_matches.push_back(b);
        //otherwise, checks if input is part of a substring of the title
        } else {
            if (contains_substr(b.get_title(), t)) {
                matches.similar_matches.push_back(b);
            }
        }
    }
    return matches;
}
void Database::search_title() const{
    cout << "\nSearch record by [Title]\n\n";
    cout << "Enter a title: ";
    string t;
    getline(cin, t);
    matches_t matches = gen_title_matches(trimmed(t));
    cout << endl;
    print_matches(matches);
}

//Generates matches based on author's name
matches_t Database::gen_author_matches(const string& a) const{
    matches_t matches;
    for (Book b : books) {
        //if user input matches exactly (character by character)
        if (a == b.get_author()) {
            matches.exact_matches.push_back(b);
        //otherwise, checks if input is part of a substring of the title
        } else {
            if (contains_substr(b.get_author(), a)) {
                matches.similar_matches.push_back(b);
            }
        }
    }
    return matches;
}

void Database::search_author() const{
    cout << "\nSearch record by an [Author's Name]\n\n";
    cout << "Enter author's name: ";
    string name;
    getline(cin, name);
    matches_t matches = gen_author_matches(trimmed(name));
    cout << endl;
    print_matches(matches);
}

//Generates matches based on genre
matches_t Database::gen_genre_matches(const string& g) const{
    matches_t matches;
    for (Book b : books) {
        //if user input matches exactly (character by character)
        if (g == b.get_genre()) {
            matches.exact_matches.push_back(b);
        //otherwise, checks if input is part of a substring of the title
        } else {
            if (contains_substr(b.get_genre(), g)) {
                matches.similar_matches.push_back(b);
            }
        }
    }   
    return matches;
}

void Database::search_genre() const{
    cout << "\nSearch record by [Genre]\n\n";
    cout << "Enter genre: ";
    string g;
    getline(cin, g);
    matches_t matches = gen_genre_matches(trimmed(g));
    cout << endl;
    print_matches(matches);
}

//Generates matches based on searching the exact year
vector<Book> Database::search_year_exact() const{
    cout << "Enter the year: ";
    int yr = 0;
    cin >> yr;
    vector<Book> matches;
    for (Book b : books) {
        if (yr == b.get_year()) {
            matches.push_back(b);
        }
    }
    cout << endl;
    if (matches.size() == 0) {
        cout << "No matches were found in year " << yr << endl;
    } else { 
        for (Book bk : matches) {
            print_book(bk);
        }
    }
    return matches;
}

vector<Book> Database::year_exact_no_print(const int& yr) const{
    vector<Book> matches;
    for (Book b : books) {
        if (yr == b.get_year()) {
            matches.push_back(b);
        }
    }
    return matches;
}
//Generates matches but given a range
vector<Book> Database::search_year_range() const{
    cout << "Enter first limit: ";
    int limit1 = 0;
    cin >> limit1;
    cout << "Enter second limit: ";
    int limit2 = 0;
    cin >> limit2;
    vector<Book> matches;
    if (limit1 <= limit2) {
        for (Book b : books) {
            if ((b.get_year() >= limit1) && (b.get_year() <= limit2)) {
                matches.push_back(b);
            }
        }
    } else {
        for (Book b : books) {
            if ((b.get_year() >= limit2) && (b.get_year() <= limit1)) {
                matches.push_back(b);
            }
        }
    }
    cout << endl;
    if (matches.size() == 0) {
        if (limit1 < limit2) {
            cout << "No matches were found between ";
            cout << "year " << limit1;
            cout << " and year " << limit2 << endl;
        } else if (limit1 > limit2) {
            cout << "No matches were found between ";
            cout << "year " << limit2;
            cout << " and year " << limit1 << endl;
        } else {
            cout << "No matches found in year " << limit1 << endl; 
        }
    } else {
        sort(matches.begin(), matches.end(), asc_year);
        for (Book b : matches) {
            print_book(b);
        }
    }
    return matches;
}
vector<Book> Database::year_range_no_print(const int& limit1, const int& limit2) const{
    vector<Book> matches;
    if (limit1 <= limit2) {
        for (Book b : books) {
            if ((b.get_year() >= limit1) && (b.get_year() <= limit2)) {
                matches.push_back(b);
            }
        }
    } else {
        for (Book b : books) {
            if ((b.get_year() >= limit2) && (b.get_year() <= limit1)) {
                matches.push_back(b);
            }
        }
    }
    return matches;
}
void Database::search_year() const{
    cout << "\nSearch record by [Year] of publication\n\n";
    cout << "You can search by: \n";
    cout << "Range of years (1)\n";
    cout << "Exact year (2)\n";
    cout << "Enter the number of your choice: ";
    string ans;
    cin >> ans;
    while (ans != "1" && ans != "2") {
        cout << endl;
        cout << "Please enter a valid answer:\n";
        cout << "Range of years (1)\n";
        cout << "Exact year (2)\n";
        cout << "Enter the number of your choice: ";
        cin >> ans;
        cin.get();
    } 
    cout << endl;
    if (ans == "1") {
        vector<Book> bks = search_year_range();
    } else {
        vector<Book> bks = search_year_exact();
    }
}
vector<Book> Database::search_rating_exact() const{
    cout << "Enter the rating: ";
    int r = 0;
    cin >> r;
    vector<Book> matches;
    for (Book b : books) {
        if (r == b.get_rating()) {
            matches.push_back(b);
        }
    }
    cout << endl;
    if (matches.size() == 0) {
        cout << "No matches were found. \n";
    } else { 
        for (Book bk : matches) {
            print_book(bk);
        }
    }
    return matches;
}
vector<Book> Database::rating_exact_no_print(const int& r) const {
    vector<Book> matches;
    for (Book b : books) {
        if (r == b.get_rating()) {
            matches.push_back(b);
        }
    }
    return matches;
}
vector<Book> Database::search_rating_range() const{
    cout << "Enter first limit: ";
    int limit1 = 0;
    cin >> limit1;
    cout << "Enter second limit: ";
    int limit2 = 0;
    cin >> limit2;
    vector<Book> matches;
    if (limit1 <= limit2) {
        for (Book b : books) {
            if ((b.get_rating() >= limit1) && (b.get_rating() <= limit2)) {
                matches.push_back(b);
            }
        }
    } else {
        for (Book b : books) {
            if ((b.get_rating() >= limit2) && (b.get_rating() <= limit1)) {
                matches.push_back(b);
            }  
        }
    }
    cout << endl;
    if (matches.size() == 0) {
        if (limit1 < limit2) {
            cout << "No matches were found between ";
            cout << limit1 << " stars and ";
            cout << limit2  << " stars\n";
        } else if (limit1 > limit2) {
            cout << "No matches were found between ";
            cout << limit2 << " stars and ";
            cout << limit1 << " stars\n";
        } else {
            cout << "No matches were found for " << limit1 << " stars\n"; 
        }
    } else {
        sort(matches.begin(), matches.end(), asc_rating);
        for (Book b : matches) {
            print_book(b);
        }
    }
    return matches;
}
vector<Book> Database::rating_range_no_print(const int& limit1, const int& limit2) const{
    vector<Book> matches;
    if (limit1 <= limit2) {
        for (Book b : books) {
            if ((b.get_rating() >= limit1) && (b.get_rating() <= limit2)) {
                matches.push_back(b);
            }
        }
    } else {
        for (Book b : books) {
            if ((b.get_rating() >= limit2) && (b.get_rating() <= limit1)) {
                matches.push_back(b);
            }  
        }
    }
    return matches;
}
void Database::search_rating() const{
    cout << "\nSearch record by [Rating]\n\n";
    cout << "You can search by: \n";
    cout << "Range of ratings (1)\n";
    cout << "Exact rating (2)\n";
    cout << "Enter the number of your choice: ";
    string ans;
    cin >> ans;
    while (ans != "1" && ans != "2") {
        cout << endl;
        cout << "Please enter valid answer:\n";
        cout << "Range of ratings (1)\n";
        cout << "Exact rating (2)\n";
        cout << "Enter the number of your choice: ";
        cin >> ans;
        cin.get();
    }
    cout << endl;
    if (ans == "1") {
        vector<Book> bks = search_rating_range();
    } else {
        vector<Book> bks = search_rating_exact();
    }
}
//[Deleting]
bool Database::is_same(const Book& a, const Book& b) const{
    if ((a.get_title() == b.get_title())
            && (a.get_author() == b.get_author())
            && (a.get_genre() == b.get_genre())
            && (a.get_year() == b.get_year())
            && (a.get_rating() == b.get_rating())) {
        return true;
    }
    return false;
}
//Asks user if they want to delete the listed records
int Database::delete_answer() const{
    cout << "Yes (1)\n";
    cout << "No (2)\n";
    cout << "Enter the number of your choice: ";
    string choice;
    cin >> choice;
    while (choice != "1" && choice != "2") {
        cout << "Please enter a valid choice. \n";
        cout << "Yes (1)\n";
        cout << "No (2)\n";        
        cout << "Enter the number of your choice: ";
        cin >> choice;
    }
    return stoi(choice);
}
//Lists the possibilities user can search to delete
int Database::delete_options() const{
    cout << "You can search by: \n";
    cout << "Substring (1)\n";
    cout << "Exact (2)\n";
    cout << "Enter the number of your choice: ";
    string ans;
    cin >> ans;
    while (ans != "1" && ans != "2") {
        cout << endl;
        cout << "Please enter a valid answer:\n";
        cout << "Substring (1)\n";
        cout << "Exact (2)\n";
        cout << "Enter the number of your choice: ";
        cin >> ans;
    }
    return stoi(ans);
}
//A vector of indexes of all the deleted items
vector<int> Database::deleted_indexes(const vector<Book>& b) const {
    vector<int> indexes;
    vector<Book> copy_of_memory = books;
    for (Book bk : b) {
        for (int i = 0; i < copy_of_memory.size(); i++) {
            if (is_same(bk,copy_of_memory.at(i))) {
                indexes.push_back(i);
            }
        }
    }
    return indexes;
}
//Deletes the records
void Database::trash_records(const vector<int>& indexes) {
    //for every index of the record to be deleted, erase them from memory
    for (int i : indexes) {
        books.erase(books.begin() + i);
    }
}

void Database::delete_records(const matches_t& matches) {
    int option = delete_options();
    cout << endl;
    vector<int> indexes;
    if (option == 1) {
        if (matches.exact_matches.size() == 0 && matches.similar_matches.size() == 0) {
            cout << "No matches were found\n";
        } else {
            vector<Book> exact = matches.exact_matches;
            vector<Book> similar = matches.similar_matches;
            cout << "Are you sure you want to delete the following records?\n";
            if (exact.size() != 0 && similar.size() != 0) {
                print_multi_books(exact);
                print_multi_books(similar);
                vector<int> list2 = deleted_indexes(similar);
                vector<int> list1 = deleted_indexes(exact);
                list1.insert(list1.end(), list2.begin(), list2.end());
                indexes = list1;
            } else if (exact.size() == 0 && similar.size() != 0) {
                print_multi_books(similar);
                indexes = deleted_indexes(similar);
            } else if (exact.size() != 0 && similar.size() == 0) {
                print_multi_books(exact);
                indexes = deleted_indexes(exact);
            } else {
                cout << "No matches were found\n";
            }
            cout << endl;
            int ans = delete_answer();
            if (ans == 1) {
                trash_records(indexes);
                cout << "\nThe chosen records have been deleted.\n\n";
            } 
        }
    } else {
        if (matches.exact_matches.size() == 0) {
            cout << "No matches were found.\n";
        } else {
            cout << "Are you sure you want to delete the following records?\n";
            print_multi_books(matches.exact_matches);
            cout << endl;
            int ans = delete_answer();
            if (ans == 1) {
                indexes = deleted_indexes(matches.exact_matches);
                trash_records(indexes);
                cout << "\nThe chosen records have been deleted.\n\n";
            }
        }   
    }
    cin.get();
}
void Database::delete_by_title() {
    cout << "\nDelete by [Title]\n";
    cout << "Enter the title: ";
    string t;
    getline(cin, t);
    matches_t m = gen_title_matches(t);
    delete_records(m);
}
void Database::delete_by_author() {
    cout << "\nDelete by [Author]\n";
    cout << "Enter the author's name: ";
    string t;
    getline(cin, t);
    matches_t m = gen_author_matches(t);
    delete_records(m); 
}
void Database::delete_by_genre() {
    cout << "\nDelete by [Genre]\n";
    cout << "Enter the genre: ";
    string t;
    getline(cin, t);
    matches_t m = gen_genre_matches(t);
    delete_records(m);  
}
void Database::delete_by_year() {
    cout << "\nDelete record by [Year] of publication\n\n";
    cout << "You can search by: \n";
    cout << "Range of years (1)\n";
    cout << "Exact year (2)\n";
    cout << "Enter the number of your choice: ";
    string ans;
    cin >> ans;
    while (ans != "1" && ans != "2") {
        cout << endl;
        cout << "Please enter a valid answer:\n";
        cout << "Range of years (1)\n";
        cout << "Exact year (2)\n";
        cout << "Enter the number of your choice: ";
        cin >> ans;
        cin.get();
    } 
    vector<Book> bks;
    if (ans == "1") {
        cout << "Enter first limit: ";
        int limit1 = 0;
        cin >> limit1;
        cout << "Enter second limit: ";
        int limit2 = 0;
        cin >> limit2;
        bks = year_range_no_print(limit1, limit2);
        if (bks.size() != 0) {
            cout << "Are you sure you want to delete the following records?\n\n";
            print_multi_books(bks);
            int ans = delete_answer();
            if (ans == 1) {
                vector<int> indexes = deleted_indexes(bks);
                trash_records(indexes);
                cout << "The chosen records have been deleted.\n";
            }
        } else {
            cout << "No records were found.\n";
        }
    } else {
        cout << "Enter the year: ";
        int yr = 0;
        cin >> yr;
        bks = year_exact_no_print(yr);
        if (bks.size() != 0) {
            cout << "Are you sure you want to delete the following records?\n\n";
            print_multi_books(bks);
            int ans = delete_answer();
            if (ans == 1) {
                vector<int> indexes = deleted_indexes(bks);
                trash_records(indexes);
                cout << "The chosen records have been deleted.\n";
            }
        } else {
            cout << "No records were found.\n";
        }
    }
}
void Database::delete_by_rating() {
    cout << "\nDelete record by [Genre]\n\n";
    cout << "You can search by: \n";
    cout << "Range of ratings (1)\n";
    cout << "Exact rating (2)\n";
    cout << "Enter the number of your choice: ";
    string ans;
    cin >> ans;
    while (ans != "1" && ans != "2") {
        cout << endl;
        cout << "Please enter a valid answer:\n";
        cout << "Range of ratings (1)\n";
        cout << "Exact rating (2)\n";
        cout << "Enter the number of your choice: ";
        cin >> ans;
        cin.get();
    } 
    vector<Book> bks;
    if (ans == "1") {
        cout << "Enter first limit: ";
        int limit1 = 0;
        cin >> limit1;
        cout << "Enter second limit: ";
        int limit2 = 0;
        cin >> limit2;
        bks = rating_range_no_print(limit1, limit2);
        if (bks.size() != 0) {
            cout << "Are you sure you want to delete the following records?\n\n";
            print_multi_books(bks);
            int ans = delete_answer();
            if (ans == 1) {
                vector<int> indexes = deleted_indexes(bks);
                trash_records(indexes);
                cout << "The chosen records have been deleted.\n";
            }
        } else {
            cout << "No records were found.\n";
        }
    } else {
        cout << "Enter the rating: ";
        int r = 0;
        cin >> r;
        bks = rating_exact_no_print(r);
        if (bks.size() != 0) {
            cout << "Are you sure you want to delete the following records?\n\n";
            print_multi_books(bks);
            int ans = delete_answer();
            if (ans == 1) {
                vector<int> indexes = deleted_indexes(bks);
                trash_records(indexes);
                cout << "The chosen records have been deleted.\n";
            }
        } else {
            cout << "No records were found.\n";
        }
    }
}


//[Listing]
int Database::alpha_options() {
    cout << "Choose the listing format\n";
    cout << "List: \n";
    cout << "Alphabetically (1) \n";
    cout << "Reverse Alphabetically (2) \n";
    cout << "Back to previous menu (0) \n\n";
    cout << "Enter the letter of your choice: ";
    int i = 0;
    cin >> i;
    return i;
}
int Database::num_options() {
    cout << "Choose the listing format\n";
    cout << "List: \n";
    cout << "Ascending Order (1) \n";
    cout << "Descending Order (2) \n";
    cout << "Back to previous menu (0) \n\n";
    cout << "Enter the letter of your choice: ";
    int i = 0;
    cin >> i;
    return i;
}

//Lowers every character in a string to lowercase
string to_lower(const string& s) {
    string str;
    for (char c : s) {
        str += tolower(c);
    }
    return str;
}
//Comparators
bool alpha_title(Book a, Book b) {
    vector<string> v = {a.get_title(), b.get_title()};
    sort(v.begin(), v.end());
    if (v.at(0) == a.get_title()) {
        return to_lower(a.get_title()) <= to_lower(b.get_title());
    }
    return to_lower(a.get_title()) < to_lower(b.get_title());
}
bool rev_alpha_title(Book a, Book b) {
    vector<string> v = {a.get_title(), b.get_title()};
    sort(v.begin(), v.end());
    if (v.at(0) == a.get_title()) {
        return to_lower(a.get_title()) > to_lower(b.get_title());
    }
    return to_lower(a.get_title()) >= to_lower(b.get_title()); 
}
bool alpha_author(Book a, Book b) {
    vector<string> v = {a.get_author(), b.get_author()};
    sort(v.begin(), v.end());
    if (v.at(0) == a.get_author()) {
        return to_lower(a.get_author()) <= to_lower(b.get_author());
    }
    return to_lower(a.get_author()) < to_lower(b.get_author());
}
bool rev_alpha_author(Book a, Book b) {
    vector<string> v = {a.get_author(), b.get_author()};
    sort(v.begin(), v.end());
    if (v.at(0) == a.get_author()) {
        return to_lower(a.get_author()) > to_lower(b.get_author());
    }
    return to_lower(a.get_author()) >= to_lower(b.get_author()); 
}
bool alpha_genre(Book a, Book b) {
    vector<string> v = {a.get_genre(), b.get_genre()};
    sort(v.begin(), v.end());
    if (v.at(0) == a.get_genre()) {
        return to_lower(a.get_genre()) <= to_lower(b.get_genre());
    }
    return to_lower(a.get_genre()) < to_lower(b.get_genre());
}
bool rev_alpha_genre(Book a, Book b) {
    vector<string> v = {a.get_genre(), b.get_genre()};
    sort(v.begin(), v.end());
    if (v.at(0) == a.get_genre()) {
        return to_lower(a.get_genre()) > to_lower(b.get_genre());
    }
    return to_lower(a.get_genre()) >= to_lower(b.get_genre()); 
} 
bool asc_year(Book a, Book b) {
    return (a.get_year() < b.get_year());
}
bool desc_year(Book a, Book b) {
    return (a.get_year() > b.get_year());
}
bool asc_rating(Book a, Book b) {
    return (a.get_rating() < b.get_rating());
}
bool desc_rating(Book a, Book b) {
    return (a.get_rating() > b.get_rating());
}

// Listing functions
void Database::list_title_alpha() {
    cout << "\nListing by title alphabetically:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), alpha_title);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_title_rev_alpha() {
    cout << "\nListing by title reverse-alphabetically:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), rev_alpha_title);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_author_alpha() {
    cout << "\nListing by author alphabetically:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), alpha_author);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_author_rev_alpha() {
    cout << "\nListing by author reverse-alphabetically:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), rev_alpha_author);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_genre_alpha() {
    cout << "\nListing by genre alphabetically:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), alpha_genre);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_genre_rev_alpha() {
    cout << "\nListing by genre reverse-alphabetically:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), rev_alpha_genre);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_year_ascending() {
    cout << "\nListing by year ascending:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), asc_year);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_year_descending() {
    cout << "\nListing by year descending:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), desc_year);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_rating_ascending() {
    cout << "\nListing by rating ascending:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), asc_rating);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}
void Database::list_rating_descending() {
    cout << "\nListing by rating descending:\n\n";
    vector<Book> copy = books;
    sort(copy.begin(), copy.end(), desc_rating);
    for (int i = 0; i < copy.size(); i++) {
        print_book(copy.at(i));
    }
}

//Converts a book record to a string
string Database::convert_to_string(const Book& b) const {
    string t;
    for (char c: b.get_title()) {
        t += c;
    }
    t = "{" + t + "}";

    string a;
    for (char c : b.get_author()) {
        a += c;
    }
    a = "{" + a + "}";

    string g;
    for (char c : b.get_genre()) {
        g += c;
    }
    g = "{" + g + "}";

    string y = "{" + to_string(b.get_year()) + "}";
    string r = "{" + to_string(b.get_rating()) + "}";

    string s = t + " " + a + " " + g + " " + y + " " + r;
    return s;

}
//Overides database.txt with the updated memory
void Database::write_to() const {
    ofstream out_file("database.txt");
    if (out_file.fail()) {
        cout << "Unable to create file.\n";
        exit(EXIT_FAILURE);
    }
    for (Book b : books) {
        string s = convert_to_string(b);
        out_file << s << endl;
    }
}
