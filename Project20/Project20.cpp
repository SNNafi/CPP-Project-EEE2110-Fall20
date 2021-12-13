//
// Created by Shahriar Nasim Nafi on 30/9/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Medicine {
public:
    string name;
    string companyName;
    int quantity;
    double unitPrice;
    string arrivalDate;
    string expireDate;
};


class Sale {
public:
    int invoiceId;
    string date;
    string customerName;
    vector<Medicine> medicines;
    int itemQuantity;
    double totalPrice;

    // special trype of function
    Sale() {
        // random// auto
        invoiceId = rand();
        itemQuantity = 0;
    }
};


class AddNewSale {
public:

    vector<Medicine> medicines;

    // constructor
    AddNewSale() {
        loadMedicines();
    }

    void listMedicine() {
        for (int i = 0; i < medicines.size(); i++) {
            Medicine medicine = medicines[i];
            cout << "Medicine " << i << " info" << endl;
            cout << "Name: " << medicine.name << endl;
            cout << "Company name: " << medicine.companyName << endl;
            cout << "Quantity: " << medicine.quantity << endl;
            cout << "Price: " << medicine.unitPrice << endl;
            cout << "Arrival date " << medicine.arrivalDate << endl;
            cout << "Expire date: " << medicine.expireDate << endl;
            cout << endl;
        }
    }

    void addNewMedicine() {
        Medicine medicine;
        cout << "Enter medicine name: ";
        cin >> medicine.name;
        cout << "Enter medicine company name: ";
        cin >> medicine.companyName;
        cout << "Enter medicine quantity: ";
        cin >> medicine.quantity;
        cout << "Enter medicine price: ";
        cin >> medicine.unitPrice;
        cout << "Enter medicine arrival date: ";
        cin >> medicine.arrivalDate;
        cout << "Enter medicine expire date: ";
        cin >> medicine.expireDate;
        medicines.push_back(medicine);
        updateMedicines();
    }

    void updateMedicineDetails() {

        Medicine medicine;
        cout << "Enter medicine name to edit: " << endl;
        cin >> medicine.name;
        int index = -1;
        for (int i = 0; i < medicines.size(); i++) {
            if (medicine.name == medicines[i].name) {
                medicine = medicines[i];
                index = i;
                break;
            }
        }
        cout << "Enter medicine new name: ";
        cin >> medicine.name;
        cout << "Enter medicine company new name: ";
        cin >> medicine.companyName;
        cout << "Enter medicine new quantity: ";
        cin >> medicine.quantity;
        cout << "Enter medicine new price: ";
        cin >> medicine.unitPrice;
        cout << "Enter medicine new arrival date: ";
        cin >> medicine.arrivalDate;
        cout << "Enter medicine new expire date: ";
        cin >> medicine.expireDate;

        medicines[index] = medicine;
        updateMedicines();
    }

    void deleteMedicineFromStock() {
        string name;
        cout << "Enter medicine name to delete: " << endl;
        cin >> name;
        int index = -1;
        // 0 1 2 3 4 5 6
        for (int i = 0; i < medicines.size(); i++) {
            if (name == medicines[i].name) {
                index = i;
                break;
            }
        }
        // delete
        medicines.erase(medicines.begin() + index);
        updateMedicines();
    }

private:
    void loadMedicines() {
        string medicineText;
        int count = 1;
        ifstream MyReadFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project20/medicine.txt");
        while (getline(MyReadFile, medicineText)) {
            if (count != 1) {
                Medicine medicine;
                stringstream ss(medicineText);
                string info;
                int index = 1;
                while (ss >> info) {
                    if (index == 1) {
                        medicine.name = info;
                    } else if (index == 2) {
                        medicine.companyName = info;
                    } else if (index == 3) {
                        stringstream toInt(info);
                        toInt >> medicine.unitPrice;
                    } else if (index == 4) {
                        stringstream toInt(info);
                        toInt >> medicine.quantity;
                    } else if (index == 5) {
                        medicine.arrivalDate = info;
                    } else if (index == 6) {
                        medicine.expireDate = info;
                    }
                    index++;
                }
                medicines.push_back(medicine);
            }
            count++;
        }
        MyReadFile.close();
    }

