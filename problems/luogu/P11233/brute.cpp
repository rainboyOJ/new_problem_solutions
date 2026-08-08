// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int T, n;
int a[MAXN];

long long calc_score(int mask) {
    int last[2];
    last[0] = last[1] = 0;

    long long score = 0;
    for (int i = 1; i <= n; i++) {
        int color = (mask >> (i - 1)) & 1;
        if (last[color] == a[i]) {
            score += a[i];
        }
        last[color] = a[i];
    }

    return score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        long long ans = 0;
        int total = 1 << n;
        for (int mask = 0; mask < total; mask++) {
            ans = max(ans, calc_score(mask));
        }

        cout << ans << '\n';
    }

    return 0;
}
