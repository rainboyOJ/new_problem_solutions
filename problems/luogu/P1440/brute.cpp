#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接枚举每个位置前面的 m 个数，只适合小数据对拍。

const int MAXN = 505;

int n, m;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        int left = max(1, i - m);
        if (left > i - 1) {
            cout << 0 << '\n';
            continue;
        }
        int best = a[left];
        for (int j = left + 1; j <= i - 1; j++) {
            best = min(best, a[j]);
        }
        cout << best << '\n';
    }

    return 0;
}
