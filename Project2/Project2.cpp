//
// Created by Shahriar Nasim Nafi on 1/10/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


string getDayName(int day) {
    if (day == 0) {
        return "sunday";
    } else if (day == 1) {
        return "monday";
    } else if (day == 2) {
        return "tuesday";
    } else if (day == 3) {
        return "wednesday";
    } else if (day == 4) {
        return "thursday";
    }
}

string getClassTime(int time) {
    if (time == 0) {
        return "9AM-10AM";
    } else if (time == 1) {
        return "0AM-11AM";
    } else if (time == 2) {
        return "11AM-12AM";
    } else if (time == 3) {
        return "12AM-1AM";
    } else {
        return "No Class";
    }
}


class aClass {

    string classroom;
    int courseNumber;
    int teacherId;
    int classTime;
    int day;
    bool isAssign;
public:
    const string &getClassroom() const {
        return classroom;
    }

    void setClassroom(const string &classroom) {
        aClass::classroom = classroom;
    }

    int getCourseNumber() const {
        return courseNumber;
    }

    void setCourseNumber(int courseNumber) {
        aClass::courseNumber = courseNumber;
    }

    int getTeacherId() const {
        return teacherId;
    }

    void setTeacherId(int teacherId) {
        aClass::teacherId = teacherId;
    }

    int getClassTime() const {
        return classTime;
    }

    void setClassTime(int classTime) {
        aClass::classTime = classTime;
    }

    int getDay() const {
        return day;
    }

    void setDay(int day) {
        aClass::day = day;
    }

    bool isActive1() const {
        return isAssign;
    }

    void setIsActive(bool isActive) {
        aClass::isAssign = isActive;
    }

    aClass() {
        isAssign = false;
    }
};

class Course {
    int courseNumber;

public:
    int getNumber() const {
        return courseNumber;
    }

    void setNumber(int number) {
        Course::courseNumber = number;
    }

    void newCourse() {
        cout << "Enter course courseNumber: ";
        cin >> courseNumber;
    }
};

class DailyClass {
public:
    string classroom;
    vector<vector<aClass>> days{{aClass(), aClass(), aClass(), aClass()},
                                {aClass(), aClass(), aClass(), aClass()},
                                {aClass(), aClass(), aClass(), aClass()},
                                {aClass(), aClass(), aClass(), aClass()},
                                {aClass(), aClass(), aClass(), aClass()}};


};

class Student {
private:
    int id;
    string username;
    string password;

public:
    int getId() const {
        return id;
    }

    const string &getUsername() const {
        return username;
    }

    const string &getPassword() const {
        return password;
    }

    void addNewStudent() {
        cout << "Enter student id: ";
        cin >> id;
        cout << "Enter student username: ";
        cin >> username;
        cout << "Enter student password: ";
        cin >> password;
    }

    void checkRoutine(int number, vector<DailyClass> dailyClasses) {
        vector<aClass> classes;
        for (int i = 0; i < dailyClasses.size();
             i++) {
            for (int j = 0; j < dailyClasses[i].days.size(); j++) {
                for (int k = 0; k < dailyClasses[i].days[j].size();
                     k++) {
                    aClass singleClass = dailyClasses[i].days[j][k];
                    if (singleClass.getCourseNumber() == number && singleClass.isActive1()) {
                        classes.push_back(singleClass);
                    }
                }
            }

        }
        cout << "All classes for course: " << number << endl;
        for (int i = 0; i < classes.size();
             i++) {
            aClass singleClass = classes[i];
            cout << "Classroom: " << singleClass.getClassroom() << " at "
                 << getClassTime(singleClass.getClassTime()) << " " << getDayName(singleClass.getDay()) << endl;
        }
    }
};

class Teacher {
private:
    int id;
    string username;
    string password;

public:
    int getId() const {
        return id;
    }

    const string &getUsername() const {
        return username;
    }

    const string &getPassword() const {
        return password;
    }

    void addNewTeacher() {
        cout << "Enter teacher id: ";
        cin >> id;
        cout << "Enter teacher username: ";
        cin >> username;
        cout << "Enter teacher password: ";
        cin >> password;
    }

