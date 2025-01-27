#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}
};
class Borrower {
public:
    string name;
    string borrowedISBN;
    time_t borrowDate;

    Borrower(string n, string isbn, time_t date) : name(n), borrowedISBN(isbn), borrowDate(date) {}
};
class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    Book* findBookByISBN(const string& isbn) {
        for (auto& book : books) {
            if (book.isbn == isbn) return &book;
        }
        return nullptr;
    }
    double calculateFine(time_t borrowDate) {
        const int finePerDay = 2; // $2 per overdue day
        const int maxBorrowDays = 14;

        time_t currentTime = time(0);
        int daysElapsed = (currentTime - borrowDate) / (60 * 60 * 24);
        int overdueDays = max(0, daysElapsed - maxBorrowDays);

        return overdueDays * finePerDay;
    }

public:
    void addBook(const string& title, const string& author, const string& isbn) {
        books.emplace_back(title, author, isbn);
        cout << "Book added successfully!\n";
    }
    void searchBooks(const string& query) {
        cout << "Search Results:\n";
        for (const auto& book : books) {
            if (book.title.find(query) != string::npos || 
                book.author.find(query) != string::npos || 
                book.isbn == query) {
                cout << "Title: " << book.title << ", Author: " << book.author
                     << ", ISBN: " << book.isbn
                     << ", Available: " << (book.isAvailable ? "Yes" : "No") << "\n";
            }
        }
    }
    void checkoutBook(const string& isbn, const string& borrowerName) {
        Book* book = findBookByISBN(isbn);
        if (book && book->isAvailable) {
            book->isAvailable = false;
            time_t borrowDate = time(0);
            borrowers.emplace_back(borrowerName, isbn, borrowDate);
            cout << "Book checked out successfully to " << borrowerName << "!\n";
        } else {
            cout << "Book is not available or does not exist.\n";
        }
    }
    void returnBook(const string& isbn) {
        for (auto it = borrowers.begin(); it != borrowers.end(); ++it) {
            if (it->borrowedISBN == isbn) {
                Book* book = findBookByISBN(isbn);
                if (book) book->isAvailable = true;

                double fine = calculateFine(it->borrowDate);
                if (fine > 0) {
                    cout << "Book returned. Fine: $" << fixed << setprecision(2) << fine << "\n";
                } else {
                    cout << "Book returned successfully with no fine.\n";
                }
                borrowers.erase(it);
                return;
            }
        }
        cout << "No record of this book being borrowed.\n";
    }
};
int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Books\n";
        cout << "3. Checkout Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string title, author, isbn;
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            library.addBook(title, author, isbn);
            break;
        }
        case 2: {
            string query;
            cout << "Enter title, author, or ISBN to search: ";
            getline(cin, query);
            library.searchBooks(query);
            break;
        }
        case 3: {
            string isbn, borrowerName;
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            cout << "Enter borrower name: ";
            getline(cin, borrowerName);
            library.checkoutBook(isbn, borrowerName);
            break;
        }
        case 4: {
            string isbn;
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            library.returnBook(isbn);
            break;
        }
        case 5:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
