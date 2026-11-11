#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}
bool calculateFare(int zoneInput, int hour, long long &farePaise) {
    if (hour < 0 || hour > 23) return false;
    long long base = 0;
    switch (zoneInput) {
        case 1: base = 1000; break;
        case 2: base = 2000; break;
        case 3: base = 3000; break;
        default: return false;
    }
    farePaise = base;
    if (isPeakHour(hour)) farePaise += base * PEAK_SURCHARGE_PERCENT / 100;
    return true;
}
void printMoney(long long paise) {
    cout << "Rs " << paise / 100 << '.' << setw(2) << setfill('0')
         << paise % 100 << setfill(' ');
}
int main() {
    long long balanceRupees;
    cout << "Enter opening balance (whole rupees): ";
    if (!(cin >> balanceRupees) || balanceRupees < 0) {
        cerr << "Invalid or negative balance.\n";
        return 1;
    }
    long long balance = balanceRupees * 100;
    int count;
    cout << "Number of journeys: ";
    if (!(cin >> count) || count < 0) {
        cerr << "Invalid journey count.\n";
        return 1;
    }

    for (int i = 1; i <= count; ++i) {
        int zone, hour;
        cout << "\nJourney " << i << " - zone (1 Inner, 2 Middle, 3 Outer): ";
        if (!(cin >> zone)) {
            cerr << "Invalid zone input.\n";
            return 1;
        }
        cout << "Hour (0-23): ";
        if (!(cin >> hour)) {
            cerr << "Invalid hour input.\n";
            return 1;
        }
        long long fare = 0;
        if (!calculateFare(zone, hour, fare)) {
            cout << "Rejected: invalid zone or hour. Balance unchanged: ";
            printMoney(balance); cout << '\n';
            continue;
        }
        cout << "Fare: "; printMoney(fare); cout << '\n';
        if (balance - fare >= MIN_BALANCE_PAISE) {
            balance -= fare;
            cout << "Status: Allowed\n";
        } else {
            cout << "Status: Denied (minimum Rs 50 must remain)\n";
        }
        cout << "Balance: "; printMoney(balance); cout << '\n';
    }
    return 0;
}
