#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举所有非空音阶集合的子集，只适合 n,m 很小的验证。

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int total = (1 << n) - 1;
    long long answer = 0;
    for (int mask = 0; mask < (1 << total); mask++) {
        if (__builtin_popcount((unsigned)mask) != m) {
            continue;
        }
        int xor_sum = 0;
        for (int i = 0; i < total; i++) {
            if (mask & (1 << i)) {
                xor_sum ^= (i + 1);
            }
        }
        if (xor_sum == 0) {
            answer++;
        }
    }
    cout << answer << '\n';

    return 0;
}
