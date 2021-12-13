//
// Created by Shahriar Nasim Nafi on 27/9/21.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


typedef int Again;
// 1 - ADMIN 2 - CUSTOMER
typedef int UserType;
// 1 - Borrow 2 - Purchase
typedef int OrderType;

typedef int Option;

const UserType ADMIN = 1;
const UserType CUSTOMER = 2;


// Use toLowerCase function to compare two string irrespectively their case for better searching
string toLowerCase(string text) {
    string::iterator it;
    for (it = text.begin(); it != text.end(); it++) {
        if (*it >= 'A' && *it <= 'Z') {
            *it += 32;
        }
    }
    return text;
}

class Book {

    // Book id;
    int id;
    // Book title
    string title;
    // Book Author Name
    string authorName;
    // Book Publsisher
    string publisher;
    // Book Edition
    string edition;
    // Book Price
    double price;
    // Book Stock
    int stock;
public:
    int getId() const {
        return id;
    }

    const string &getTitle() const {
        return title;
    }

    const string &getAuthorName() const {
        return authorName;
    }

    const string &getPublisher() const {
        return publisher;
    }

    const string &getEdition() const {
        return edition;
    }

    double getPrice() const {
        return price;
    }

    int getStock() const {
        return stock;
    }

    void setStock(int stock) {
        this->stock = stock;
    }

    void addNewBook() {

        cout << "Add new Book" << endl;
        cout << "Enter id: ";
        cin >> id;
        cout << "Enter name: ";
        cin.ignore(1, '\n');
        getline(cin, title);
        cout << "Enter author name: ";
        getline(cin, authorName);
        cout << "Enter publisher: ";
        getline(cin, publisher);
        cout << "Enter edition: ";
        getline(cin, edition);
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter stock: ";
        cin >> stock;
    }

    void editBookInfo() {
        cout << "Editing book info" << endl;
        cout << "Enter new id: ";
        cin >> id;
        cout << "Enter new name: ";
        cin.ignore(1, '\n');
        getline(cin, title);
        cout << "Enter new author name: ";
        getline(cin, authorName);
        cout << "Enter new publisher: ";
        getline(cin, publisher);
        cout << "Enter new edition: ";
        getline(cin, edition);
        cout << "Enter new price: ";
        cin >> price;
        cout << "Enter new stock: ";
        cin >> stock;
    }

    void viewBookInfo() {
        cout << "Book info for: " << endl;
        cout << "ID: " << id;
        cout << "| Title: " << title;
        cout << "| Author Name: " << authorName << endl;
        cout << "Publisher: " << publisher;
        cout << "| Edition: " << edition << endl;
        cout << "Book price: " << price;
        cout << "| Stock: " << stock << endl;
        cout << endl;
    }

    Book() {

    }

    Book(int id, const string title, const string authorName, const string publisher, const string edition,
         double price, int stock) {
        this->id = id;
        this->title = title;
        this->authorName = authorName;
        this->publisher = publisher;
        this->edition = edition;
        this->price = price;
        this->stock = stock;
    }

};

class Order {

    int customerId;
    string customerName;
    int bookId;
    string bookName;
    int quantity;
    // OrderType (tyepdef int) -> Borrow 1 Purchase 2
    OrderType orderType;
    double price;

public:
    int getCustomerId() const {
        return customerId;
    }

    const string &getCustomerName() const {
        return customerName;
    }

    int getBookId() const {
        return bookId;
    }

    const string &getBookName() const {
        return bookName;
    }

    int getQuantity() const {
        return quantity;
    }

    OrderType getOrderType() const {
        return orderType;
    }

    double getPrice() const {
        return price;
    }


public:
    static void showAllOrders(vector<Order> &orders) {
        if (orders.size() == 0) {
            cout << "No orders found !" << endl;
            return;
        }
        cout << endl;
        cout << "ALL ORDERS DETAIL" << endl;
        cout << endl;
        for (int i = 0; i < orders.size(); i++) {
            Order order = orders[i];
            cout << "ORDER DETAIL FOR: " << i + 1 << endl;
            cout << "Customer ID: " << order.customerId;
            cout << " | Customer Name: " << order.customerName << endl;
            cout << "Book ID: " << order.bookId;
            cout << " | Book Name: " << order.bookName << endl;
            cout << "Order Status: " << orderStatus(order.orderType);
            cout << " | Total price: " << order.price << endl;
            cout << endl;

        }
    }

