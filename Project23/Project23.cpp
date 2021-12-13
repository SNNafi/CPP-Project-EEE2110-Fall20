//
// Created by Shahriar Nasim Nafi on 30/9/21.
//

#include <iostream>

using namespace std;


class BankAccount {
protected:
    int accountNumber;
    double balance;

public:
    void setAccountNumber() {
        cout << "Enter account courseNumber: ";
        cin >> accountNumber;
    }

    int retrieveAccountNumber() {
        cout << "Account courseNumber:" << accountNumber << endl;
        return accountNumber;
    }

    double retrieveAccountBalance() {
        cout << "Account balance:" << balance << endl;
        return balance;
    }

    void depositMoney() {
        double deositAmount;
        cout << "Enter deposit amount: ";
        cin >> deositAmount;
        balance += deositAmount;

    }

    void withdrawMoney() {
        double withdrawAmount;
        cout << "Enter withdraw amount: ";
        cin >> withdrawAmount;
        if (withdrawAmount > balance) {
            cout << "Not enough balances to withdraw !" << endl;
            return;
        }
        balance -= withdrawAmount;
        cout << "Money withdrawed " << withdrawAmount << endl;

    }

    virtual void printAccountInfo() {
        cout << "Bank account : " << accountNumber << " has balance " << balance << endl;
    }
};

// oveeride
class CheckingAccount : public BankAccount {
protected:
    double interest;
    double minimalBalance = 100;
    double serviceCharge = 3;
    double interestRate = 0.1;

    virtual void writeCheck() {
        double amount;
        cout << "Enter amount to write check: ";
        cin >> amount;
        if (amount > balance) {
            cout << "Not enought balances to write check !" << endl;
            return;
        }
        balance -= amount;
        cout << "Check is written for " << amount << endl;
    }

    virtual double checkServiceCharge() {
        if (minimalBalance > balance) {
            cout << "Service Charge balance:" << serviceCharge << endl;
            return serviceCharge;
        }
        cout << "Service Charge balance:" << 0 << endl;
        return 0;
    }

    virtual double postInterest() {
        if (minimalBalance < balance) {
            interest = balance * interestRate;
            balance += interest;
            cout << "Post interest:" << interestRate << endl;
            return interest;
        } else {
            cout << "Post interest:" << 0 << endl;
        }
    }

    virtual void setInterestRate() {
        cout << "Set interest rate: ";
        cin >> interestRate;
    }

    virtual double getInterestRate() {
        cout << "Interest rate: " << interestRate << endl;
        return interestRate;
    }

    virtual void setMinimumBalance() {
        cout << "Set minimum balance: ";
        cin >> minimalBalance;
    }

    virtual double getMinimumBalance() {
        cout << "Minimal balance: " << minimalBalance << endl;
        return minimalBalance;
    }

    virtual void setServiceCharge() {
        cout << "Set service charge: ";
        cin >> serviceCharge;
    }


    virtual double getServiceCharge() {
        cout << "Service charge: " << serviceCharge << endl;
        return serviceCharge;
    }

    void printAccountInfo() override {
        cout << "Checking bank account : " << accountNumber << " has balance " << balance << " and interest rate is "
             << interestRate << endl;
    }

};

class SavingsAccount : public BankAccount {
protected:
    double interestRate = 0.1;

public:
    virtual double postInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "Post interest:" << interestRate;
        return interest;

    }

    void setInterestRate() {
        cout << "Set interest rate: ";
        cin >> interestRate;
    }

    double getInterestRate() {
        cout << "Interest rate: " << interestRate << endl;
        return interestRate;
    }

    void printAccountInfo()
    override {
        cout << "Savings bank account : " << accountNumber << " has balance " << balance << " and interest rate is "
             << interestRate <<
             endl;
    }
};

class HighInterestAccount : public SavingsAccount {
protected:
    double minimalBalance = 100;

public:
    virtual double postInterest() {
        if (minimalBalance < balance) {
            double interest = balance * interestRate;
            balance += interest;
            cout << "Post interest:" << interestRate << endl;
            return interest;
        } else {
            cout << "Post interest:" << 0 << endl;
            return 0;
        }
    }

    void setMinimumBalance() {
        cout << "Set minimum balance: ";
        cin >> minimalBalance;
    }

