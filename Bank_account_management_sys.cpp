#include <iostream>
#include <string>
using namespace std;

class bankAcc {
    int ac;
    string name;
    double balance;
    static double interest;

public:
    bankAcc() {}

    bankAcc(string n, int a, double b) {
        name = n;
        ac = a;
        balance = b;
    }

    bool deposit(double money) {
        if (money <= 0) return false;
        balance += money;
        return true;
    }

    bool withdraw(double money) {
        if (money <= 0 || money > balance) return false;
        balance -= money;
        return true;
    }

    void applyInterest() {
        balance += balance * interest;
    }

    void display() const {
        cout << "Account No.: " << ac << endl;
        cout << "Name      : " << name << endl;
        cout << "Balance   : " << balance << endl;
        cout << endl;
    }

    int getAccNo() const {
        return ac;
    }

    friend bool transfer(bankAcc &from, bankAcc &to, double amount);
};

double bankAcc::interest = 0.05;

bool transfer(bankAcc &from, bankAcc &to, double amount) {
    if (from.withdraw(amount)) {
        to.deposit(amount);
        return true;
    }
    return false;
}

int findAccount(bankAcc acc[], int n, int acno) {
    for (int i = 0; i < n; i++) {
        if (acc[i].getAccNo() == acno)
            return i;
    }
    return -1;
}

int main() {
    int n;
    cout << "Enter number of accounts: ";
    cin >> n;

    bankAcc acc[n];

    for (int i = 0; i < n; i++) {
        string name;
        int acno;
        double bal;

        cout << "\nEnter details for Account " << i + 1 << endl;
        cout << "Account No: ";
        cin >> acno;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Initial Balance: ";
        cin >> bal;

        acc[i] = bankAcc(name, acno, bal);
    }

    int choice;
    do {
        cout << "\n BANK MANAGEMENT SYSTEM \n";
        cout << "1. Display All Accounts\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Apply Interest to All\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int acno, idx, toIdx;
        double amt;

        switch (choice) {
            case 1:
                for (int i = 0; i < n; i++)
                    acc[i].display();
                break;

            case 2:
                cout << "Enter account number: ";
                cin >> acno;
                idx = findAccount(acc, n, acno);
                if (idx == -1) {
                    cout << "Account not found\n";
                    break;
                }
                cout << "Enter amount to deposit: ";
                cin >> amt;
                if (acc[idx].deposit(amt))
                    cout << "Deposit successful\n";
                else
                    cout << "Invalid amount\n";
                break;

            case 3:
                cout << "Enter account number: ";
                cin >> acno;
                idx = findAccount(acc, n, acno);
                if (idx == -1) {
                    cout << "Account not found\n";
                    break;
                }
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                if (acc[idx].withdraw(amt))
                    cout << "Withdrawal successful\n";
                else
                    cout << "Insufficient balance / Invalid amount\n";
                break;

            case 4:
                int fromAc, toAc;
                cout << "From account number: ";
                cin >> fromAc;
                cout << "To account number: ";
                cin >> toAc;

                idx = findAccount(acc, n, fromAc);
                toIdx = findAccount(acc, n, toAc);

                if (idx == -1 || toIdx == -1) {
                    cout << "Invalid account number\n";
                    break;
                }

                cout << "Enter amount to transfer: ";
                cin >> amt;

                if (transfer(acc[idx], acc[toIdx], amt))
                    cout << "Transfer successful\n";
                else
                    cout << "Transfer failed\n";
                break;

            case 5:
                for (int i = 0; i < n; i++)
                    acc[i].applyInterest();
                cout << "Interest applied to all accounts\n";
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }
    } 
    while (choice != 6);

    return 0;
}