    void addNewOrder(vector<Order> &orders, int _customerId, string _customerName, Book &book, int bookQuantity,
                     OrderType _orderType) {
        customerId = _customerId;
        customerName = _customerName;
        bookId = book.getId();
        bookName = book.getTitle();
        quantity = bookQuantity;
        orderType = _orderType;
        if (orderType == 1) {
            price = (book.getPrice() * 0.2) * quantity;
        } else {
            price = book.getPrice() * quantity;
        }
    }

    static string orderStatus(int status) {
        return status == 2 ? "Purchase" : "Borrow";
    }
};

// Customer Class
class Customer {

    // Customer ID
    int id;
    // Customer Name
    string name;
    // Customer Phone No
    int phoneNo;
    // Customer Email ID
    string emailId;
    // Customer Mailing Address
    string mailingAddress;
    // Customer Billing Address
    string billingAddress;

public:
    vector<Order> corders;

    int getId() const {
        return id;
    }

    const string &getName() const {
        return name;
    }

    int getPhoneNo() const {
        return phoneNo;
    }

    const string &getEmailId() const {
        return emailId;
    }

    const string &getMailingAddress() const {
        return mailingAddress;
    }

    const string &getBillingAddress() const {
        return billingAddress;
    }

    // Get Customer Info
    void getCustomerInfo() {

        cout << "Customer info for " << id << endl;
        cout << "Name: " << name;
        cout << "| ID: " << id << endl;
        cout << "Phone No: " << phoneNo;
        cout << "| Email ID: " << emailId << endl;
        cout << "Mailing Address: " << mailingAddress;
        cout << "| Billing Address: " << billingAddress << endl;
        cout << endl;
        cout << "ALL ORDERS DETAIL FOR " << name << endl;
        cout << endl;
        for (int i = 0; i < corders.size(); i++) {
            cout << "Order " << i + 1 << " detail: " << endl;
            cout << "Book id: " << corders[i].getBookId();
            cout << " | Book name: " << corders[i].getBookName() << endl;
            cout << "Price: " << corders[i].getPrice();
            cout << " | Type: " << Order::orderStatus(corders[i].getOrderType()) << endl;
            cout << endl;
        }
    }

    // Edit Customer Info
    void editCustomerInfo() {
        getCustomerInfo();
        cout << "Editing Customer Info" << endl;
        cout << "Enter new id: ";
        cin >> id;
        cout << "Enter new name: ";
        cin.ignore(1, '\n');
        getline(cin, name);
        cout << "Enter new phone no: ";
        cin >> phoneNo;
        cout << "Enter new email id: ";
        cin >> emailId;
        cout << "Enter new mailing address: ";
        cin.ignore(1, '\n');
        getline(cin, mailingAddress);
        cout << "Enter new billing address: ";
        getline(cin, billingAddress);
    }

    // Add new customer
    void addNewCustomer() {
        cout << "Add new Customer" << endl;
        cout << "Enter id: ";
        cin >> id;
        cout << "Enter name: ";
        cin.ignore(1, '\n');
        getline(cin, name);
        cout << "Enter phone no: ";
        cin >> phoneNo;
        cout << "Enter email id: ";
        cin >> emailId;
        cout << "Enter mailing address: ";
        cin.ignore(1, '\n');
        getline(cin, mailingAddress);
        cout << "Enter billing address: ";
        getline(cin, billingAddress);
    }

    Customer() {

    }

    Customer(int id, const string name, int phoneNo, const string emailId, const string mailingAddress,
             const string billingAddress) {
        this->id = id;
        this->name = name;
        this->phoneNo = phoneNo;
        this->emailId = emailId;
        this->mailingAddress = mailingAddress;
        this->billingAddress = billingAddress;
    }
};