    double getMinimumBalance() {
        cout << "Minimal balance: " << minimalBalance << endl;
        return minimalBalance;
    }

    void printAccountInfo() override {
        cout << "HighInterest bank account : " << accountNumber << " has balance " << balance
             << " and interest rate is "
             << interestRate <<
             endl;
    }
};

class ServiceChargeChecking : public CheckingAccount {
protected:
    int totalCheckWrite = 3;
    int currentWritten = 0;


public:
    int getTotalCheckWrite() const {
        cout << "Total check written:" << totalCheckWrite << endl;
        return totalCheckWrite;
    }

    int getCurrentWritten() const {
        cout << "Current check written: " << currentWritten << endl;
        return currentWritten;
    }


    void writeCheck() override {
        double amount;
        cout << "Enter amount to write check: ";
        cin >> amount;
        if (amount > balance) {
            cout << "Not enough balances to write check !" << endl;
            return;
        } else if (totalCheckWrite > currentWritten) {
            cout << "Writing check limit crossed" << endl;
            return;
        }
        balance -= amount;
        currentWritten++;
        cout << "Check is written for " << amount << endl;
    }

    void printAccountInfo() override {
        cout << "Service Charge Checking bank account : " << accountNumber << " has balance " << balance
             << " and interest rate is "
             << interestRate <<
             endl;
    }

    void setServiceCharge() override {
        cout << "Set service charge: ";
        cin >> serviceCharge;
    }

    double getServiceCharge() override {
        cout << "Service charge: " << serviceCharge << endl;
        return serviceCharge;
    }

private:
    double postInterest() override {
    }

    void setInterestRate() override {

    }

    double getInterestRate() override {

    }

    void setMinimumBalance() override {

    }

    double getMinimumBalance() override {

    }


};

class NoServiceChargeChecking : public CheckingAccount {

public:
    void writeCheck() override {
        double amount;
        cout << "Enter amount to write check: ";
        cin >> amount;
        if (amount > balance) {
            cout << "Not enough balances to write check !" << endl;
            return;
        }
        balance -= amount;
        cout << "Check is written for " << amount << endl;
    }


    double postInterest() override {
        if (minimalBalance < balance) {
            interest = balance * interestRate;
            balance += interest;
            cout << "Post interest: " << interest << endl;
            return interest;
        } else {
            cout << "Post interest: " << 0 << endl;
            return 0;
        }
    }

    void setInterestRate() override {
        cout << "Set interest rate: ";
        cin >> interestRate;
    }

    double getInterestRate() override {
        cout << "Interest rate: " << interestRate << endl;
        return interestRate;
    }

    void setMinimumBalance() override {
        cout << "Set minimum balance: ";
        cin >> minimalBalance;
    }

    double getMinimumBalance() override {
        cout << "Minimal balance: " << minimalBalance << endl;
        return minimalBalance;
    }

    void printAccountInfo() override {
        cout << "No Service Charge Checking bank account : " << accountNumber << " has balance " << balance
             << " and interest rate is "
             << interestRate <<
             endl;
    }

private:
    void setServiceCharge() override {

    }

    double getServiceCharge() override {

    }
};


class HighInterestChecking : public NoServiceChargeChecking {

public:
    void writeCheck() override {
        double amount;
        cout << "Enter amount to write check: ";
        cin >> amount;
        if (amount > balance) {
            cout << "Not enough balances to write check !" << endl;
            return;
        }
        balance -= amount;
        cout << "Check is written for " << amount << endl;
    }


    double postInterest() override {
        if (minimalBalance < balance) {
            interest = balance * interestRate;
            balance += interest;
            cout << "Post interest: " << interest;
            return interest;
        } else {
            cout << "Post interest: " << 0;
            return 0;
        }
    }

    void setInterestRate() override {
        cout << "Set interest rate: ";
        cin >> interestRate;
    }

    double getInterestRate() override {
        cout << "Interest rate: " << interestRate << endl;
        return interestRate;
    }

    void setMinimumBalance() override {
        cout << "Set minimum balance: ";
        cin >> minimalBalance;
    }

    double getMinimumBalance() override {
        cout << "Minimum balance: " << minimalBalance << endl;
        return minimalBalance;
    }

