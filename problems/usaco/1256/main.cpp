/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:22
 * update_at: 2026-07-11 21:24
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;

int n;
long long r[MAXN][MAXN];
long long ans[MAXN];

bool check_prefix(int left) {
    long long mn = ans[left];
    long long mx = ans[left];

    for (int j = left; j <= n; j++) {
        if (mn > ans[j]) mn = ans[j];
        if (mx < ans[j]) mx = ans[j];
        if (mx - mn != r[left][j]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> r[i][j];
        }
    }

    ans[n] = 0;
    for (int i = n - 1; i >= 1; i--) {
        ans[i] = ans[i + 1] + r[i][i + 1];
        if (!check_prefix(i)) {
            ans[i] = ans[i + 1] - r[i][i + 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
