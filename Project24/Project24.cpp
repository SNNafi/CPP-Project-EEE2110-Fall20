//
// Created by Shahriar Nasim Nafi on 1/10/21.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Contact {
private:
    string name;
    int number;
    string email;
    string address;
    string dateOfBirth;

public:
    string getName() {
        return name;
    }

    int getNumber() {
        return number;
    }

    string getEmail() {
        return email;
    }

    string getAddress() {
        return address;
    }

    string getDateOfBirth() {
        return dateOfBirth;
    }

    void addContactByAdmin() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Number: ";
        cin >> number;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Address: ";
        cin >> address;
        cout << "Enter Date of Birth: ";
        cin >> dateOfBirth;
    }

    void updateContactByAdmin() {
        cout << "Update Name for " << name << ": ";
        cin >> name;
        cout << "Update Number for " << name << ": ";
        cin >> number;
        cout << "Update Email for " << name << ": ";
        cin >> email;
        cout << "Update Address for " << name << ": ";
        cin >> address;
        cout << "Update Date of Birth for " << name << ": ";
        cin >> dateOfBirth;
    }


    void updateContactByOtherApp() {
        cout << "Update Number for " << name << ": ";
        cin >> number;
        cout << "Update Email for " << name << ": ";
        cin >> email;
    }

};

class OtherApp {
    string username;
    int password;

public:
    string getUsername() {
        return username;
    }

    int getPassword() {
        return password;
    }

    void accessContacts(vector<Contact> &contacts) {
        for (int i = 0; i < contacts.size(); i++) {
            cout << "Contact " << i + 1 << " info" << endl;
            cout << "Name: " << contacts[i].getName();
            cout << " Number: " << contacts[i].getNumber();
            cout << " Email: " << contacts[i].getEmail() << endl;
            cout << "Address: " << contacts[i].getAddress();
            cout << " Date of birth: " << contacts[i].getDateOfBirth() << endl;
        }
    }

    void updateContacts(vector<Contact> &contacts) {
        for (int i = 0; i < contacts.size(); i++) {
            cout << "Contact Index " << i << " " << contacts[i].getName() << endl;
        }
        int index;
        cout << "Enter contact index to update: ";
        cin >> index;
        Contact contact = contacts[index];
        contact.updateContactByOtherApp();
        contacts[index] = contact;
    }


    void createOtherApp() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
    }
};


class Guest {
    string username;
    int password;

public:
    string getUsername() {
        return username;
    }

    int getPassword() {
        return password;
    }

    void createGuest() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
    }

    void viewContacts(vector<Contact> &contacts) {
        for (int i = 0; i < contacts.size(); i++) {
            cout << "Contact " << i + 1 << " info" << endl;
            cout << "Name: " << contacts[i].getName();
            cout << " Number: " << contacts[i].getNumber();
            cout << " Email: " << contacts[i].getEmail() << endl;
            cout << "Address: " << contacts[i].getAddress();
            cout << " Date of birth: " << contacts[i].getDateOfBirth() << endl;
        }
    }
};

class Owner {
public:
    vector<Contact> contacts;
    vector<OtherApp> otherApps;
    vector<Guest> guests;
    OtherApp currentOtherApp;
    Guest currentGuest;

    void createGuest() {
        Guest guest;
        guest.createGuest();
        guests.push_back(guest);
    }

    void createOtherApp() {
        OtherApp otherApp;
        otherApp.createOtherApp();
        otherApps.push_back(otherApp);
    }

    void addNewContact() {
        Contact contact;
        contact.addContactByAdmin();
        contacts.push_back(contact);
    }


    void viewContacts() {
        for (int i = 0; i < contacts.size(); i++) {
            cout << "Contact " << i + 1 << " info" << endl;
            cout << "Name: " << contacts[i].getName();
            cout << " Number: " << contacts[i].getNumber();
            cout << " Email: " << contacts[i].getEmail() << endl;
            cout << "Address: " << contacts[i].getAddress();
            cout << " Date of birth: " << contacts[i].getDateOfBirth() << endl;
        }
    }

