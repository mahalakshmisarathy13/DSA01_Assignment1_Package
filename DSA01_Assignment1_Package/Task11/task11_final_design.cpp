#include <iostream>
using namespace std;

enum class Zone { Inner, Middle, Outer };
constexpr long long FARES[] = {1000, 2000, 3000};
constexpr long long MIN_BALANCE = 5000;
constexpr int PEAK_PERCENT = 20;

bool peakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}
long long fareFor(Zone zone, int hour) {
    int index = static_cast<int>(zone);
    long long fare = FARES[index];
    if (peakHour(hour)) fare += fare * PEAK_PERCENT / 100;
    return fare;
}
class SmartCard {
private:
    long long balance;
public:
    explicit SmartCard(long long initial) : balance(initial) {}
    bool pay(long long fare) {
        if (fare < 0 || balance - fare < MIN_BALANCE) return false;
        balance -= fare;
        return true;
    }
    long long getBalance() const { return balance; }
};
int main() {
    SmartCard card(10000);
    long long fare = fareFor(Zone::Outer, 18);
    cout << "Fare paise: " << fare << '\n';
    cout << (card.pay(fare) ? "Journey allowed\n" : "Journey denied\n");
    cout << "Balance paise: " << card.getBalance() << '\n';
    return 0;
}
