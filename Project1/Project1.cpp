//
// Created by Shahriar Nasim Nafi on 1/10/21.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


// Weeks
const int SUNDAY = 0;
const int MONDAY = 1;
const int TUESDAY = 2;
const int WEDNESDAY = 3;
const int THURSDAY = 4;

string weekName(int day) {
    if (day == 0) {
        return "sunday";
    } else if (day == 1) {
        return "monday";
    } else if (day == 2) {
        return "tuesday";
    } else if (day == 3) {
        return "wednesday";
    } else {
        return "thursday";
    }
}


class StudentActivity {
public:
    int studentId;
    int attendence = 0;
    int performance = 0;
    int givenByTeacher = -1;
};


class StudentData {
public:
    vector<vector<StudentActivity>> days = {{},
                                            {},
                                            {},
                                            {},
                                            {}};
};

class Student {
public:
    int id;
    string username;
    int password;

    void giveAttendance(StudentData &data, int today) {
        StudentActivity studentActivity;
        studentActivity.studentId = id;
        studentActivity.attendence = 1;
        data.days[today].push_back(studentActivity);

    }

    void seePerformance(StudentData &data) {
        int day;
        cout << "Enter day to show 0.Sunday  1.Monday 2.Tuesday 3.Thursday 4.Wednesday: " << endl;
        cin >> day;
        for (int i = 0; i < data.days[day].size(); i++) {
            if (data.days[day][i].studentId == id && data.days[day][i].attendence) {
                cout << "Performance: "
                     << data.days[day][i].performance << " in " << weekName(day) << endl;
            }
        }
    }
};

class Teacher {
public:
    int id;
    string username;
    int password;

    void seePerformance(StudentData &data) {
        int day;
        cout << "Enter day to show 0.Sunday  1.Monday 2.Tuesday 3.Thursday 4.Wednesday: " << endl;
        cin >> day;
        for (int i = 0; i < data.days[day].size(); i++) {
            if (data.days[day][i].givenByTeacher == id && data.days[day][i].attendence) {
                cout << "Performance for student id " << data.days[day][i].studentId << " is "
                     << data.days[day][i].performance << " in " << weekName(day) << endl;
            }
        }
    }

    void seeAttendence(StudentData &data) {
        int day;
        cout << "Enter day to show 0.Sunday  1.Monday 2.Tuesday 3.Thursday 4.Wednesday: " << endl;
        cin >> day;
        for (int i = 0; i < data.days[day].size(); i++) {
            if (data.days[day][i].givenByTeacher == id) {
                cout << "Attendence for student id " << data.days[day][i].studentId << " is "
                     << data.days[day][i].attendence << " in " << weekName(day) << endl;
            }
        }
    }

    void givePerformance(StudentData &data, int today) {
        for (int i = 0; i < data.days[today].size(); i++) {
            int p = 0;
            cout << "Give performance [1 - 10] for student id: " << data.days[today][i].studentId << " in "
                 << weekName(today) << ": ";
            cin >> p;
            data.days[today][i].performance = p;
            data.days[today][i].givenByTeacher = id;
        }
    }

};

class Admin {
public:
    vector<Teacher> teachers;
    vector<Student> students;
    Teacher currentTeacher;
    Student currentStudent;


    void seePerformance(StudentData &data) {
        int day;
        cout << "Enter day to show 0.Sunday 1.Monday 2.Tuesday 3.Thursday 4.Wednesday: " << endl;
        cin >> day;
        for (int i = 0; i < data.days[day].size(); i++) {
            if (data.days[day][i].attendence) {
                cout << "Performance for student id " << data.days[day][i].studentId << " is "
                     << data.days[day][i].performance << " in " << weekName(day) << endl;
            }
        }
    }


    void registerNewTecher() {
        Teacher teacher;
        cout << "Enter teacher id: ";
        cin >> teacher.id;
        cout << "Enter teacher username: ";
        cin >> teacher.username;
        cout << "Enter teacher password: ";
        cin >> teacher.password;
        teachers.push_back(teacher);
    }

