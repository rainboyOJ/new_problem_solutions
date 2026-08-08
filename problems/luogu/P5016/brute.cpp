#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, m, p1;
long long s1, s2;
long long c[MAXN];

long long calc_diff_after_choose(int p2) {
    long long dragon = 0;
    long long tiger = 0;

    for (int i = 1; i <= n; i++) {
        long long cnt = c[i];

        if (i == p1) {
            cnt += s1;
        }
        if (i == p2) {
            cnt += s2;
        }

        if (i < m) {
            dragon += cnt * (m - i);
        }
        else if (i > m) {
            tiger += cnt * (i - m);
        }
    }

    return dragon - tiger;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    cin >> m >> p1 >> s1 >> s2;

    int ans = 1;
    long long best_abs = -1;

    // 直接枚举最后把 s2 放到哪个兵营，并重新统计双方气势。
    for (int p2 = 1; p2 <= n; p2++) {
        long long diff = calc_diff_after_choose(p2);
        long long cur_abs = llabs(diff);
        if (best_abs == -1 || cur_abs < best_abs ||
            (cur_abs == best_abs && p2 < ans)) {
            best_abs = cur_abs;
            ans = p2;
        }
    }

    cout << ans << '\n';

    return 0;
}