class Admin {

public:
    static void addNewBook(vector<Book> &books) {
        Book book;
        book.addNewBook();
        books.push_back(book);
        cout << book.getTitle() << " added successfully !" << endl;
    }

    // Edit book
    static void editBook(vector<Book> &books) {
        // Text to search i.e book title/ book author name
        string searchCase;
        cout << "Enter book title or author name to edit." << endl;
        cin.ignore(1, '\n');
        getline(cin, searchCase);
        // If found several books with same author or similar name, the store there index
        vector<int> foundBooks;
        // check found more than one
        int totalFound = 0;
        // the finally seleectd book to edit
        int bookIndexToEdit = -1;
        // Book class to edit book
        Book book;
        // searching for the book

        for (int i = 0; i < books.size(); i++) {
            // first checking if both are same  if not then check if substring match
            if ((toLowerCase(searchCase)) == toLowerCase(books[i].getTitle()) ||
                (toLowerCase(searchCase)) == toLowerCase(books[i].getAuthorName()) ||
                toLowerCase(searchCase).find(toLowerCase(books[i].getTitle())) ||
                toLowerCase(searchCase).find(toLowerCase(books[i].getAuthorName()))) {
                foundBooks.push_back(i);
                totalFound += 1;
            }
        }


        // check if several found
        if (totalFound > 1) {
            cout << "Several books found!" << endl;
            // then cout them by for loop to select one
            for (int i = 0; i < foundBooks.size(); i++) {
                cout << i + 1 << ". " << books[foundBooks[i]].getTitle() <<
                     endl;
            }

            cout << "Enter book number to edit: ";
            cin >> bookIndexToEdit;
            // Check if bookNumber out of index then return
            if (bookIndexToEdit > foundBooks.size()) {
                cout << "Please enter valid book number" << endl;
                return;
            }

            book = books[foundBooks[bookIndexToEdit - 1]];
            book.editBookInfo();

            books[foundBooks[bookIndexToEdit - 1]] = book;
            cout << book.getTitle() << " edited successfully !" << endl;

        } else if (totalFound == 1) {
            // Single book found.
            cout << "Single book found!: " << endl;
            cout << books[foundBooks[0]].getTitle() <<
                 endl;
            cout << "Enter 1 to edit: ";
            cin >> bookIndexToEdit;
            if (bookIndexToEdit == 1) {
                book = books[foundBooks[0]];
                book.editBookInfo();
                books[foundBooks[0]] = book;
                cout << book.getTitle() << " edited successfully !" << endl;
            }
        } else {
            cout << "No books found for following case: " << searchCase << endl;
        }
    }


    // Delete book
    static void deleteBook(vector<Book> &books) {
        // Text to search i.e book title/ book author name
        string searchCase;
        cout << "Enter book title or author name to delete." << endl;
        cin.ignore(1, '\n');
        getline(cin, searchCase);

        // If found several books with same author or similar name, the store there index
        vector<int> foundBooks;
        // check found more than one
        int totalFound = 0;
        // the finally seleectd book to edit
        int bookIndexToEdit = -1;
        // Book class to edit book
        Book book;
        // searching for the book

        for (int i = 0; i < books.size(); i++) {
            // first checking if both are same  if not then check if substring match
            if ((toLowerCase(searchCase)) == toLowerCase(books[i].getTitle()) ||
                (toLowerCase(searchCase)) == toLowerCase(books[i].getAuthorName()) ||
                toLowerCase(searchCase).find(toLowerCase(books[i].getTitle())) ||
                toLowerCase(searchCase).find(toLowerCase(books[i].getAuthorName()))) {
                foundBooks.push_back(i);
                totalFound += 1;
            }
        }

        // check if several found
        if (totalFound > 1) {
            cout << "Several books found!" << endl;
            // then cout them by for loop to select one
            for (int i = 0; i < foundBooks.size(); i++) {
                cout << i + 1 << ". " << books[foundBooks[i]].getTitle() <<
                     endl;
            }

            cout << "Enter book number to delete: ";
            cin >> bookIndexToEdit;

            // Check if bookNumber out of index then return
            if (bookIndexToEdit > foundBooks.size()) {
                cout << "Please enter valid book number" << endl;
                return;
            }
            book = books[foundBooks[bookIndexToEdit - 1]];
            books.erase(books.begin() + foundBooks[bookIndexToEdit - 1]);
            cout << book.getTitle() << " deleted successfully !" << endl;

        } else if (totalFound == 1) {
            // Single book found.
            cout << "Single book found!: " << endl;
            cout << books[foundBooks[0]].getTitle() <<
                 endl;
            cout << "Enter 1 to delete: ";
            cin >> bookIndexToEdit;

            if (bookIndexToEdit) {
                book = books[foundBooks[0]];
                books.erase(books.begin() + 0);
                cout << book.getTitle() << " deleted successfully !" << endl;
            }
        } else {
            cout << "No books found for following case: " << searchCase << endl;
        }
    }