    void updateContact() {
        for (int i = 0; i < contacts.size(); i++) {
            cout << "Contact Index " << i << " " << contacts[i].getName() << endl;
        }
        cout << "Enter contact index to update: ";

        int index;
        cin >> index;
        Contact contact = contacts[index];
        contact.updateContactByAdmin();
        contacts[index] = contact;
    }


    void deleteContact() {
        for (int i = 0; i < contacts.size(); i++) {
            cout << "Contact Index " << i << " " << contacts[i].getName() << endl;
        }
        cout << "Enter contact index to delete: ";
        int index;
        cin >> index;
        contacts.erase(contacts.begin() + index);
    }

    void saveToTextFile() {
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project24/contact.txt");
        MyFile << "Name" << "\t" << "PhoneNumber" << "\t" << "Email"
               << "\t" << "Address" << "\t"
               << "DOB"
               << endl;
        for (int i = 0; i < contacts.size(); i++) {
            Contact contact = contacts[i];
            MyFile << contact.getName() << "\t" << contact.getNumber()
                   << "\t" << contact.getEmail() << "\t" << contact.getAddress()
                   << "\t" << contact.getDateOfBirth() << endl;
        }
        MyFile.close();
    }

    int checkLogin(string username, int password) {
        if ("admin" == username && 12345 == password) {
            return 1;
        }
        for (int i = 0; i < otherApps.size(); i++) {
            if (otherApps[i].getUsername() == username && otherApps[i].getPassword() == password) {
                currentOtherApp = otherApps[i];
                return 2;
            }
        }
        for (int i = 0; i < guests.size(); i++) {
            if (guests[i].getUsername() == username && guests[i].getPassword() == password) {
                currentGuest = guests[i];
                return 3;
            }
        }
    }

};

void works(Owner &owner, int &isLogged, int &userType) {

    if (userType == 1) {


        int again = 1;
        while (again == 1) {
            int choice;
            cout << "1. View all contact\n";
            cout << "2. Add new other app\n";
            cout << "3. Add new guest\n";
            cout << "4. Add new contact\n";
            cout << "5. Update a contact\n";
            cout << "6. Delete a contact\n";
            cout << "7. Save contact to file\n";
            cout << "8. Log out\n";
            cin >> choice;

            if (choice == 1) {
                owner.viewContacts();
            } else if (choice == 2) {
                owner.createOtherApp();
            } else if (choice == 3) {
                owner.createGuest();
            } else if (choice == 4) {
                owner.addNewContact();
            } else if (choice == 5) {
                owner.updateContact();
            } else if (choice == 6) {
                owner.deleteContact();
            } else if (choice == 7) {
                owner.saveToTextFile();
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
        while (again == 1) { ;
            int choice;
            cout << "1. View contact\n";
            cout << "2. Modify a contact\n";
            cout << "3. Log out\n";
            cin >> choice;
            if (choice == 1) {
                owner.currentOtherApp.accessContacts(owner.contacts);
            } else if (choice == 2) {
                owner.currentOtherApp.updateContacts(owner.contacts);
            } else {
                isLogged = 1;
                userType = -1;
                return;
            }
            cout << "Press 1 to back to main menu: ";
            cin >> again;
        }


    } else if (userType == 3) {


        int again = 1;
        while (again == 1) {

            int choice;
            int number;
            cout << "1. View Contact\n";
            cout << "2. Log out\n";
            cin >> choice;
            if (choice == 1) {
                owner.currentGuest.viewContacts(owner.contacts);
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

int main() {

    Owner owner;
    string username;
    int password;
    int isLogged = 1;
    // 1 - admin, 2- other app, 3 - guest
    int userType = -1;
    while (isLogged == 1) {

        cout << "Enter login details" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (owner.checkLogin(username, password) == 1) {
            userType = 1;
        } else if (owner.checkLogin(username, password) == 2) {
            userType = 2;
        } else if (owner.checkLogin(username, password) == 3) {
            userType = 3;
        } else {
            cout << "Wrong details" << endl;
        }
        works(owner, isLogged, userType);
    }


}