/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:23
 * update_at: 2026-11-10 10:50
 */
// brute.cpp：小数据直接暴力枚举，用于辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;

int n, k;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k)) return 0;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int best_len = 0, best_l = 1;
    for (int i = 1; i <= n; i++) {
        int cnt0 = 0;
        for (int j = i; j <= n; j++) {
            if (a[j] == 0) cnt0++;
            if (cnt0 <= k) {
                if (j - i + 1 > best_len) {
                    best_len = j - i + 1;
                    best_l = i;
                }
            } else {
                break;
            }
        }
    }

    for (int i = best_l; i < best_l + best_len; i++) {
        a[i] = 1;
    }

    cout << best_len << "\n";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}