    static void viewBooks(vector<Book> &books) {
        if (books.size() == 0) {
            cout << "No books found !" << endl;
            return;
        }
        // typedef int
        Again anotherBookShow = 1;
        cout << "All books in this shop" << endl << endl;
        for (int i = 0; i < books.size(); i++) {
            cout << i + 1 << ". " << books[i].getTitle() <<
                 endl;
        }
        // as 1+ automatically take as true
        while (anotherBookShow) {
            int bookNumber;
            cout << "Enter book number to view details" << endl;
            cin >> bookNumber;
            if (bookNumber > books.size()) {
                cout << "Please enter valid bookNumber" << endl;
                return;
            }
            Book book = books[bookNumber - 1];
            book.viewBookInfo();
            cout << "Enter 1 to show another or 0 to back menu" << endl;
            cin >> anotherBookShow;
            if (anotherBookShow == 0) {
                return;
            }
        }

    }

    static void seeCustomersInfo(vector<Customer> &customers) {
        if (customers.size() == 0) {
            cout << "No customers found !" << endl;
            return;
        }
        // typedef int
        Again anotherCustomerShow = 1;
        cout << "All customers in this shop" << endl << endl;
        for (int i = 0; i < customers.size(); i++) {
            cout << i + 1 << ". " << customers[i].getName() <<
                 endl;
        }
        while (anotherCustomerShow) {
            int number;
            cout << "Enter customer number to view details" << endl;
            cin >> number;

            if (number > customers.size()) {
                cout << "Please enter valid number" << endl;
                return;
            }
            Customer customer = customers[number - 1];
            customer.getCustomerInfo();
            cout << "Enter 1  to show another or 0 to back menu" << endl;
            cin >> anotherCustomerShow;
            if (anotherCustomerShow == 0) {
                return;
            }
        }
    }

    static void editCustomerInfo(vector<Customer> &customers) {
        // Text to search i.e book title/ book author name
        int id;

        cout << "Enter customrer id to edit." << endl;
        cin >> id;
        // the finally seleectd customer to edit
        int customerIndexToEdit = -1;
        // Customer class to edit book
        Customer customer;
        // searching for the customer
        bool isFound = false;

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getId() == id) {
                customerIndexToEdit = i;
                isFound = true;
                break;
            }
        }

        // check if several found
        if (isFound) {
            // Single book found.
            cout << "Customer found!: " << endl;
            cout << customers[customerIndexToEdit].getName() <<
                 endl;
            int isEdit = -1;
            cout << "Enter 1 to edit: ";
            cin >> isEdit;
            if (isEdit == 1) {
                customer = customers[customerIndexToEdit];
                customer.editCustomerInfo();
                customers[customerIndexToEdit] = customer;
                cout << customer.getName() << "'s info successfully !" << endl;
            }
        } else {
            cout << "No customer found for following id: " << id << endl;
        }
    }


};

class AccountInfo {
private:
    int id;
    string userName;
    string password;
    bool isAdmin = false;
public:
    AccountInfo(int id, const string userName, string password, bool isAdmin) {
        this->id = id;
        this->userName = userName;
        this->password = password;
        this->isAdmin = isAdmin;
    }

    bool checkCredentials(string userName, string password) {
        if (this->userName == userName && this->password == password) {
            return true;
        }
        return false;
    }

    int getId() const {
        return id;
    }

