#include <iostream>
#include <climits>
#include <iomanip>
using namespace std;

int main() {
    const long long counts[] = {20000, 500000, 3000000};
    constexpr long long FARE_PAISE = 1000; // Assumption: Rs 10 per journey
    cout << "INT_MAX = " << INT_MAX << "\nLLONG_MAX = " << LLONG_MAX << "\n";
    cout << fixed << setprecision(8);
    for (long long n : counts) {
        long long exactPaise = n * FARE_PAISE;
        double rupees = 10.0 * static_cast<double>(n);
        cout << "Journeys: " << n
             << " | exact paise: " << exactPaise
             << " | double rupees: " << rupees << '\n';
        if (exactPaise > INT_MAX) cout << "  int paise total would exceed INT_MAX\n";
        else cout << "  int paise total is within INT_MAX\n";
    }
    double repeated = 0.0;
    long long exact = 0;
    for (int i = 0; i < 1000000; ++i) {
        repeated += 0.1;
        exact += 10; // 0.1 rupee = 10 paise
    }
    cout << "Repeated double total: " << repeated
         << " | integer paise / 100: " << static_cast<double>(exact) / 100.0 << '\n';
    return 0;
}
