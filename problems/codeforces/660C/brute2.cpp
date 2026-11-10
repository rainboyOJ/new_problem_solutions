/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:44
 * update_at: 2026-11-10 10:50
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;

int n, k;
int a[MAXN];
int s0[MAXN]; // 0 的个数前缀和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s0[i] = s0[i - 1] + (a[i] == 0);
    }

    int best_len = 0;
    int best_l = 1;

    // 枚举所有可能区间 [i, j]，O(n^2) 暴力基线
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (s0[j] - s0[i - 1] <= k) {
                if (j - i + 1 > best_len) {
                    best_len = j - i + 1;
                    best_l = i;
                }
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
