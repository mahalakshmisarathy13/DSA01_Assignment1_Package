
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

enum class Zone { Inner, Middle, Outer };

class SmartCard {
private:
    long long balancePaise;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

public:
    explicit SmartCard(long long openingBalance)
        : balancePaise(openingBalance) {}

    bool canTravel(long long farePaise) const {
        return farePaise >= 0 &&
               balancePaise - farePaise >= MIN_BALANCE_PAISE;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise))
            return false;

        balancePaise -= farePaise;
        return true;
    }

    long long getBalance() const {
        return balancePaise;
    }
};

string getZoneName(Zone zone) {
    switch (zone) {
        case Zone::Inner: return "Inner";
        case Zone::Middle: return "Middle";
        case Zone::Outer: return "Outer";
    }
    return "";
}

long long calculateFare(Zone zone, bool peakHour) {
    long long fare = 0;

    switch (zone) {
        case Zone::Inner: fare = 1000; break;
        case Zone::Middle: fare = 2000; break;
        case Zone::Outer: fare = 3000; break;
    }

    if (peakHour)
        fare += 600;

    return fare;
}

int main() {
    SmartCard card(10000);

    string passenger = "Arun";
    string category = "Regular";

    cout << fixed << setprecision(2);

    cout << "NAMMA METRO SMART-CARD SYSTEM" << endl;
    cout << "Passenger: " << passenger << endl;
    cout << "Category: " << category << endl;

    // Journey 1
    Zone zone1 = Zone::Outer;
    bool peak1 = true;

    long long fare1 = calculateFare(zone1, peak1);

    cout << "\nJourney 1" << endl;
    cout << "Destination: " << getZoneName(zone1) << endl;
    cout << "Peak hour: " << (peak1 ? "Yes" : "No") << endl;
    cout << "Fare: Rs " << fare1 / 100.0 << endl;

    bool approved1 = card.deduct(fare1);

    cout << "Status: " << (approved1 ? "APPROVED" : "DENIED") << endl;
    cout << "Balance: Rs " << card.getBalance() / 100.0 << endl;

    // Journey 2
    Zone zone2 = Zone::Middle;
    bool peak2 = false;

    long long fare2 = calculateFare(zone2, peak2);

    cout << "\nJourney 2" << endl;
    cout << "Destination: " << getZoneName(zone2) << endl;
    cout << "Peak hour: " << (peak2 ? "Yes" : "No") << endl;
    cout << "Fare: Rs " << fare2 / 100.0 << endl;

    bool approved2 = card.deduct(fare2);

    cout << "Status: " << (approved2 ? "APPROVED" : "DENIED") << endl;
    cout << "Balance: Rs " << card.getBalance() / 100.0 << endl;

    return 0;
}