    void registerNewStudent() {
        Student student;
        cout << "Enter student id: ";
        cin >> student.id;
        cout << "Enter student username: ";
        cin >> student.username;
        cout << "Enter student password: ";
        cin >> student.password;
        students.push_back(student);
    }

    int checkLogin(string username, int password) {
        if ("admin" == username && 12345 == password) {
            return 1;
        }
        for (int i = 0; i < teachers.size(); i++) {
            if (teachers[i].username == username && teachers[i].password == password) {
                currentTeacher = teachers[i];
                return 2;
            }
        }
        for (int i = 0; i < students.size(); i++) {
            if (students[i].username == username && students[i].password == password) {
                currentStudent = students[i];
                return 3;
            }
        }
    }

    void saveInDatabase(StudentData &data, int today) {
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project1/studentDb.txt");
        MyFile << "Name\tAttendence\tPerformance" << endl;
        for (int i = 0; i < data.days[today].size(); i++) {
            if (data.days[today][i].attendence) {
                MyFile << getStudentNameById(data.days[today][i].studentId) << "\t\t" << data.days[today][i].attendence
                       << "\t\t"
                       << data.days[today][i].performance << "\t\t" << endl;

            }
        }
        MyFile.close();
    }

private:
    string getStudentNameById(int id) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].id == id) {
                return students[i].username;
            }
        }
    }
};


void works(Admin &admin, StudentData &data, int &isLogged, int &userType, int &date) {

    if (userType == 1) {
        int again = 1;
        while (again == 1) {
            int choice;
            cout << "1. View all students\n";
            cout << "2. View all teachers\n";
            cout << "3. Add new teacher\n";
            cout << "4. Add new student\n";
            cout << "5. See performances\n";
            cout << "6. Save to text file\n";
            cout << "7. Log out\n";
            cin >> choice;

            if (choice == 1) {
                for (int i = 0; i < admin.students.size(); i++) {
                    cout << "Student Name: " << admin.students[i].username << " ID: " << admin.students[i].id << endl;
                }
            } else if (choice == 2) {
                for (int i = 0; i < admin.teachers.size(); i++) {
                    cout << "Teacher Name: " << admin.teachers[i].username << " ID: " << admin.teachers[i].id << endl;
                }
            } else if (choice == 3) {
                admin.registerNewTecher();
            } else if (choice == 4) {
                admin.registerNewStudent();
            } else if (choice == 5) {
                admin.seePerformance(data);
            } else if (choice == 6) {
                admin.saveInDatabase(data, date);
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

            int number;
            string classroom;
            int choice;
            cout << "1. See attendence\n";
            cout << "2. See performances\n";
            cout << "3. Give performances\n";
            cout << "4. Log out\n";
            cin >> choice;
            if (choice == 1) {
                admin.currentTeacher.seeAttendence(data);
            } else if (choice == 2) {
                admin.currentTeacher.seePerformance(data);
            } else if (choice == 3) {
                admin.currentTeacher.givePerformance(data, date);
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
            cout << "1. Give attendence\n";
            cout << "2. See performance\n";
            cout << "3. Log out\n";
            cin >> choice;
            if (choice == 1) {
                admin.currentStudent.giveAttendance(data, date);
            } else if (choice == 2) {
                admin.currentStudent.seePerformance(data);
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
    StudentData data;
    string username;
    int password;
    int isLogged = 1;
    int date = 2;
    // 1 - admin, 2 - teahcer, 3 - student
    int userType = -1;
    while (isLogged == 1) {

        cout << "Enter login details" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (admin.checkLogin(username, password) == 1) {
            userType = 1;
        } else if (admin.checkLogin(username, password) == 2) {
            userType = 2;
        } else if (admin.checkLogin(username, password) == 3) {
            userType = 3;
        } else {
            cout << "Wrong details" << endl;
        }
        works(admin, data, isLogged, userType, date);
    }

}

