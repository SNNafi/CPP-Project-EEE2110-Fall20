//
// Created by Shahriar Nasim Nafi on 30/9/21.
//
// NOT COMPLETED


#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class Book {
public:
    string title;
    int price;
    int borrowStatus = false;
    int lastDateOfReturn = 0;
    int borrowedStudentId = 0;
};

class BookRequest {
public:
    string bookName;
    int studentId;
};


class BookReturnRequest {
public:
    string bookName;
    int studentId;
    int returnDate;
};

class Fund {
public:
    // 1. Late Return, 2.Damage / Loss 3,New Account Request
    int fundType;
    double value;
};


class BookDamageRequest {
public:
    string bookName;
    int studentId;

};

class Student {
public:
    int id;
    string password;
    int totalFault = 0;

    void placeIssueRequest(vector<BookRequest> &bookRequests) {
        BookRequest bookRequest;
        cout << "Enter book name: ";
        cin >> bookRequest.bookName;
        bookRequest.studentId = id;
        bookRequests.push_back(bookRequest);
    }

    void bookReturnRequest(vector<BookReturnRequest> &bookReturnRequests, int returnDate) {
        BookReturnRequest bookReturnRequest;
        cout << "Enter book name: ";
        cin >> bookReturnRequest.bookName;
        bookReturnRequest.studentId = id;
        bookReturnRequest.returnDate = returnDate;
        bookReturnRequests.push_back(bookReturnRequest);
    }

    void placeDamageRequst(vector<BookDamageRequest> &damageRequests) {
        BookDamageRequest damageRequest;
        cout << "Enter book name: ";
        cin >> damageRequest.bookName;
        damageRequest.studentId = id;
        damageRequests.push_back(damageRequest);
    }
};


class Librarian {
public:
    vector<Student> students;
    vector<Book> books;
    vector<BookRequest> bookRequests;
    vector<BookReturnRequest> bookReturnRequests;
    vector<BookDamageRequest> damageRequests;
    vector<Fund> funds;

    void addNewBook() {
        Book book;
        cout << "Enter book name ";
        cin >> book.title;
        cout << "Enter book price: ";
        cin >> book.price;
        books.push_back(book);
    }

    void viewAllBooks() {
        for (int i = 1; i < books.size(); i++) {
            Book book = books[i];
            cout << "Book name: " << book.title << endl;
            cout << "Book price: " << book.price << endl;
            cout << "Book borrow status: " << book.borrowStatus << endl;
            if (book.borrowStatus) {
                cout << "Borrowed by student id: " << book.borrowedStudentId << endl;
                cout << "Last return date: " << book.lastDateOfReturn << endl;
            }
        }
    }

    void addNewAccount() {
        Student student;
        cout << "Enter student id: ";
        cin >> student.id;
        cout << "Enter student password: ";
        cin >> student.password;
        students.push_back(student);
    }

    void deleteAccount(int studentId) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].id == studentId) {
                students.erase(students.begin() + i);
                break;
            }
        }
    }

    void showBookRequests() {
        for (int i = 0; i < bookRequests.size(); i++) {
            cout << "Book " << bookRequests[i].bookName << "requested by student id: " << bookRequests[i].studentId
                 << endl;
        }
        cout << endl;
    }

    void issueBooks(string bookTitle, int studentId, int issuedate) {
        Book book;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == bookTitle) {
                book = books[i];
                book.borrowStatus = true;
                book.borrowedStudentId = studentId;
                book.lastDateOfReturn = issuedate + 7;
                break;
            }
        }

        int index = -1;
        for (int i = 0; i < bookRequests.size(); i++) {
            if (book.title == bookRequests[i].bookName) {
                index = i;
                break;
            }
        }
        bookRequests.erase(bookRequests.begin() + index);
    }

    void viewBookReturnRequest() {
        for (int i = 0; i < bookReturnRequests.size(); i++) {
            cout << "Book " << bookReturnRequests[i].bookName << " return requested by student id: "
                 << bookReturnRequests[i].studentId << endl;
        }
        cout << endl;
    }

    void returnBook(string bookTitle, int studentId, int returnDate) {
        Book book;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == bookTitle) {
                book = books[i];
                if (book.lastDateOfReturn < returnDate) {
                    Fund fund;
                    fund.fundType = 1;
                    fund.value = 2 * (returnDate - book.lastDateOfReturn);
                    funds.push_back(fund);
                }
                book.borrowStatus = false;
                book.borrowedStudentId = 0;
            }
        }
        int index = -1;
        for (int i = 0; i < bookReturnRequests.size(); i++) {
            if (book.title == bookReturnRequests[i].bookName) {
                index = i;
                break;
            }
        }
        bookReturnRequests.erase(bookReturnRequests.begin() + index);
    }


    void showDamageRequests() {
        for (int i = 0; i < damageRequests.size(); i++) {
            cout << "Book " << damageRequests[i].bookName << " damaged requested by student id: "
                 << damageRequests[i].studentId
                 << endl;
        }
        cout << endl;
    }

    void fineForDamage(string bookTitle, int studentId) {
        Book book;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == bookTitle) {
                book = books[i];
                break;;
            }
        }
        int index = -1;
        for (int i = 0; i < damageRequests.size(); i++) {
            if (damageRequests[i].bookName == bookTitle) {
                BookDamageRequest damageRequest = damageRequests[i];
                Fund fund;
                fund.fundType = 2;
                fund.value = book.price;
                funds.push_back(fund);
                index = i;
                break;
            }
        }

        damageRequests.erase(damageRequests.begin() + index);

    }
};

