#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

int main() {
    string passengerName;
    int zone = 0, hour = -1;
    long long balanceRupees = 0;

    cout << "Passenger name: ";
    getline(cin, passengerName);

    while (true) {
        cout << "Balance in rupees: ";
        if (cin >> balanceRupees && balanceRupees >= 0) break;
        cout << "Invalid balance. Enter a non-negative whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Zone (1=Inner, 2=Middle, 3=Outer): ";
        if (cin >> zone && zone >= 1 && zone <= 3) break;
        cout << "Invalid zone. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Hour (0-23): ";
        if (cin >> hour && hour >= 0 && hour <= 23) break;
        cout << "Invalid hour. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long long basePaise = zone * 1000LL;
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    long long farePaise = basePaise + (peak ? basePaise * 20 / 100 : 0);
    long long balancePaise = balanceRupees * 100;

    cout << "\n--- Journey Report ---\n";
    cout << "Passenger: " << passengerName << '\n';
    cout << "Fare: Rs " << farePaise / 100 << '.' << setw(2) << setfill('0')
         << farePaise % 100 << setfill(' ') << '\n';
    if (balancePaise - farePaise >= 5000) {
        balancePaise -= farePaise;
        cout << "Status: Allowed\n";
    } else {
        cout << "Status: Denied (minimum Rs 50 must remain)\n";
    }
    cout << "Remaining balance: Rs " << balancePaise / 100 << '.'
         << setw(2) << setfill('0') << balancePaise % 100 << setfill(' ') << '\n';
    return 0;
}
