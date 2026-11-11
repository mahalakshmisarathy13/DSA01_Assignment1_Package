#include <iostream>
#include <iomanip>
constexpr long long INNER_FARE_PAISE = 1000;
constexpr long long MIDDLE_FARE_PAISE = 2000;
constexpr long long OUTER_FARE_PAISE = 3000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;
enum class Zone { Inner, Middle, Outer };
long long baseFare(Zone zone) {
 switch (zone) {
 case Zone::Inner: return INNER_FARE_PAISE;
 case Zone::Middle: return MIDDLE_FARE_PAISE;
 case Zone::Outer: return OUTER_FARE_PAISE;
 }
 return 0;
}
int main() {
 std::cout << "BASE FARES\n"
 << "Inner : Rs " << INNER_FARE_PAISE / 100.0 << '\n'
 << "Middle: Rs " << MIDDLE_FARE_PAISE / 100.0 << '\n'
 << "Outer : Rs " << OUTER_FARE_PAISE / 100.0 << '\n'
 << "Peak surcharge: " << PEAK_SURCHARGE_PERCENT << "%\n"
 << "Minimum balance: Rs " << MIN_BALANCE_PAISE / 100.0 << '\n';
 const long long fare = baseFare(Zone::Outer);
 const long long total = fare + fare * PEAK_SURCHARGE_PERCENT / 100;
 std::cout << std::fixed << std::setprecision(2)
 << "Outer peak fare: Rs " << total / 100.0 << '\n';
}