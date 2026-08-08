// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 10;

int n, m;
string s;
int c[MAXN];
int p[MAXN];

bool check_perm() {
    int failed = 0;
    int hired = 0;

    for (int day = 0; day < n; day++) {
        int person = p[day];
        if (failed >= c[person]) {
            failed++;
            continue;
        }

        if (s[day] == '1') {
            hired++;
        } else {
            failed++;
        }
    }

    return hired >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> s;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        p[i] = i;
    }

    int ans = 0;
    do {
        if (check_perm()) {
            ans++;
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
    } while (next_permutation(p, p + n));

    cout << ans << '\n';
    return 0;
}