    const string &getUserName() const {
        return userName;
    }

    bool isAdmin1() const {
        return isAdmin;
    }

};

class AccountInfos {
    AccountInfo admin = AccountInfo(0, "admin", "12345678", true);
    vector<AccountInfo> customerinfos;
    int currentCustomerId;

public:

    AccountInfos() {
        // Default Customer Login
        AccountInfo accountInfo = AccountInfo(1, "snnafi", "1234", false);
        customerinfos.push_back(accountInfo);
    }

    const int getCurrentCustomerId() const {
        return currentCustomerId;
    }


public:
    // typedef UserType = int
    UserType checkLogin(string username, string password) {
        if (admin.checkCredentials(username, password)) {
            // admin -> 1
            return 1;
        }
        for (int i = 0; i < customerinfos.size(); i++) {
            if (customerinfos[i].checkCredentials(username, password)) {
                currentCustomerId = customerinfos[i].getId();
                return 2;
            }
        }
        return false;
    }

    void addNewCustomer(vector<Customer> &customers) {
        Customer customer;
        string userName;
        string password;
        customer.addNewCustomer();
        cout << "Enter customer username: ";
        cin >> userName;
        cout << "Enter customer password: ";
        cin >> password;
        customers.push_back(customer);
        AccountInfo accountInfo = AccountInfo(customer.getId(), userName, password, false);
        customerinfos.push_back(accountInfo);
        cout << customer.getName() << " added successfully !" << endl;

    }

    void deleteCustomer(vector<Customer> &customers) {
        int id;
        cout << "Enter customer id to delete: ";
        cin >> id;
        int customerIndex = -1;
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getId() == id) {
                customerIndex = i;
            }
        }
        Customer customer = customers[customerIndex];
        customers.erase(customers.begin() + customerIndex);

        for (int i = 0; i < customerinfos.size(); i++) {
            if (customerinfos[i].getId() == id) {
                customerIndex = i;
            }
        }

        customerinfos.erase(customerinfos.begin() + customerIndex);
        cout << customer.getName() << " deleted successfully !" << endl;
    }


};


class MenuSelection {
    vector<Book> books;
    vector<Customer> customers;
    vector<Order> orders;
    // 1 Admin 2 Customer
    UserType currentUserType = -1;

public:
    bool loggedDailogue = true;
    AccountInfos accountInfos = AccountInfos();


    void searchBook() {
        vector<int> foundBooks;
        int totalFound = 0;
        Book book;
        Order order;
        string searchCase;

        cout << "Enter book name or author name to search: ";
        cin.ignore(1, '\n');
        getline(cin, searchCase);

        for (int i = 0; i < books.size(); i++) {
            // first checking if both are same  if not then check if substring match
            if ((toLowerCase(searchCase)) == toLowerCase(books[i].getTitle()) ||
                (toLowerCase(searchCase)) == toLowerCase(books[i].getAuthorName()) ||
                toLowerCase(searchCase).find(toLowerCase(books[i].getTitle())) ||
                toLowerCase(searchCase).find(toLowerCase(books[i].getAuthorName()))) {
                foundBooks.push_back(i);
                totalFound += 1;

            }
        }
        // check if several found
        if (totalFound > 1) {
            cout << "Several books found!" << endl;
            // then cout them by for loop to select one
            for (int i = 0; i < foundBooks.size(); i++) {
                cout << i + 1 << ". " << books[foundBooks[i]].getTitle() <<
                     endl;
            }

            int bookIndex;
            cout << "Enter book number to borrow or purchase: ";
            cin >> bookIndex;

            // Check if bookNumber out of index then return
            if (bookIndex > foundBooks.size()) {
                cout << "Please enter valid book number" << endl;
                return;
            }
            book = books[foundBooks[bookIndex - 1]];
            if (book.getStock() > 0) {
                int type;
                int quantity;

                cout << "1. Borrow \n2. Buy" << endl;
                cout << "Enter number to select order type: ";
                cin >> type;
                cout << "How much you want to buy: ";
                cin >> quantity;
                if (quantity > book.getStock()) {
                    cout << "Your ordered books amount exceed the current stock !" << endl;
                    return;
                }

                if (type == 1) {
                    borrowBook(book, quantity, 1);
                } else {
                    buyBook(book, quantity, 2);
                }

                cout << book.getTitle() << " ordered successfully !" << endl;
            } else {
                cout << book.getTitle() << "is stocked out" << endl;
            }
        } else if (totalFound == 1) {
            // Single book found.
            cout << "Single book found!: " << endl;
            cout << books[foundBooks[0]].getTitle() <<
                 endl;
            int status = -1;
            cout << "Enter 1 to borrow or purchase: ";
            cin >> status;
            if (status == 1) {
                book = books[foundBooks[0]];
                if (book.getStock() > 0) {
                    int type;
                    int quantity;

                    cout << "1. Borrow \n2. Buy" << endl;
                    cout << "Enter number to select order type: ";
                    cin >> type;
                    cout << "How much you want to buy: ";
                    cin >> quantity;

                    if (quantity > book.getStock()) {
                        cout << "Your ordered books amount exceed the current stock !" << endl;
                        return;
                    }

                    if (type == 1) {
                        borrowBook(book, quantity, 1);
                    } else {
                        buyBook(book, quantity, 2);
                    }
                    cout << book.getTitle() << " ordered successfully !" << endl;
                } else {
                    cout << book.getTitle() << "is stocked out" << endl;
                }
            }
        } else {
            cout << "No books found for following case: " << searchCase << endl;
        }

    }