    void updateMedicines() {
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project20/medicine.txt");
        MyFile << "Medicine Name\tCompany\tUnit Price\tQuantity\tArival Date\tExpiry Date\n";
        for (int i = 0; i < medicines.size(); i++) {
            Medicine medicine = medicines[i];
            MyFile << medicine.name << "\t\t" << medicine.companyName << "\t\t" << medicine.unitPrice << "\t\t"
                   << medicine.quantity
                   << "\t\t" << medicine.arrivalDate << "\t\t" << medicine.expireDate << endl;
        }
        MyFile.close();
    }
};

class SoldMedicineList {
public:
    void addNewSales(AddNewSale &addNewSale, vector<Sale> &sales, vector<Medicine> &medicines,
                     vector<Medicine> &soldMedicines) {
        int quantity = 0;
        int totalQuantity = 0;
        double totalPrice = 0;
        int again = 1;
        Sale sale = Sale();
        cout << "Enter customer name: ";
        cin >> sale.customerName;
        cout << "Enter today's date: ";
        cin >> sale.date;
        while (again == 1) {
            Medicine medicine;
            int number;
            addNewSale.listMedicine();
            cout << "Enter medicine number from above to buy: ";
            cin >> number;
            for (int i = 0; i < medicines.size(); i++) {
                if (number == i) {
                    medicine = medicines[i];
                    break;
                }
            }
            cout << "Enter medicine quantity: ";
            cin >> quantity;

            if (quantity <= medicine.quantity) {
                sale.medicines.push_back(medicine);
                medicines[number].quantity -= quantity;
                totalQuantity += quantity;
                totalPrice += (medicine.unitPrice * quantity);
                soldMedicines.push_back(medicine);
            } else {
                cout << "Not enough medicines to order" << endl;
                return;
            }

            cout << "Want to buy another ? Press 1 else 0: ";
            cin >> again;
        }
        sale.itemQuantity = totalQuantity;
        sale.totalPrice = totalPrice;
        sales.push_back(sale);
    }

    void soldMedicineList(vector<Medicine> &soldMedicines) {
        for (int i = 0; i < soldMedicines.size(); i++) {
            Medicine medicine = soldMedicines[i];
            cout << "Sold Medicine " << i + 1 << " info" << endl;
            cout << "Name: " << medicine.name << endl;
            cout << "Company name: " << medicine.companyName << endl;
            cout << "Quantity: " << medicine.quantity << endl;
            cout << "Price: " << medicine.unitPrice << endl;
            cout << "Arrival date " << medicine.arrivalDate << endl;
            cout << "Expire date: " << medicine.expireDate << endl;
            cout << endl;
        }
    }


    void totalSalesReport(vector<Sale> &sales) {
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project20/pharmacy.txt");
        MyFile << "Invoice ID\tCustomer Name\tDate\tTotal Medincines\n";
        for (int i = 0; i < sales.size(); i++) {
            Sale sale = sales[i];
            MyFile << sale.invoiceId << "\t\t" << sale.customerName << "\t\t" << sale.date << "\t" << sale.itemQuantity;
        }
        MyFile.close();
    }
};

int main() {
    vector<Medicine> soldMedicines;
    vector<Sale> sales;
    AddNewSale addNewSale = AddNewSale();
    SoldMedicineList soldMedicineList;
    int again = 1;
    int choice = 0;
    while (again == 1) {
        cout << "Please. choose your option" << endl;
        cout << "1. Add New Sale" << endl;
        cout << "2. View all mediciens" << endl;
        cout << "3. Sold medicien" << endl;
        cout << "4. Add new mediciens" << endl;
        cout << "5. Edit medicine" << endl;
        cout << "6. Delete medicine" << endl;
        cout << "7. Generate total sales report" << endl;
        cout << "Select one: ";
        cin >> choice;
        if (choice == 1) {
            soldMedicineList.addNewSales(addNewSale, sales, addNewSale.medicines, soldMedicines);
        } else if (choice == 2) {
            addNewSale.listMedicine();
        } else if (choice == 3) {
            soldMedicineList.soldMedicineList(soldMedicines);
        } else if (choice == 4) {
            addNewSale.addNewMedicine();
        } else if (choice == 5) {
            addNewSale.updateMedicineDetails();
        } else if (choice == 6) {
            addNewSale.deleteMedicineFromStock();
        } else if (choice == 7) {
            soldMedicineList.totalSalesReport(sales);
        }
        cout << "Press 1  back  to main menu else 0: ";
        cin >> again;

    }
}


// struct // class