class Library {
public:
    void showMenu(Librarian &librarian, Student &loggedStudent, int &isLogged, int &userType) {

        if (userType == 1) {
            int again = 1;
            while (again == 1) {
                int choice;
                cout << "1. View all books\n";
                cout << "2. Add new book\n";
                cout << "3. Add New student\n";
                cout << "4. Delete  student account\n";
                cout << "5. Issue book\n";
                cout << "6. Return Book\n";
                cout << "7. Fine for damage/lost\n";
                cout << "8. View borrow requestst\n";
                cout << "9. View return request\n";
                cout << "10.View damage/lost request\n";
                cout << "11. Log out\n";
                cin >> choice;

                if (choice == 1) {
                    librarian.viewAllBooks();
                } else if (choice == 2) {
                    librarian.addNewBook();
                } else if (choice == 3) {
                    librarian.addNewAccount();
                } else if (choice == 4) {
                    int id;
                    cout << "Enter student id to delete: ";
                    cin >> id;
                    librarian.deleteAccount(id);
                } else if (choice == 5) {
                    int id, date;
                    string bookName;
                    cout << "Enter student id to issue: ";
                    cin >> id;
                    cout << "Enter book name: ";
                    cin >> bookName;
                    cout << "Enter issue date: ";
                    cin >> date;
                    librarian.issueBooks(bookName, id, date);
                } else if (choice == 6) {
                    int id, returnDate;
                    string bookName;
                    cout << "Enter student id to issue: ";
                    cin >> id;
                    cout << "Enter book name: ";
                    cin >> bookName;
                    cout << "Enter return date: ";
                    cin >> returnDate;
                    librarian.returnBook(bookName, id, returnDate);
                } else if (choice == 7) {
                    int id;
                    string bookName;
                    cout << "Enter student id to issue: ";
                    cin >> id;
                    cout << "Enter book name: ";
                    cin >> bookName;
                    librarian.fineForDamage(bookName, id);
                } else if (choice == 8) {
                    librarian.showBookRequests();
                } else if (choice == 9) {
                    librarian.viewBookReturnRequest();
                } else if (choice == 10) {
                    librarian.showDamageRequests();
                } else {
                    isLogged = 1;
                    userType = -1;
                    return;
                }

                cout << "Press 1 to back to main menu: ";
                cin >> again;
            }


        } else if (userType == 2) {
            int again = 1;
            while (again == 1) {

                int choice;
                cout << "1. View all books\n";
                cout << "2. Place book request\n";
                cout << "3. Place return book request\n";
                cout << "4. Place damage book request\n";
                cout << "5. Log out\n";
                cin >> choice;
                if (choice == 1) {
                    librarian.viewAllBooks();
                } else if (choice == 2) {
                    loggedStudent.placeIssueRequest(librarian.bookRequests);
                } else if (choice == 3) {
                    int returnDate;
                    cout << "Enter ruturn date: " << endl;
                    cin >> returnDate;
                    loggedStudent.bookReturnRequest(librarian.bookReturnRequests, returnDate);
                } else if (choice == 4) {
                    loggedStudent.placeDamageRequst(librarian.damageRequests);
                } else {
                    isLogged = 1;
                    userType = -1;
                    return;
                }

                cout << "Press 1 to back to main menu: ";
                cin >> again;
            }
        }

    }

    int checkLogin(Librarian &librarian, Student &loggedStudent, string username, int id, string
    password) {
        if ("admin" == username && "lib" == password) {
            return 1;
        }
        for (int i = 0; i < librarian.students.size(); i++) {
            if (librarian.students[i].id == id && librarian.students[i].password == password) {
                loggedStudent = librarian.students[i];
                return 2;
            }
        }
        return 0;
    }

    void totalSalesReport(vector<BookRequest> &bookRequests, vector<BookReturnRequest> &bookReturnRequests,
                          vector<Fund> funds) {
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project12/library.txt");
        MyFile << "Book Request";
        for (int i = 0; i < bookRequests.size(); i++) {
            MyFile << "Book " << bookRequests[i].bookName << "requested by student id: " << bookRequests[i].studentId
                   << endl;
        }

        MyFile << "Book Return Request";
        for (int i = 0; i < bookReturnRequests.size(); i++) {
            for (int i = 0; i < bookReturnRequests.size(); i++) {
                MyFile << "Book " << bookReturnRequests[i].bookName << " return requested by student id: "
                       << bookReturnRequests[i].studentId << endl;
            }
        }


        int totalFund = 0;
        for (int i = 0; i < funds.size(); i++) {
            for (int i = 0; i < funds.size(); i++) {
                totalFund += funds[i].value;
            }
        }
        MyFile << "Total fund: " << totalFund << endl;
        for (int i = 0; i < funds.size(); i++) {
            for (int i = 0; i < funds.size(); i++) {
                MyFile << "Fund: " << fundType(funds[i].fundType) << " -> " << funds[i].value << endl;
            }
        }
        MyFile.close();
    }

    string fundType(int type) {
        return type == 1 ? "Late Fee" : "Damage / Lost";
    }


};

int main() {

    Librarian librarian;
    Library library;
    Student loggedStudent;
    string username;
    string password;
    int isLogged = 1;
    // 0 - admin, 1 - teahcer, 2 - student
    int userType = -1;

    while (isLogged == 1) {

        cout << "Enter login details" << endl;
        cout << "Enter username / user id: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (library.checkLogin(librarian, loggedStudent, username, 0, password) == 1) {
            userType = 1;
        } else if (library.checkLogin(librarian, loggedStudent, "", stoi(username), password) == 2) {
            userType = 2;
        } else {
            cout << "Wrong details" << endl;
        }
        library.showMenu(librarian, loggedStudent, isLogged, userType);
    }


}