/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:50
 * update_at: 2026-07-11 12:51
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int h[MAXN];

bool all_become(vector<int> a, int x) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                int cnt = 0;
                for (int i = l; i <= r; i++) {
                    if (a[i] == x) {
                        cnt++;
                    }
                }

                int len = r - l + 1;
                if (cnt * 2 > len && cnt < len) {
                    for (int i = l; i <= r; i++) {
                        a[i] = x;
                    }
                    changed = true;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] != x) {
            return false;
        }
    }
    return true;
}

void solve_one() {
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        a[i] = h[i];
    }

    bool printed = false;
    for (int x = 1; x <= n; x++) {
        if (all_become(a, x)) {
            if (printed) {
                cout << ' ';
            }
            cout << x;
            printed = true;
        }
    }
    if (!printed) {
        cout << -1;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_one();
    }

    return 0;
}
