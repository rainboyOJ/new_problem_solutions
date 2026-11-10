/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:36
 * update_at: 2026-11-10 10:50
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;

int n, k;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int cnt0 = 0;
    int best_len = 0, best_l = 1;

    // 滑动窗口：右端点逐个加入，窗口内 0 超标时收缩左端点
    for (int l = 1, r = 1; r <= n; r++) {
        if (a[r] == 0) {
            cnt0++;
        }
        while (cnt0 > k) {
            if (a[l] == 0) {
                cnt0--;
            }
            l++;
        }
        // 此时窗口 [l, r] 内 0 的个数 <= k，天然合法
        if (r - l + 1 > best_len) {
            best_len = r - l + 1;
            best_l = l;
        }
    }

    // 将最优窗口内的 0 全部修改为 1
    for (int i = best_l; i < best_l + best_len; i++) {
        a[i] = 1;
    }

    cout << best_len << "\n";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}
