#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接枚举 5 的个数，作为教学版朴素解和对拍基准。

long long n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    long long ans = 0;

    // 朴素做法：直接枚举用了多少个 5。
    // 如果剩下的部分可以被 4 正好填满，就是一种方案。
    for (long long cnt_five = 0; cnt_five * 5 <= n; cnt_five++) {
        long long rest = n - cnt_five * 5;
        if (rest % 4 == 0) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
