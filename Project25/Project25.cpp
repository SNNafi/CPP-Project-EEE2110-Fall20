//
// Created by Shahriar Nasim Nafi on 30/9/21.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Semester {
public:
    string name;
};

class Student {
public:
    int id;
    string username;
    // 0 EEE 1 CSE 2 CE 3 ME 4 CIVIL 5 ARCH
    int department;
    int year;
    Semester semester;
    int password;
};

class Official {
public:
    int id;
    string username;
    int password;
};


class Payment {
public:
    Student student;
    double tutionFee;
    double laboraotoryFee;
    double libraryFee;
    double others;
};


class Admin {
public:
    vector<Semester> semesters;
    vector<Official> officials;
    vector<Student> students;
    vector<Payment> payments;
    Student loggedStudent;


public:
    void registerNewOfficial() {
        Official official;
        cout << "Enter official id: ";
        cin >> official.id;
        cout << "Enter official username: ";
        cin >> official.username;
        cout << "Enter official password: ";
        cin >> official.password;
        officials.push_back(official);
    }

    void registerNewStudent() {
        Student student;
        cout << "Enter student id: ";
        cin >> student.id;
        cout << "Enter student username: ";
        cin >> student.username;
        cout << "Enter student password: ";
        cin >> student.password;
        cout << "Enter student dept, 0: EEE 1: CSE 2: CE 3: ME 4: CIVIL 5: ARCH ";
        cin >> student.department;
        cout << "Enter student year: ";
        cin >> student.year;
        cout << "Enter student semester: ";
        cin >> student.semester.name;
        students.push_back(student);
    }

    void listSemester() {
        cout << "All semester" << endl;
        for (int i = 0; i < semesters.size(); i++) {
            cout << semesters[i].name << endl;
        }
    }

    void addNewSemester() {
        Semester semester;
        cout << "Enter semester name: ";
        cin >> semester.name;
        semesters.push_back(semester);
    }

    void deleteSemester() {
        string name;
        cout << "Enter semester name to delete: ";
        cin >> name;
        for (int i = 0; i < semesters.size(); i++) {
            if (semesters[i].name == name) {
                semesters.erase(semesters.begin() + i);
                break;
            }
        }

    }

    void editSemester() {
        Semester semester;
        cout << "Enter semester name: ";
        cin >> semester.name;
        int index = -1;
        for (int i = 0; i < semesters.size(); i++) {
            if (semesters[i].name == semester.name) {
                index = i;
                break;
            }
        }
        cout << "Enter semester new name: ";
        cin >> semester.name;
        semesters[index] = semester;
    }

    void modifyStudentAccount() {
        Student student;
        cout << "Enter student id to edit: ";
        cin >> student.id;
        int index;
        for (int i = 0; i < students.size(); i++) {
            if (students[i].id == student.id) {
                index = i;
                break;
            }
        }

        cout << "Enter student new username: ";
        cin >> student.username;
        cout << "Enter student new password: ";
        cin >> student.password;
        cout << "Enter student new dept, 0: EEE 1: CSE 2: CE 3: ME 4: CIVIL 5: ARCH ";
        cin >> student.department;
        cout << "Enter student new year: ";
        cin >> student.year;
        cout << "Enter student new semester: ";
        cin >> student.semester.name;

        students[index] = student;
    }

    void viewStudentsPaymentHistory() {
        int id;
        cout << "Enter student id to view: ";
        cin >> id;
        for (int i = 0; i < payments.size(); i++) {
            if (payments[i].student.id == id) {
                Payment payment = payments[i];
                cout << "Student Id: " << payment.student.id << endl;
                cout << "Student Name: " << payment.student.username << endl;
                cout << "Student Semester: " << payment.student.id << endl;
                cout << "Student Tution Fee: " << payment.tutionFee << endl;
                cout << "Student laboraotory Fee: " << payment.laboraotoryFee << endl;
                cout << "Student library Fee: " << payment.libraryFee << endl;
                cout << "Student others: " << payment.others << endl;
                cout << endl;
                cout << endl;
            }
        }
    }

    void modifyStudentPaymentHistory() {
        int id;
        cout << "Enter student id to modify: ";
        cin >> id;
        vector<int> spayments;
        Student student;
        for (int i = 0; i < payments.size(); i++) {
            if (payments[i].student.id == id) {
                spayments.push_back(i);
                student = payments[i].student;
            }

        }
        int again = 1;
        while (again == 1) {
            int choice = -1;
            cout << "Enter courseNumber to edit specefic payment history" << endl;
            for (int i = 0; i < spayments.size(); i++) {
                cout << "Payment No " << i << endl;
            }
            cin >> choice;

            Payment payment;
            payment.student = student;

            cout << "Enter new tution fee: ";
            cin >> payment.tutionFee;
            cout << "Enter new laboraotory fee: ";
            cin >> payment.laboraotoryFee;
            cout << "Enter new library fee: ";
            cin >> payment.libraryFee;
            cout << "Enter new other fee: ";
            cin >> payment.others;

            payments[spayments[choice]] = payment;

            cout << "Want to modify another ? Press 1 else 0: " << endl;
            cin >> again;
        }
    }