    void printAccountInfo() override {
        cout << "High Interest Checking bank account : " << accountNumber << " has balance " << balance
             << " and interest rate is "
             << interestRate <<
             endl;
    }

private:
    void setServiceCharge() override {

    }

    double getServiceCharge() override {

    }
};

class CertificateOfDeposit : public BankAccount {
protected:
    int CDMaturityMonth = 6;
    int currentCDMaturityMonth = 1;
    double interestRate = 0.1;

public:
    int getMaturityMonth() const {
        cout << "Maturity month: " << CDMaturityMonth << endl;
        return CDMaturityMonth;
    }

    int getCurrentMaturityMonth() const {
        cout << "Current month: " << currentCDMaturityMonth << endl;
        return currentCDMaturityMonth;
    }

    double getInterestRate() const {
        cout << "Interest rate: " << interestRate << endl;
        return interestRate;
    }

    void setMaturityMonth() {
        cout << "Enter CD maturity month: " << endl;
        cin >> CDMaturityMonth;
    }

    void setCurrentMaturityMonth() {
        cout << "Enter current CD month: " << endl;
        cin >> currentCDMaturityMonth;
    }

    void setInterestRate() {
        cout << "Enter interest rate: " << endl;
        cin >> interestRate;
    }

    void printAccountInfo() override {
        cout << "Certificate Of Deposit bank account : " << accountNumber << " has balance " << balance
             << " and interest rate is "
             << interestRate <<
             endl;
    }
};


