// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 205;

int l, target_k;
i64 a[MAXN];

int count_ac(i64 need) {
    i64 cur = 0;
    int cnt = 0;

    for (int i = 1; i <= l; i++) {
        cur += a[i];
        if (cur < 0) cur = 0;
        if (cur >= need) {
            cnt++;
            cur = 0;
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> l >> target_k;
    i64 sum_pos = 0;
    for (int i = 1; i <= l; i++) {
        cin >> a[i];
        if (a[i] > 0) sum_pos += a[i];
    }

    i64 first = -1;
    i64 last = -1;

    for (i64 n = 1; n <= sum_pos; n++) {
        if (count_ac(n) == target_k) {
            if (first == -1) first = n;
            last = n;
        }
    }

    if (first == -1) cout << -1 << '\n';
    else cout << first << ' ' << last << '\n';

    return 0;
}
