#include <iostream>
using namespace std;

class SmartCard {
private:
    long long balancePaise;
    static constexpr long long MIN_BALANCE_PAISE = 5000;
public:
    explicit SmartCard(long long initialBalance) : balancePaise(initialBalance) {}
    bool canTravel(long long farePaise) const {
        return farePaise >= 0 && balancePaise - farePaise >= MIN_BALANCE_PAISE;
    }
    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }
    long long getBalance() const { return balancePaise; }
};
int main() {
    SmartCard card(10000);
    if (card.deduct(2000)) cout << "Allowed. Balance paise: " << card.getBalance() << '\n';
    else cout << "Denied. Balance paise: " << card.getBalance() << '\n';
    return 0;
}