    void borrowBook(Book book, int quantity, OrderType orderType) {
        Order order;
        Customer customer = customers[getCustomerIndexById()];
        cout << "NAME: " << customer.getName() << endl;
        order.addNewOrder(orders, customer.getId(), customer.getName(), book, quantity, orderType);
        orders.push_back(order);
        customers[getCustomerIndexById()].corders.push_back(order);
        for (int i = 0; i < books.size(); i++) {
            if (order.getBookId() == books[i].getId()) {
                int updatedQuantity = books[i].getStock() - quantity;
                Book updated = books[i];
                updated.setStock(updatedQuantity);
                books[i] = updated;
                break;
            }
        }
    }

    void buyBook(Book book, int quantity, OrderType orderType) {
        Order order;
        Customer customer = customers[getCustomerIndexById()];
        cout << "NAME: " << customer.getName() << endl;
        order.addNewOrder(orders, customer.getId(), customer.getName(), book, quantity, orderType);
        orders.push_back(order);
        customers[getCustomerIndexById()].corders.push_back(order);
        for (int i = 0; i < books.size(); i++) {
            if (order.getBookId() == books[i].getId()) {
                int updatedQuantity = books[i].getStock() - quantity;
                Book updated = books[i];
                updated.setStock(updatedQuantity);
                books[i] = updated;
                break;
            }
        }
    }


    void viewBooks() {
        // typedef int
        Again anotherBookShow = 1;
        cout << "All books in this shop" << endl << endl;
        for (int i = 0; i < books.size(); i++) {
            cout << i + 1 << ". " << books[i].getTitle() <<
                 endl;
        }
        // as 1+ automatically take as true
        while (anotherBookShow) {
            int bookNumber;
            cout << "Enter book number to view details" << endl;
            cin >> bookNumber;
            if (bookNumber > books.size()) {
                cout << "Please enter valid bookNumber" << endl;
                return;
            }
            Book book = books[bookNumber - 1];
            book.viewBookInfo();
            cout << "Enter 1 to show another or 0 to back menu" << endl;
            cin >> anotherBookShow;
            if (anotherBookShow == 0) {
                return;
            }
        }
    }