    void checkRoutine(string classroom, vector<DailyClass> dailyClasses) {
        vector<aClass> classes;
        for (int i = 0; i < dailyClasses.size();
             i++) {
            if (dailyClasses[i].classroom == classroom) {
                for (int j = 0; j < dailyClasses[i].days.size(); j++) {
                    for (int k = 0; k < dailyClasses[i].days[j].size();
                         k++) {
                        aClass singleClass = dailyClasses[i].days[j][k];
                        if (singleClass.isActive1()) {
                            classes.push_back(singleClass);
                        }
                    }
                }
            }
        }

        cout << "Clases for Classroom: " << classroom << endl;

        for (int i = 0; i < classes.size();
             i++) {
            aClass singleClass = classes[i];
            cout << "Course: " << singleClass.getCourseNumber() << " at "
                 << getClassTime(singleClass.getClassTime()) << " " << getDayName(singleClass.getDay()) << endl;
        }
    }

    void checkRoutine(int day, vector<DailyClass> dailyClasses) {
        cout << "Day: " << day << endl;
        cout << "Id: " << id << endl;
        vector<aClass> clases;
        for (int i = 0; i < dailyClasses.size();
             i++) {
            for (int j = 0; j < dailyClasses[i].days[day].size();
                 j++) {
                aClass singleClass = dailyClasses[i].days[day][j];
                if (singleClass.getTeacherId() == id && singleClass.isActive1()) {
                    clases.push_back(singleClass);
                }
            }
        }

        cout << "Clases for day: " << getDayName(day) << endl;

        for (int i = 0; i < clases.size();
             i++) {
            aClass singleClass = clases[i];
            cout << "Classroom: " << singleClass.getClassroom() << " for course " << singleClass.getCourseNumber()
                 << " at "
                 << getClassTime(singleClass.getClassTime()) << endl;
        }
    }
};


class Classroom {
private:
    string name;

public:
    const string &getName() const {
        return name;
    }

    void addNewClassroom(string name) {
        this->name = name;
    }

};


class FileClassroom {
private:
    string name;

public:
    FileClassroom(string name) {
        this->name = name;
    }

public:
    string &getName() {
        return name;
    }
};

class Admin {
public:
    Teacher currentTeacher;
    Student currentStudent;
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Classroom> classrooms;
    vector<FileClassroom> fileClassrooms;
    vector<DailyClass> dailyClasses;
    vector<Course> courses;


    Admin() {
        loadFileClassrooms();
    }

    void addNewStudent() {
        Student student;
        student.addNewStudent();
        students.push_back(student);

    }

    void addNewTeacher() {
        Teacher teacher;
        teacher.addNewTeacher();
        teachers.push_back(teacher);

    }

    void addClassroom() {
        Classroom classroom;
        string name;
        cout << "Enter classroom name: ";
        cin >> name;
        if (checkClassroomExistInFileClassrooms(name)) {
            classroom.addNewClassroom(name);
            classrooms.push_back(classroom);
            DailyClass dailyClass;
            dailyClass.classroom = name;
            dailyClasses.push_back(dailyClass);
        } else {
            cout << "Classroom doesnt exist in the text file" << endl;
        }

    }


    void deleteClassroom() {
        string name;
        int index;
        cout << "Enter classroom name: ";
        cin >> name;
        for (int i = 0; i < classrooms.size(); i++) {
            if (classrooms[i].getName() == name) {
                index = i;
            }
        }

        classrooms.erase(classrooms.begin() + index);

        for (int i = 0; i < dailyClasses.size();
             i++) {
            if (dailyClasses[i].classroom == name) {
                index = i;
                break;
            }
        }

        dailyClasses.erase(dailyClasses.begin() + index);
    }


