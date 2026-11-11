#include <iostream>
#include <array>
#include <string>
using namespace std;

enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };
constexpr array<long long, 4> FARES = {1000, 2000, 3000, 6000};
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}
long long calculateFare(Zone zone, int hour, bool weekend) {
    int index = static_cast<int>(zone);
    if (index < 0 || index >= static_cast<int>(FARES.size()) || hour < 0 || hour > 23)
        return -1;
    long long base = FARES[static_cast<size_t>(index)];
    if (weekend) {
        // Weekend discount replaces peak surcharge; they do not combine.
        return base - (base * WEEKEND_DISCOUNT_PERCENT / 100);
    }
    if (isPeakHour(hour)) base += base * PEAK_PERCENT / 100;
    return base;
}

class Pass {
private:
    Zone firstZone;
    Zone secondZone;
    bool active;
public:
    Pass(Zone a, Zone b, bool isActive = true)
        : firstZone(a), secondZone(b), active(isActive) {}
    bool covers(Zone zone) const {
        return active && (zone == firstZone || zone == secondZone);
    }
};

class SmartCard {
private:
    long long balancePaise;
public:
    explicit SmartCard(long long initial) : balancePaise(initial) {}
    bool pay(long long farePaise) {
        if (farePaise < 0 || balancePaise - farePaise < MIN_BALANCE_PAISE)
            return false;
        balancePaise -= farePaise;
        return true;
    }
    long long balance() const { return balancePaise; }
};

string zoneName(Zone z) {
    switch (z) {
        case Zone::Inner: return "Inner";
        case Zone::Middle: return "Middle";
        case Zone::Outer: return "Outer";
        case Zone::Airport: return "Airport";
    }
    return "Invalid";
}
int main() {
    SmartCard card(20000); // Rs 200
    Pass monthlyPass(Zone::Inner, Zone::Airport);

    struct Trip { Zone zone; int hour; bool weekend; };
    Trip trips[] = {
        {Zone::Airport, 12, false}, // Rs 60
        {Zone::Airport, 18, false}, // Rs 72
        {Zone::Airport, 18, true},  // Rs 54; weekend replaces peak
        {Zone::Outer, 12, true},    // not covered; Rs 27
        {Zone::Inner, 9, false}     // pass-covered; no stored-value fare
    };

    for (const Trip &trip : trips) {
        cout << zoneName(trip.zone) << ": ";
        if (monthlyPass.covers(trip.zone)) {
            cout << "Monthly pass accepted; no fare deducted. ";
        } else {
            long long fare = calculateFare(trip.zone, trip.hour, trip.weekend);
            cout << "Fare paise = " << fare << ". ";
            if (card.pay(fare)) cout << "Payment accepted. ";
            else cout << "Payment denied (minimum balance rule). ";
        }
        cout << "Card balance paise = " << card.balance() << '\n';
    }
    return 0;
}
