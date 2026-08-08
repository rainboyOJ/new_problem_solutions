/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-10 11:39
 * update_at: 2026-07-10 11:39
 */
#include <bits/stdc++.h>
using namespace std;

long long isqrt_ll(long long x) {
    long long l = 0, r = 1000000000LL;
    while (l < r) {
        long long mid = (l + r + 1) / 2;
        if (mid <= x / mid) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    while (k--) {
        long long n, e, d;
        cin >> n >> e >> d;

        long long sum = n - e * d + 2;
        long long delta = sum * sum - 4 * n;
        if (delta < 0) {
            cout << "NO\n";
            continue;
        }

        long long root = isqrt_ll(delta);
        if (root * root != delta || (sum - root) % 2 != 0) {
            cout << "NO\n";
            continue;
        }

        long long p = (sum - root) / 2;
        long long q = (sum + root) / 2;
        if (p <= 0 || q <= 0 || p * q != n) {
            cout << "NO\n";
        } else {
            cout << p << ' ' << q << '\n';
        }
    }

    return 0;
}