    void startMenu() {
        if (currentUserType == ADMIN) {
            Again showAdminMenuAgain = true;
            while (showAdminMenuAgain) {
                Option option = -1;
                cout << "1. View books" << endl;
                cout << "2. Add new book" << endl;
                cout << "3. Edit book" << endl;
                cout << "4. Delete book" << endl;
                cout << "5. View customers" << endl;
                cout << "6. Add new customer" << endl;
                cout << "7. Delete customer" << endl;
                cout << "8. View all orders" << endl;
                cout << "9. Generate daily sales report" << endl;
                cout << "10. Log out" << endl;
                cout << "Select ONE: ";
                cin >> option;
                if (option == 1) {
                    Admin::viewBooks(books);
                } else if (option == 2) {
                    Admin::addNewBook(books);
                } else if (option == 3) {
                    Admin::editBook(books);
                } else if (option == 4) {
                    Admin::deleteBook(books);
                } else if (option == 5) {
                    Admin::seeCustomersInfo(customers);
                } else if (option == 6) {
                    accountInfos.addNewCustomer(customers);
                } else if (option == 7) {
                    accountInfos.deleteCustomer(customers);
                } else if (option == 8) {
                    Order::showAllOrders(orders);
                } else if (option == 9) {
                    generateDailySalesReport();
                } else if (option == 10) {
                    loggedDailogue = true;
                    currentUserType = -1;
                    return;
                }
                cout << "Press 1 to return menu: ";
                cin >> showAdminMenuAgain;
            }
        } else if (currentUserType == CUSTOMER) {
            Again showUserMenuAgain = true;
            while (showUserMenuAgain) {
                Option option = -1;
                cout << "1. Search book" << endl;
                cout << "2. log out" << endl;
                cout << "Enter number to select: ";
                cin >> option;
                if (option == 1) {
                    searchBook();
                } else if (option == 2) {
                    loggedDailogue = true;
                    currentUserType = -1;
                    return;
                }
                cout << "Press 1 to return menu: ";
                cin >> showUserMenuAgain;
            }
        }
    }

    UserType getCurrentUserType() const {
        return currentUserType;
    }

    void setCurrentUserType(UserType cuurentUserType) {
        this->currentUserType = cuurentUserType;
    }

    MenuSelection() {
        // Default Customer
        Customer customer = Customer(1, "Shahriar Nasim Nafi", 0324355, "shahriarnasim.nafi@gmail.com", "Mymensigh",
                                     "Mymensigh");
        customers.push_back(customer);

        //Default Book
        Book book = Book(1, "Saḥiḥ al-Bukharī", "Muhammad al-Bukhari", "---", "9th century", 5000, 30);
        books.push_back(book);

    }

private:
    int getCustomerIndexById() {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getId() == accountInfos.getCurrentCustomerId()) {
                return i;
            }
        }
    }

    void generateDailySalesReport() {
        ofstream dailySales;
        dailySales.open("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/SELF/DailySales.txt");
        dailySales << "CustomerID\tCustomerName\tBookID\tBookName\tQuantity\tStatus(B/P)\tPrice\n";
        for (int i = 0; i < orders.size(); i++) {
            dailySales << orders[i].getCustomerId() << "\t\t\t" << orders[i].getCustomerName() << "\t\t\t"
                       << orders[i].getBookId()
                       << "\t\t"
                       << orders[i].getBookName()
                       << "\t\t\t" << orders[i].getQuantity() << "\t\t\t" << orderStatusPrint(orders[i].getOrderType())
                       << "\t\t\t"
                       << orders[i].getPrice()
                       << endl;
        }
        dailySales.close();
        cout << "Generated daily sales report in DailySales.txt file !" << endl;
    }

    string orderStatusPrint(OrderType orderType) {
        if (orderType == 1) {
            return "B";
        } else {
            return "P";
        }
    }
};


int main() {

    MenuSelection menuSelection;
    string username;
    string password;

    while (menuSelection.loggedDailogue) {
        cout << "Enter login details" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (menuSelection.accountInfos.checkLogin(username, password) == ADMIN) {
            menuSelection.setCurrentUserType(ADMIN);
        } else if (menuSelection.accountInfos.checkLogin(username, password) == CUSTOMER) {
            menuSelection.setCurrentUserType(CUSTOMER);
        } else {
            cout << "Wrong credentials" << endl;
            cout << "1. Back to login menu else 0 to end program: ";
            cin >> menuSelection.loggedDailogue;
            if (!menuSelection.loggedDailogue) {
                break;
            }
        }
        menuSelection.startMenu();

    }
    return 0;
}