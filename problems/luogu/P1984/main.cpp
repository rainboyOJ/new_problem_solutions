#include <bits/stdc++.h>
using namespace std;

long long n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 最优总“温度增量”是：
    // 第一杯从 0 烧到 100，需要 100 度；
    // 后面每一杯在最优情况下，第一次被烧开前最多只有 50 度，
    // 所以每杯再补 50 度即可。
    // 因而总温度增量为 100 + 50 * (n - 1) = 50 * (n + 1)。
    //
    // 每杯水质量是 1/n kg，升高 1 度需要 4200/n J。
    // 所以最小总能量为：
    // 4200 / n * 50 * (n + 1) = 210000 * (n + 1) / n。
    long double ans = 210000.0L * (n + 1.0L) / (long double)n;

    cout << fixed << setprecision(2) << (double)ans << '\n';
    return 0;
}
