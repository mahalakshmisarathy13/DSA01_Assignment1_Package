
#include <iostream>
#include <climits>
#include <cstddef>
#include <limits>

int main() {
    const int zones = 3;
    const long long journeys = 3000000LL;
    const long long maximumFarePaise = 3600LL;

    const long long networkTotalPaise =
        journeys * maximumFarePaise;

    std::cout << "TYPE SIZES (bytes)\n"
              << "bool: " << sizeof(bool) << '\n'
              << "char: " << sizeof(char) << '\n'
              << "int: " << sizeof(int) << '\n'
              << "long long: " << sizeof(long long) << '\n'
              << "float: " << sizeof(float) << '\n'
              << "double: " << sizeof(double) << '\n';

    std::cout << "\nINT RANGE: "
              << INT_MIN << " to " << INT_MAX << '\n';

    std::cout << "Zones: " << zones << '\n';
    std::cout << "Journeys: " << journeys << '\n';

    std::cout << "Worst-case total at Rs 36 each: Rs "
              << networkTotalPaise / 100 << '\n';

    std::cout << "\nMoney is stored as integer paise to avoid "
              << "binary floating-point rounding in fare and "
              << "balance calculations.\n";

    return 0;
}
