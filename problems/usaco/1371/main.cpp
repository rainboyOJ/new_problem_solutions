/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:50
 * update_at: 2026-07-11 12:51
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int h[MAXN];
bool good[MAXN];

void solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        good[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        if (i >= 2 && h[i] == h[i - 1]) {
            good[h[i]] = true;
        }
        if (i >= 3 && h[i] == h[i - 2]) {
            good[h[i]] = true;
        }
    }

    bool printed = false;
    for (int x = 1; x <= n; x++) {
        if (good[x]) {
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