    void scheduleCourse() {
        Course course;
        int courseNumber = -1;
        int nextWeekDay = 0;
        DailyClass dailyClass;
        int classroomIndex = -1;
        for (int i = 0; i < classrooms.size(); i++) {
            cout << i << ": " << classrooms[i].getName() << endl;
        }
        cout << "Enter classroom index to add classes for this classroom: ";
        cin >> classroomIndex;
        dailyClass.classroom = classrooms[classroomIndex].getName();
        cout << "Enter  course courseNumber: ";
        cin >> courseNumber;
        course.setNumber(courseNumber);

        while (nextWeekDay < 5) {
            int time = -1;
            cout << "Class time for " << getDayName(nextWeekDay) << endl;
            cout
                    << "Class times\n0. 9AM-10AM \n1. 10AM-11AM \n2. 11AM-12AM \n3. 12AM-1AM \n4. No class in this day\nEnter one:  ";
            cin >> time;

            if (time != 4) {

                aClass singleClass;
                singleClass.setClassroom(dailyClass.classroom);
                singleClass.setCourseNumber(course.getNumber());
                singleClass.setClassTime(time);
                singleClass.setDay(nextWeekDay);
                singleClass.setIsActive(true);
                int teacherIndex;
                for (int i = 0; i < teachers.size(); i++) {
                    cout << i << " " << teachers[i].getUsername() << endl;
                }
                cout << "Enter teacher index: ";
                cin >> teacherIndex;

                singleClass.setTeacherId(teachers[teacherIndex].getId());

                if (!alreadyClassExisted(dailyClass.classroom, nextWeekDay, time)) {
                    assignClass(dailyClass.classroom, singleClass, nextWeekDay, time);
                } else {
                    cout << "Class already exist in this classroom at this time of "
                         << getDayName(nextWeekDay) << endl;
                }
            }
            nextWeekDay++;
        }
        courses.push_back(course);
    }

    void checkRoutine(string classroom) {
        vector<aClass> classes;
        for (int i = 0; i < dailyClasses.size();
             i++) {
            if (dailyClasses[i].classroom == classroom) {
                for (int j = 0; j < dailyClasses[i].days.size(); j++) {
                    for (int k = 0; k < dailyClasses[i].days[j].size();
                         k++) {
                        aClass singleClass = dailyClasses[i].days[j][k];
                        if (singleClass.isActive1()) {
                            classes.push_back(singleClass);
                        }
                    }
                }
            }
        }

        cout << "Clases for Classroom: " << classroom << endl;

        for (int i = 0; i < classes.size();
             i++) {
            aClass singleClass = classes[i];
            cout << "Course: " << singleClass.getCourseNumber() << " at "
                 << getClassTime(singleClass.getClassTime()) << " " << getDayName(singleClass.getDay()) << endl;
        }
    }

    void checkRoutine(int number) {
        vector<aClass> classes;
        for (int i = 0; i < dailyClasses.size();
             i++) {
            for (int j = 0; j < dailyClasses[i].days.size(); j++) {
                for (int k = 0; k < dailyClasses[i].days[j].size();
                     k++) {
                    aClass singleClass = dailyClasses[i].days[j][k];
                    if (singleClass.getCourseNumber() == number && singleClass.isActive1()) {
                        classes.push_back(singleClass);
                    }
                }
            }

        }
        cout << "All classes for course: " << number << endl;
        for (int i = 0; i < classes.size();
             i++) {
            aClass singleClass = classes[i];
            cout << "Classroom: " << singleClass.getClassroom() << " at "
                 << getClassTime(singleClass.getClassTime()) << " " << getDayName(singleClass.getDay()) << endl;
        }
    }

    int checkLoginDetails(string username, string password) {
        if ("admin" == username && "12345" == password) {
            return 1;
        }
        for (int i = 0; i < teachers.size(); i++) {
            if (teachers[i].getUsername() == username && teachers[i].getPassword() == password) {
                currentTeacher = teachers[i];
                return 2;
            }
        }
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getUsername() == username && students[i].getPassword() == password) {
                currentStudent = students[i];
                return 3;
            }
        }
    }


