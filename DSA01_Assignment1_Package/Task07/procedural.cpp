#include <iostream>
using namespace std;
const long long MIN_BALANCE = 5000;

bool canTravel(long long balance, long long fare) {
    return fare >= 0 && balance - fare >= MIN_BALANCE;
}
bool deduct(long long &balance, long long fare) {
    if (!canTravel(balance, fare)) return false;
    balance -= fare;
    return true;
}
int main() {
    long long balance = 10000;
    long long fare = 2000;
    if (deduct(balance, fare)) cout << "Allowed. Balance paise: " << balance << '\n';
    else cout << "Denied. Balance paise: " << balance << '\n';
    return 0;
}
