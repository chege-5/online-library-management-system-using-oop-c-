#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

class Book
 {
private:
    string title;
    string author;
    bool available;
    int rating;

public:
    Book(string title, string author) : title(title), author(author), available(true), rating(0)
     {}

    string getTitle()
     const
      {
        return title;
    }

    string getAuthor()
     const
      {
        return author;
    }

    bool isAvailable()
     const
      {
        return available;
    }

    void setAvailable(bool availability)
     {
        available = availability;
    }

    int getRating()
     const
      {
        return rating;
    }

    void setRating(int newRating)
     {
        rating = newRating;
    }
};

class Library
 {
private:
    vector<Book> books;

public:
    void addBook(const Book& book)
     {
        books.push_back(book);
    }

    vector<Book> searchBooksByTitle(const string& title)
     const 
     {
        vector<Book> result;
        for (size_t i = 0; i < books.size(); i++)
         {
            if (books[i].getTitle() == title)
             {
                result.push_back(books[i]);
            }
        }
        return result;
    }

    void borrowBook(Book& book)
     {
        if (book.isAvailable())
         {
            book.setAvailable(false);
            cout << "Book \"" << book.getTitle() << "\" by " << book.getAuthor() << " borrowed successfully." << endl;

            time_t now = time(0);
            tm* date = localtime(&now);
            date->tm_mday += 14;

            cout << "Please return the book by=" << asctime(date) << endl;
        }
         else
         {
            cout << "Book \"" << book.getTitle() << "\" by " << book.getAuthor() << " is not available for borrowing." << endl;
        }
    }

    void listAvailableBooks() 
    const
     {
        cout << "Available Books:" << endl;
        for (size_t i = 0; i < books.size(); i++)
         {
            if (books[i].isAvailable())
             {
                cout << "- " << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
            }
        }
    }
};

int main()
 {
    Library library;

    library.addBook(Book("oop1", "Gerorge"));
    library.addBook(Book("oop2", "Jimmy"));
    library.addBook(Book("oop3", "Simon"));
    library.addBook(Book("oop4", "Peter"));
    library.addBook(Book("oop5", "Amina"));
    library.addBook(Book("oop6", "Aurelius"));
    library.addBook(Book("oop7", "Max"));
    library.addBook(Book("oop8", "John"));

    cout << "WELCOME TO ZETECH ONLINE LIBRARY MANAGEMENT" << endl;
    cout << "Have you ever borrowed a book before? (yes/no)="<< endl;
    string response;
    getline(cin, response);

    if (response == "no")
     {
        cout << "Welcome! Here are the available books in the library:" << endl;
        library.listAvailableBooks();

        cout << "Please enter the title of the book you want to borrow="<<endl;
        string userBookTitle;
        getline(cin, userBookTitle);

        vector<Book> userBooks = library.searchBooksByTitle(userBookTitle);
        if (!userBooks.empty())
         {
            Book& userBook = userBooks[0];
            if (userBook.isAvailable()) 
            {
                library.borrowBook(userBook);

                cout << "Thank you for your continued support! Welcome back again." << endl;
            } 
            else
             {
                cout << "Book \"" << userBook.getTitle() << "\" by " << userBook.getAuthor() << " is not available for borrowing." << endl;
            }
        } 
        
        else
         {
            cout << "Book \"" << userBookTitle << "\" not found in the library." << endl;
        }
    } 
    else if (response == "yes") {
        cout << "Please enter the title of the book you previously borrowed: ";
        string previousBookTitle;
        getline(cin, previousBookTitle);

        cout << "Please enter the day you borrowed the book (1-31)="<<endl;
        int previousBorrowDay;
        cin >> previousBorrowDay;

        cout << "Please enter the day you plan to return the book (1-31)="<<endl;
        int returnDay;
        cin >> returnDay;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        time_t now = time(0);
        tm* date = localtime(&now);
        int currentDay = date->tm_mday;

        if (returnDay < previousBorrowDay)
         {
            cout << "Invalid return date. Please try again." << endl;
            return 0;
        }

        int borrowedDays = returnDay - previousBorrowDay;
        int extraDays = borrowedDays - 14;
        int extraCharge = extraDays * 20;

        if (extraDays > 0)
         {
            cout << "You have exceeded the return period by " << extraDays << " days." << endl;
            cout << "Please pay an extra charge of $" << extraCharge << "." << endl;
        } 
        else
         {
            cout << "Thank you for returning the book on time." << endl;
        }

        cout << "Please rate the book \"" << previousBookTitle << "\" (1-5)="<<endl;
        int rating;
        cin >> rating;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (rating < 3) 
        {
            cout << "Ouch! That's not good. Please provide a review "<<endl;
            string review;
            getline(cin, review);

            cout << "Thank you for your feedback.." << endl;

            cout << "Here are some book recommendations for you=" << endl;
            for (size_t i = 0; i < library.searchBooksByTitle("Title 4").size(); i++)
             {
                Book& recommendation = library.searchBooksByTitle("Title 4")[i];
                cout << "- " << recommendation.getTitle() << " by " << recommendation.getAuthor() << endl;
            }
        } 
        else
         {
            cout << "Thank you for your rating!" << endl;

            cout << "Here are some book recommendations for you=" << endl;
            for (size_t i = 0; i < library.searchBooksByTitle("Title 1").size(); i++)
             {
                Book& recommendation = library.searchBooksByTitle("Title 1")[i];
                cout << "- " << recommendation.getTitle() << " by " << recommendation.getAuthor() << endl;
            }
        }

        cout << "Please enter the title of the book you want to borrow="<<endl;
        string userBookTitle;
        getline(cin, userBookTitle);

        vector<Book> userBooks = library.searchBooksByTitle(userBookTitle);
        if (!userBooks.empty())
         {
            Book& userBook = userBooks[0];
            if (userBook.isAvailable())
             {
                library.borrowBook(userBook);

                cout << "Thank you for your continued support! Welcome back again." << endl;
            } 
            else
             {
                cout << "Book \"" << userBook.getTitle() << "\" by " << userBook.getAuthor() << " is not available for borrowing." << endl;
            }
        } 
        else
         {
            cout << "Book \"" << userBookTitle << "\" not found in the library." << endl;
        }
    }
     else 
     {
        cout << "Invalid response. Please try again." << endl;
    }

    return 0;
}