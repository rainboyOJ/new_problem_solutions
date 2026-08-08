#include <bits/stdc++.h>
using namespace std;

// brute.cpp：教学版直接模拟最优构造过程。
// 我们按 1 -> 2 -> 3 -> ... -> n 的顺序处理：
// 1. 把当前这杯烧到 100 度；
// 2. 如果后面还有没烧开的杯子，就拿它和下一杯传热一次。
//
// 这样除了第一杯以外，后面的每一杯在第一次被烧开前都会先变成 50 度，
// 所以每次再补 50 度即可。

int n;
vector<long double> temp_arr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    temp_arr.assign(n + 1, 0.0L);

    long double sum_delta = 0.0L;

    for (int i = 1; i <= n; i++) {
        // 先把第 i 杯补到 100 度。
        sum_delta += 100.0L - temp_arr[i];
        temp_arr[i] = 100.0L;

        // 再拿它给下一杯传热一次。
        if (i < n) {
            long double avg = (temp_arr[i] + temp_arr[i + 1]) / 2.0L;
            temp_arr[i] = avg;
            temp_arr[i + 1] = avg;
        }
    }

    long double ans = 4200.0L / n * sum_delta;
    cout << fixed << setprecision(2) << (double)ans << '\n';

    return 0;
}
