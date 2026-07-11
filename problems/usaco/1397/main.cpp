/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:03
 * update_at: 2026-07-11 16:04
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, q;
int c[MAXN];
int t[MAXN];
int diff_arr[MAXN]; // diff_arr[i] = c[i] - t[i]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        diff_arr[i] = c[i] - t[i];
    }

    sort(diff_arr + 1, diff_arr + n + 1);

    for (int i = 1; i <= q; i++) {
        int v, s;
        cin >> v >> s;

        // t[i] + S < c[i] 等价于 c[i] - t[i] > S。
        int pos = upper_bound(diff_arr + 1, diff_arr + n + 1, s) - diff_arr;
        int cnt = n - pos + 1;

        if (cnt >= v) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
