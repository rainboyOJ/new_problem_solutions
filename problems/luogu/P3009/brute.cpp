#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举所有连续区间，直接求区间和。

const int MAXN = 100005;

int n;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long ans = a[1];

    for (int l = 1; l <= n; l++) {
        long long sum = 0;
        for (int r = l; r <= n; r++) {
            sum += a[r];
            ans = max(ans, sum);
        }
    }

    cout << ans << '\n';
    return 0;
}
