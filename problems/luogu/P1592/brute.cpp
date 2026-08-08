#include <bits/stdc++.h>
using namespace std;

long long n, k;

long long gcd_value(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // brute.cpp：直接从 1 开始枚举正整数，
    // 找到第 k 个与 n 互质的数。
    // 复杂度与答案大小成正比，只适合小数据对拍。
    long long cnt = 0;
    for (long long x = 1; ; x++) {
        if (gcd_value(x, n) == 1) {
            cnt++;
            if (cnt == k) {
                cout << x << '\n';
                return 0;
            }
        }
    }

    return 0;
}