int main() {

// parent base super
// child, sub class
    SavingsAccount savingsAccount;
    HighInterestAccount highInterestAccount;
    ServiceChargeChecking serviceChargeChecking;
    NoServiceChargeChecking noServiceChargeChecking;
    HighInterestChecking highInterestChecking;
    CertificateOfDeposit certificateOfDeposit;

    // SavingsAccount
    int again = 1;
    while (again == 1) {

        int choice;
        cout << "1. Test Savings Account\n";
        cout << "2. Test HighInterestAccount Account\n";
        cout << "3. Test ServiceChargeChecking Account\n";
        cout << "4. Test NoServiceChargeChecking Account\n";
        cout << "5. Test HighInterestChecking Account\n";
        cout << "6. Test CertificateOfDeposit Account\n";
        cin >> choice;
        if (choice == 1) {
            int _again = 1;
            while (_again == 1) {
                int _choice = 1;
                cout << "Savings Account" << endl;
                cout << "1. Set account courseNumber\n";
                cout << "2. Get interest rate\n";
                cout << "3. Set interest rate\n";
                cout << "4. Desposit Money\n";
                cout << "5. Withdraw money\n";
                cout << "6. Retrieve balance\n";
                cout << "7. Retrieve account courseNumber\n";
                cout << "8. Post interest\n";
                cout << "9. Print account info\n";
                cout << "Select One: ";
                cin >> _choice;
                if (_choice == 1) {
                    savingsAccount.setAccountNumber();
                } else if (_choice == 2) {
                    savingsAccount.getInterestRate();
                } else if (_choice == 3) {
                    savingsAccount.setInterestRate();
                } else if (_choice == 4) {
                    savingsAccount.depositMoney();
                } else if (_choice == 5) {
                    savingsAccount.withdrawMoney();
                } else if (_choice == 6) {
                    savingsAccount.retrieveAccountBalance();
                } else if (_choice == 7) {
                    savingsAccount.retrieveAccountNumber();
                } else if (_choice == 8) {
                    savingsAccount.postInterest();
                } else if (_choice == 9) {
                    savingsAccount.printAccountInfo();
                }

                cout << "Press 1 to back to main menu: ";
                cin >> _again;
            }

        } else if (choice == 2) {
            int _again = 1;
            while (_again == 1) {
                int _choice = 1;
                cout << "HighInterestAccount Account" << endl;
                cout << "1. Set account courseNumber\n";
                cout << "2. Get interest rate\n";
                cout << "3. Set interest rate\n";
                cout << "4. Get minimum balance rate\n";
                cout << "5. Set minimum balance rate\n";
                cout << "6. Desposit Money\n";
                cout << "7. Withdraw money\n";
                cout << "8. Retrieve balance\n";
                cout << "9. Retrieve account courseNumber\n";
                cout << "10. Post interest\n";
                cout << "11. Print account info\n";
                cout << "Select One: ";
                cin >> _choice;
                if (_choice == 1) {
                    highInterestAccount.setAccountNumber();
                } else if (_choice == 2) {
                    highInterestAccount.getInterestRate();
                } else if (_choice == 3) {
                    highInterestAccount.setInterestRate();
                } else if (_choice == 4) {
                    highInterestAccount.getMinimumBalance();
                } else if (_choice == 5) {
                    highInterestAccount.setMinimumBalance();
                } else if (_choice == 6) {
                    highInterestAccount.depositMoney();
                } else if (_choice == 7) {
                    highInterestAccount.withdrawMoney();
                } else if (_choice == 8) {
                    highInterestAccount.retrieveAccountBalance();
                } else if (_choice == 9) {
                    highInterestAccount.retrieveAccountNumber();
                } else if (_choice == 10) {
                    highInterestAccount.postInterest();
                } else if (_choice == 11) {
                    highInterestAccount.printAccountInfo();
                }

                cout << "Press 1 to back to main menu: ";
                cin >> _again;
            }
        } else if (choice == 3) {
            int _again = 1;
            while (_again == 1) {
                int _choice = 1;
                cout << "Service Charge Checking Account" << endl;
                cout << "1. Set account courseNumber\n";
                cout << "2. Write check\n";
                cout << "3. Get total check limit\n";
                cout << "4. Get current check\n";
                cout << "5. Set service charge\n";
                cout << "6. Desposit Money\n";
                cout << "7. Withdraw money\n";
                cout << "8. Retrieve balance\n";
                cout << "9. Retrieve account courseNumber\n";
                cout << "10.Get service charge\n";
                cout << "11.Print account info\n";
                cout << "Select One: ";
                cin >> _choice;
                if (_choice == 1) {
                    serviceChargeChecking.setAccountNumber();
                } else if (_choice == 2) {
                    serviceChargeChecking.writeCheck();
                } else if (_choice == 3) {
                    serviceChargeChecking.getTotalCheckWrite();
                } else if (_choice == 4) {
                    serviceChargeChecking.getCurrentWritten();
                } else if (_choice == 5) {
                    serviceChargeChecking.setServiceCharge();
                } else if (_choice == 6) {
                    serviceChargeChecking.depositMoney();
                } else if (_choice == 7) {
                    serviceChargeChecking.withdrawMoney();
                } else if (_choice == 8) {
                    serviceChargeChecking.retrieveAccountBalance();
                } else if (_choice == 9) {
                    serviceChargeChecking.retrieveAccountNumber();
                } else if (_choice == 10) {
                    serviceChargeChecking.getServiceCharge();
                } else if (_choice == 11) {
                    serviceChargeChecking.printAccountInfo();
                }

                cout << "Press 1 to back to main menu: ";
                cin >> _again;
            }
        } else if (choice == 4) {
            int _again = 1;
            while (_again == 1) {
                int _choice = 1;
                cout << "No Service Charge Checking Account" << endl;
                cout << "1. Write check\n";
                cout << "2. Set account courseNumber\n";
                cout << "3. Get interest rate\n";
                cout << "4. Set interest rate\n";
                cout << "5. Get minimum balance rate\n";
                cout << "6. Set minimum balance rate\n";
                cout << "7. Desposit Money\n";
                cout << "8. Withdraw money\n";
                cout << "9. Retrieve balance\n";
                cout << "10.Retrieve account courseNumber\n";
                cout << "11.Post interest\n";
                cout << "12.Print account info\n";
                cout << "Select One: ";
                cin >> _choice;
                if (_choice == 1) {
                    noServiceChargeChecking.writeCheck();
                } else if (_choice == 2) {
                    noServiceChargeChecking.setAccountNumber();
                } else if (_choice == 3) {
                    noServiceChargeChecking.getInterestRate();
                } else if (_choice == 4) {
                    noServiceChargeChecking.setInterestRate();
                } else if (_choice == 5) {
                    noServiceChargeChecking.getMinimumBalance();
                } else if (_choice == 6) {
                    noServiceChargeChecking.setMinimumBalance();
                } else if (_choice == 7) {
                    noServiceChargeChecking.depositMoney();
                } else if (_choice == 8) {
                    noServiceChargeChecking.withdrawMoney();
                } else if (_choice == 9) {
                    noServiceChargeChecking.retrieveAccountBalance();
                } else if (_choice == 10) {
                    noServiceChargeChecking.retrieveAccountNumber();
                } else if (_choice == 11) {
                    noServiceChargeChecking.postInterest();
                } else if (_choice == 12) {
                    noServiceChargeChecking.printAccountInfo();
                }

                cout << "Press 1 to back to main menu: ";
                cin >> _again;
            }
        } else if (choice == 5) {
            int _again = 1;
            while (_again == 1) {
                int _choice = 1;
                cout << "High Interest Checking Account" << endl;
                cout << "1. Write check\n";
                cout << "2. Set account courseNumber\n";
                cout << "3. Get interest rate\n";
                cout << "4. Set interest rate\n";
                cout << "5. Get minimum balance rate\n";
                cout << "6. Set minimum balance rate\n";
                cout << "7. Desposit Money\n";
                cout << "8. Withdraw money\n";
                cout << "9. Retrieve balance\n";
                cout << "10.Retrieve account courseNumber\n";
                cout << "11.Post interest\n";
                cout << "12.Print account info\n";
                cout << "Select One: ";
                cin >> _choice;
                if (_choice == 1) {
                    highInterestChecking.writeCheck();
                } else if (_choice == 2) {
                    highInterestChecking.setAccountNumber();
                } else if (_choice == 3) {
                    noServiceChargeChecking.getInterestRate();
                } else if (_choice == 4) {
                    noServiceChargeChecking.setInterestRate();
                } else if (_choice == 5) {
                    noServiceChargeChecking.getMinimumBalance();
                } else if (_choice == 6) {
                    noServiceChargeChecking.setMinimumBalance();
                } else if (_choice == 7) {
                    noServiceChargeChecking.depositMoney();
                } else if (_choice == 8) {
                    noServiceChargeChecking.withdrawMoney();
                } else if (_choice == 9) {
                    noServiceChargeChecking.retrieveAccountBalance();
                } else if (_choice == 10) {
                    noServiceChargeChecking.retrieveAccountNumber();
                } else if (_choice == 11) {
                    noServiceChargeChecking.postInterest();
                } else if (_choice == 12) {
                    noServiceChargeChecking.printAccountInfo();
                }

                cout << "Press 1 to back to main menu: ";
                cin >> _again;
            }
        } else if (choice == 6) {
            int _again = 1;
            while (_again == 1) {
                int _choice = 1;
                cout << "CertificateOfDeposit Account" << endl;
                cout << "1. Set account courseNumber\n";
                cout << "2. Get interest rate\n";
                cout << "3. Set interest rate\n";
                cout << "4. Get CD maturity month\n";
                cout << "5. Set CD maturity month\n";
                cout << "6. Get CD current month\n";
                cout << "7. Set CD current month\n";
                cout << "8. Deposit money\n";
                cout << "9. Withdraw money\n";
                cout << "10.Retrieve balance\n";
                cout << "11.Retrieve account courseNumber\n";
                cout << "12.Print account info\n";
                cout << "Select One: ";
                cin >> _choice;
                if (_choice == 1) {
                    certificateOfDeposit.setAccountNumber();
                } else if (_choice == 2) {
                    certificateOfDeposit.getInterestRate();
                } else if (_choice == 3) {
                    certificateOfDeposit.setInterestRate();
                } else if (_choice == 4) {
                    certificateOfDeposit.getMaturityMonth();
                } else if (_choice == 5) {
                    certificateOfDeposit.setMaturityMonth();
                } else if (_choice == 6) {
                    certificateOfDeposit.getCurrentMaturityMonth();
                } else if (_choice == 7) {
                    certificateOfDeposit.setCurrentMaturityMonth();
                } else if (_choice == 8) {
                    certificateOfDeposit.depositMoney();
                } else if (_choice == 9) {
                    certificateOfDeposit.withdrawMoney();
                } else if (_choice == 10) {
                    certificateOfDeposit.retrieveAccountBalance();
                } else if (_choice == 11) {
                    certificateOfDeposit.retrieveAccountNumber();
                } else if (_choice == 12) {
                    certificateOfDeposit.printAccountInfo();
                }

                cout << "Press 1 to back to main menu: ";
                cin >> _again;
            }
        }

        cout << "Press 1 to back to main menu: ";
        cin >> again;
    }
}