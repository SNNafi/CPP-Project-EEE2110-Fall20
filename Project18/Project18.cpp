//
// Created by Shahriar Nasim Nafi on 29/9/21.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class Item {
public:
    int itemId;
    string itemName;
    int itemQuantity = 0;
    double itemPrice;
};

class Sale {
public:
    int invoiceId;
    string date;
    string customerName;
    vector<Item> items;
    int itemQuantity;


    Sale() {
        invoiceId = rand();
        itemQuantity = 0;
    }
};

class AllItems {
public:
    void addNewItem(vector<Item> &items) {
        Item item;
        cout << "Enter item id: ";
        cin >> item.itemId;
        cout << "Enter item name: ";
        cin >> item.itemName;
        cout << "Enter item quantity: ";
        cin >> item.itemQuantity;
        cout << "Enter item price: ";
        cin >> item.itemPrice;
        items.push_back(item);
    }

    void editItem(vector<Item> &items) {
        int choice;
        cout << "Look up by 1.Id or 2.Name.\nEnter one: ";
        cin >> choice;
        int id;
        string name;
        Item item;
        int itemIndex = -1;
        if (choice == 1) {
            cout << "Enter item id to edit: ";
            cin >> id;
            for (int i = 0; i < items.size(); i++) {
                if (items[i].itemId == id) {
                    item = items[i];
                    itemIndex = i;
                    break;
                }
            }
        } else {
            cout << "Enter item name to edit: ";
            cin >> name;
            for (int i = 0; i < items.size(); i++) {
                if (items[i].itemName == name) {
                    item = items[i];
                    itemIndex = i;
                    break;
                }
            }
        }


        cout << "Enter item id: ";
        cin >> item.itemId;
        cout << "Enter  item name: ";
        cin >> item.itemName;
        cout << "Enter item quantity: ";
        cin >> item.itemQuantity;
        cout << "Enter item price: ";
        cin >> item.itemPrice;
        items[itemIndex] = item;
    }

    void deleteItem(vector<Item> &items) {
        int choice;
        cout << "Look up by 1.Id or 2.Name.\nEnter one: ";
        cin >> choice;
        int id;
        string name;
        Item item;
        int itemIndex = -1;
        if (choice == 1) {
            cout << "Enter item id to delete: ";
            cin >> id;
            for (int i = 0; i < items.size(); i++) {
                if (items[i].itemId == id) {
                    item = items[i];
                    itemIndex = i;
                    break;
                }
            }
        } else {
            cout << "Enter item name to delete: ";
            cin >> name;
            for (int i = 0; i < items.size(); i++) {
                if (items[i].itemName == name) {
                    item = items[i];
                    itemIndex = i;
                    break;
                }
            }
        }

        items.erase(items.begin() + itemIndex);
    }

    void listItems(vector<Item> &items) {
        for (int i = 0; i < items.size(); i++) {
            cout << "Item " << i << endl;
            Item item = items[i];
            cout << "Item id: " << item.itemId;
            cout << "| Item name: " << item.itemName << endl;
            cout << "Item quantity: " << item.itemQuantity;
            cout << "| Item price: " << item.itemPrice << endl;
            cout << endl;
        }
    }


};


class SoldItems {
public:
    void addNewSale(AllItems &allItems, vector<Sale> &sales, vector<Item> &items, vector<Item> &soldItems) {
        int quantity = 0;
        int totalQuantity = 0;
        double totalPrice = 0;
        int again = 1;
        Sale sale = Sale();
        cout << "Enter your name: ";
        cin >> sale.customerName;
        cout << "Enter today's date: ";
        cin >> sale.date;

        while (again == 1) {
            Item item;
            int itemIndex = -1;
            int id;
            allItems.listItems(items);
            cout << "Enter item id from above to buy: ";
            cin >> id;
            for (int i = 0; i < items.size(); i++) {
                if (id == items[i].itemId) {
                    item = items[i];
                    itemIndex = i;
                    break;
                }
            }
            cout << "Enter item quantity: ";
            cin >> quantity;

            if (quantity <= item.itemQuantity) {
                items[itemIndex].itemQuantity -= quantity;
                totalQuantity += quantity;
                totalPrice += (item.itemPrice * quantity);
                sale.items.push_back(item);
                soldItems.push_back(item);
            } else {
                cout << "Not enough items to order" << endl;
                return;
            }

            cout << "Want to buy another ? Press 1 else 0: ";
            cin >> again;
        }
        sale.itemQuantity = totalQuantity;
        sales.push_back(sale);
    }

    void listsoldItems(vector<Item> &soldItems) {
        for (int i = 0; i < soldItems.size(); i++) {
            cout << "Sold Item " << i << endl;
            Item item = soldItems[i];
            cout << "Item id: " << item.itemId;
            cout << "| Item name: " << item.itemName << endl;
            cout << "Item quantity: " << item.itemQuantity;
            cout << "| Item price: " << item.itemPrice << endl;
            cout << endl;
        }
    }

    void totalSalesReport(vector<Sale> &sales) {
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project18/canteen.txt");
        MyFile << "Invoice ID\tCustomer Name\tDate\tTotal Items\n";
        for (int i = 0; i < sales.size(); i++) {
            Sale sale = sales[i];
            MyFile << sale.invoiceId << "\t\t" << sale.customerName << "\t\t" << sale.date << "\t" << sale.itemQuantity;
        }
        MyFile.close();
    }
};

int main() {

    vector<Item> items;
    vector<Item> solditems;
    vector<Sale> sales;
    AllItems allItems;
    SoldItems soldItems;
    int again = 1;
    int choice = 0;
    while (again == 1) {
        cout << "Please. choose your option" << endl;
        cout << "1. Add New Sale" << endl;
        cout << "2. View All Items" << endl;
        cout << "3. Sold Items" << endl;
        cout << "4. Add New Item" << endl;
        cout << "5. Edit Item" << endl;
        cout << "6. Delete Item" << endl;
        cout << "7. Total Sales Report" << endl;
        cout << "Select one: ";
        cin >> choice;
        if (choice == 1) {
            soldItems.addNewSale(allItems, sales, items, solditems);
        } else if (choice == 2) {
            allItems.listItems(items);
        } else if (choice == 3) {
            soldItems.listsoldItems(solditems);
        } else if (choice == 4) {
            allItems.addNewItem(items);
        } else if (choice == 5) {
            allItems.editItem(items);
        } else if (choice == 6) {
            allItems.deleteItem(items);
        } else if (choice == 7) {
            soldItems.totalSalesReport(sales);
        }
        cout << "Press 1  back  to main menu else 0: ";
        cin >> again;

    }

}