private:
    void loadFileClassrooms() {
        string classroomText;
        ifstream MyReadFile(
                "/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/SELF/_Project2_Idrak/classroom.txt");
        while (getline(MyReadFile, classroomText)) {
            stringstream ss(classroomText);
            string classroomName;
            while (ss >> classroomName) {
                FileClassroom fileClassroom = FileClassroom(classroomName);
                fileClassrooms.push_back(fileClassroom);
            }
        }
        MyReadFile.close();
    }

    bool checkClassroomExistInFileClassrooms(string name) {
        for (int i = 0; i < fileClassrooms.size(); i++) {
            if (fileClassrooms[i].getName() == name) {
                return true;
            }
        }
        return false;
    }


    bool alreadyClassExisted(string classroom, int day, int time) {
        DailyClass dailyClass;
        for (int i = 0; i < dailyClasses.size();
             i++) {
            if (dailyClasses[i].classroom == classroom) {
                dailyClass = dailyClasses[i];
                return dailyClass.days[day][time].isActive1();
            }
        }
        return true;
    }

    void assignClass(string classroom, aClass singleClass, int day, int time) {
        for (int i = 0; i < dailyClasses.size();
             i++) {
            if (dailyClasses[i].classroom == classroom) {
                dailyClasses[i].days[day][time] = singleClass;
                break;
            }
        }
    }
};


void startMenu(Admin &admin, int &isLogged, int &userType) {

    if (userType == 1) {

        int again = 1;
        while (again == 1) {
            int choice;
            cout << "1. View All classroom\n";
            cout << "2. Add new teacher\n";
            cout << "3. Add new student\n";
            cout << "4. Add new classroom\n";
            cout << "5. Delete classroom\n";
            cout << "6. Schedule new course\n";
            cout << "7. View routine for a classroom\n";
            cout << "8. Log out\n";
            cin >> choice;

            if (choice == 1) {
                for (int i = 0; i < admin.classrooms.size(); i++) {
                    cout << "Classroom: " << admin.classrooms[i].getName() << endl;
                }
            } else if (choice == 2) {
                admin.addNewTeacher();
            } else if (choice == 3) {
                admin.addNewStudent();
            } else if (choice == 4) {
                admin.addClassroom();
            } else if (choice == 5) {
                admin.deleteClassroom();
            } else if (choice == 6) {
                if (admin.classrooms.size() == 0) {
                    cout << "Please add at least one classroom first" << endl;
                } else if (admin.teachers.size() == 0) {
                    cout << "Please add at least one teacher first" << endl;
                } else {
                    admin.scheduleCourse();
                }
            } else if (choice == 7) {
                string classroom;
                cout << "Enter classroom name to show clases: ";
                cin >> classroom;
                for (int i = 0; i < admin.classrooms.size(); i++) {
                    if (admin.classrooms[i].getName() == classroom) {
                        admin.checkRoutine(classroom);
                    }
                }
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
            cout << "1. See routine for a classroom\n";
            cout << "2. See classes for a specific day\n";
            cout << "3. Log out\n";
            cin >> choice;
            if (choice == 1) {
                cout << "Enter classroom name to show clases: ";
                cin >> classroom;
                for (int i = 0; i < admin.classrooms.size(); i++) {
                    if (admin.classrooms[i].getName() == classroom) {
                        admin.currentTeacher.checkRoutine(classroom, admin.dailyClasses);
                    }
                }
            } else if (choice == 2) {
                cout << "Enter day name to show clases: 0.Sunday  1.Monday 2.Tuesday 3.Thursday 4.Wednesday ";
                cin >> number;
                admin.currentTeacher.checkRoutine(number, admin.dailyClasses);
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
            cout << "1. See clases for a course courseNumber\n";
            cout << "2. Log out\n";
            cin >> choice;
            if (choice == 1) {
                cout << "Enter course courseNumber to show clases: ";
                cin >> number;
                for (int i = 0; i < admin.courses.size(); i++) {
                    if (admin.courses[i].getNumber() == number) {
                        admin.currentStudent.checkRoutine(number, admin.dailyClasses);
                    }
                }
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
    string password;
    int isLogged = 1;
    // 1 - admin, 2 - teahcer, 3 - student
    int userType = -1;
    while (isLogged == 1) {

        cout << "Enter login details" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (admin.checkLoginDetails(username, password) == 1) {
            userType = 1;
        } else if (admin.checkLoginDetails(username, password) == 2) {
            userType = 2;
        } else if (admin.checkLoginDetails(username, password) == 3) {
            userType = 3;
        } else {
            cout << "Wrong details" << endl;
            return 0;
        }
        startMenu(admin, isLogged, userType);
    }
}




