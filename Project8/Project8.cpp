//
// Created by Shahriar Nasim Nafi on 28/9/21.
//

#include <iostream> // input output
#include <vector>  //
#include <fstream> // file stram

using namespace std;


class Doctor {
public:
    string doctorName;

    // selectedDate = 1, selectedTime = 3
    // false true true true // 0
    // 0     1    2     3
    // false true true true  1

    // false true false true  2
    // 0    1
    // false true false true   3

    // false true false true  4
    vector<vector<bool>> days;


    // constructor is a special type
    // when object is created
    Doctor(string name) {
        // instance
        // it will refer to the current object of this class
        this->doctorName = name;
        readFromFile(name);

    }

private:
    void readFromFile(string name) {
        string schedules;
        if (name == "Dr. A") {
            ifstream MyReadFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project8/drA.txt");
            while (getline(MyReadFile, schedules)) {
                vector<bool> day;
                day.push_back(schedules[0] == 'Y');
                day.push_back(schedules[2] == 'Y');
                day.push_back(schedules[4] == 'Y');
                day.push_back(schedules[5] == 'Y');
                days.push_back(day);
            }
            MyReadFile.close();
        } else {
            ifstream MyReadFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project8/drB.txt");
            while (getline(MyReadFile, schedules)) {
                vector<bool> day;
                day.push_back(schedules[0] == 'Y');
                day.push_back(schedules[2] == 'Y');
                day.push_back(schedules[4] == 'Y');
                day.push_back(schedules[5] == 'Y');
                days.push_back(day);
            }
            MyReadFile.close();
        }

    }
};

class Patient {
public:
    string name;
    int age;
    int cellNo;
    string doctor;
    int day;
    int time;
};

// by default public - struct
// by default private - class

class Hospital {
public:
    vector<Patient> patients;
    // 1 -> A 2 -> B
    int selectedDoctor = 0;
    int selectedDate = 0;
    int selectedTime = 0;

    Hospital() {
    }

private:
    ofstream registeredPatients;
public:

    void selectAppointment(Doctor &doctor, int &recheck) {

        cout << "Medical Hospital" << endl;
        cout << "Select Doctor\n" << "------------------" << endl;
        cout << "1: Dr. A" << endl;
        cout << "2: Dr. B" << endl;
        cout << "Select ONE: ";
        cin >> selectedDoctor;
        cout << "Select One of following DATE\n" << "-----------------------------" << endl;
        cout << "0: Monday" << endl;
        cout << "1: Tuesday" << endl;
        cout << "2: Wednesday" << endl;
        cout << "3: Thrusday" << endl;
        cout << "4: Friday" << endl;
        cout << "Select ONE: ";
        cin >> selectedDate;
        cout << "Select One of following time\n" << "-----------------------------" << endl;
        cout << "0: 10 AM - 11 AM" << endl;
        cout << "1: 12 AM - 1 PM" << endl;
        cout << "2: 2 PM - 3 PM" << endl;
        cout << "3: 4 PM - 5 PM" << endl;
        cout << "Select ONE: ";
        cin >> selectedTime;
        if (checkDoctorAvailable(doctor)) {
            registerPatient(doctor, recheck);
        } else {
            int choice = 0;
            cout << "Doctor not available. Do you want check another schedule ?" << endl;
            cout << "1: Check Another" << endl << "2: End Program" << endl;
            cout << "Select ONE: ";
            cin >> choice;
            if (choice == 1) {
                recheck = true;
                return;
            } else {
                recheck = false;
                return;
            }
        }

    }


    void registerPatient(Doctor &doctor, int &recheck) {
        Patient patient;
        cout << "Enter info for registration" << endl;
        cout << "Enter name: ";
        cin >> patient.name;
        cout << "Enter age: ";
        cin >> patient.age;
        cout << "Enter cell: ";
        cin >> patient.cellNo;
        patient.doctor = doctor.doctorName;
        patient.day = selectedDate;
        patient.time = selectedTime;
        patients.push_back(patient);
        saveDoctorAppointment(doctor);

        string doctorName = selectedDoctor == 1 ? "Dr. A" : "Dr. B";
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project8/rp.txt");
        MyFile << "Patient Name\tAge\tCell No\tDoctor Name\tDay\tTime\n";
        MyFile << patient.name << "\t\t" << patient.age << "\t\t" << patient.cellNo << "\t\t"
               << doctorName
               << "\t\t" << selectedDate << "\t\t" << selectedTime;
        MyFile.close();
        cout << "Succesfully registerd ! Thank you" << endl;
        recheck = false;

    }


    //  !true = false
    bool checkDoctorAvailable(Doctor &doctor) {
        return !doctor.days[selectedDate][selectedTime];
    }

    void saveDoctorAppointment(Doctor &doctor) {
        doctor.days[selectedDate][selectedTime] = true;
    }


};


int main() {


    // pbject
    Hospital hospital = Hospital();

    // standard
    // instance / object
    Doctor doctorA = Doctor("Dr. A");
    Doctor doctorB = Doctor("Dr. B");
    int recheck = true;

    while (recheck == true) {
        hospital.selectAppointment(hospital.selectedDoctor == 1 ? doctorA : doctorB, recheck);
    }

}