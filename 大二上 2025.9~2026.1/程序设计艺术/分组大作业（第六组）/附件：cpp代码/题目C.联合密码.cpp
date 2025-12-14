#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a, b;
    if (!(cin >> a >> b)) return 0; 

    double sqrt_a = sqrt(max(0.0, a));
    double ans = sqrt(b * b + (1.0 + sqrt_a) * (1.0 + sqrt_a));

    cout << setiosflags(ios::fixed) << setprecision(6) << ans << endl;
    return 0;
}
