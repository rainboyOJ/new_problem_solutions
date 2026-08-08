// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, limit_num;
int a[MAXN][4];
int cnt[4];
long long best_ans;

void dfs(int pos, long long sum) {
    if (pos > n) {
        best_ans = max(best_ans, sum);
        return;
    }

    for (int dep = 1; dep <= 3; dep++) {
        if (cnt[dep] == limit_num) {
            continue;
        }
        cnt[dep]++;
        dfs(pos + 1, sum + a[pos][dep]);
        cnt[dep]--;
    }
}

void solve_case() {
    cin >> n;
    limit_num = n / 2;
    for (int i = 1; i <= n; i++) {
        cin >> a[i][1] >> a[i][2] >> a[i][3];
    }

    cnt[1] = cnt[2] = cnt[3] = 0;
    best_ans = -1;
    dfs(1, 0);
    cout << best_ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