    void newPayment() {
        Student student;
        Payment payment;
        cout << "Enter student id to pay: ";
        cin >> student.id;
        cout << "Enter tution fee: ";
        cin >> payment.tutionFee;
        cout << "Enter laboraotory fee: ";
        cin >> payment.laboraotoryFee;
        cout << "Enter library fee: ";
        cin >> payment.libraryFee;
        cout << "Enter new other fee: ";
        cin >> payment.others;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].id == student.id) {
                student = students[i];
                break;
            }
        }
        payment.student = student;
        payments.push_back(payment);
    }

    void viewStudentPaymentHistory() {
        for (int i = 0; i < payments.size(); i++) {
            if (payments[i].student.id == loggedStudent.id) {
                Payment payment = payments[i];
                cout << "Student Id: " << payment.student.id << endl;
                cout << "Student Name: " << payment.student.username << endl;
                cout << "Student Semester: " << payment.student.id << endl;
                cout << "Student Tution Fee: " << payment.tutionFee << endl;
                cout << "Student laboraotory Fee: " << payment.laboraotoryFee << endl;
                cout << "Student library Fee: " << payment.libraryFee << endl;
                cout << "Student others: " << payment.others << endl;
                cout << endl;
                cout << endl;
            }
        }
    }

    void saveStudentFees() {
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project25/studentFees.txt");
        MyFile << "Student Name" << "\t\t" << "Student Id" << "\t" << "Year" << "\t"
               << "Semester"
               << "\t" << "Tuition" << "\t" << "Laboratory" << "\t" << "Library" << "\t"
               << "Others" << endl;
        for (int i = 0; i < payments.size(); i++) {
            Payment payment = payments[i];
            MyFile << payment.student.username << "\t\t\t\t" << payment.student.id << "\t\t\t" << payment.student.year
                   << "\t\t"
                   << payment.student.semester.name
                   << "\t\t" << payment.tutionFee << "\t\t" << payment.laboraotoryFee << payment.libraryFee << "\t\t"
                   << payment.others << endl;
        }

        MyFile.close();
    }

    int checkLogin(string username, int password) {
        if ("admin" == username && 12345 == password) {
            return 0;
        }
        for (int i = 0; i < officials.size(); i++) {
            if (officials[i].username == username && officials[i].password == password) {
                return 1;
            }
        }
        for (int i = 0; i < students.size(); i++) {
            if (students[i].username == username && students[i].password == password) {
                loggedStudent = students[i];
                return 2;
            }
        }
    }

};

void startMenu(Admin &admin, int &isLogged, int &userType) {
    if (userType == 0) {


        int again = 1;
        while (again == 1) {
            int choice;
            cout << "1. View all semester\n";
            cout << "2. Add new official\n";
            cout << "3. Add new student\n";
            cout << "4. Add new semester\n";
            cout << "5. Add new payment\n";
            cout << "6. Delete semester\n";
            cout << "7. Edit  semester\n";
            cout << "8. Modify student info\n";
            cout << "9. See payment history for a student\n";
            cout << "10. Update payment history for a student\n";
            cout << "11. Save payment info to text file\n";
            cout << "12. Log out\n";
            cin >> choice;

            if (choice == 1) {
                admin.listSemester();
            } else if (choice == 2) {
                admin.registerNewOfficial();
            } else if (choice == 3) {
                admin.registerNewStudent();
            } else if (choice == 4) {
                admin.addNewSemester();
            } else if (choice == 5) {
                admin.newPayment();
            } else if (choice == 6) {
                admin.deleteSemester();
            } else if (choice == 7) {
                admin.editSemester();
            } else if (choice == 8) {
                admin.modifyStudentAccount();
            } else if (choice == 9) {
                admin.viewStudentsPaymentHistory();
            } else if (choice == 10) {
                admin.modifyStudentPaymentHistory();
            } else if (choice == 11) {
                admin.saveStudentFees();
            } else {
                isLogged = 1;
                userType = -1;
                return;
            }

            cout << "Press 1 to back to main menu: ";
            cin >> again;
        }


    } else if (userType == 1) {
        int again = 1;
        while (again == 1) {

            int choice;
            int number;
            cout << "1. Modify student info\n";
            cout << "2. New Payment\n";
            cout << "3. See payment history for a student\n";
            cout << "4. Update payment history for a student\n";
            cout << "5. Log out\n";
            cin >> choice;
            if (choice == 1) {
                admin.modifyStudentAccount();
            } else if (choice == 2) {
                admin.newPayment();
            } else if (choice == 3) {
                admin.viewStudentsPaymentHistory();
            } else if (choice == 4) {
                admin.modifyStudentPaymentHistory();
            } else {
                isLogged = 1;
                userType = -1;
                return;
            }

            cout << "Press 1 to back to main menu: ";
            cin >> again;
        }
    } else {
        int again = 1;
        while (again == 1) {

            int choice;
            int number;
            cout << "1. See payment history\n";
            cout << "2. Log out\n";
            cin >> choice;
            if (choice == 1) {
                admin.viewStudentPaymentHistory();
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
    Admin admin;
    string username;
    int password;
    int isLogged = 1;
    // 0 - admin, 1 - teahcer, 2 - student
    int userType = -1;
    while (isLogged == 1) {

        cout << "Enter login details" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (admin.checkLogin(username, password) == 0) {
            userType = 0;
        } else if (admin.checkLogin(username, password) == 1) {
            userType = 1;
        } else if (admin.checkLogin(username, password) == 2) {
            userType = 2;
        } else {
            cout << "Wrong details" << endl;
        }
        startMenu(admin, isLogged, userType);
    }
}

