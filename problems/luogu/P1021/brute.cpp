/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:21
 * update_at: 2026-11-10 23:21
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 暴力验证版本：每次重新用一维完全背包核算连续最大值
const int MAX_VAL = 2000;
const int INF = 0x3f3f3f3f;

int n, k;
int cur_a[20];
int ans_a[20];
int ans_max = 0;

int calc_max(int len) {
    static int f[MAX_VAL + 5];
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;

    for (int i = 1; i <= len; ++i) {
        int v = cur_a[i];
        for (int j = v; j <= MAX_VAL; ++j) {
            f[j] = min(f[j], f[j - v] + 1);
        }
    }

    int r = 0;
    while (r + 1 <= MAX_VAL && f[r + 1] <= n) {
        r++;
    }
    return r;
}

void search(int idx, int last_max) {
    if (idx > k) {
        if (last_max > ans_max) {
            ans_max = last_max;
            for (int i = 1; i <= k; ++i) ans_a[i] = cur_a[i];
        }
        return;
    }

    for (int v = cur_a[idx - 1] + 1; v <= last_max + 1; ++v) {
        cur_a[idx] = v;
        int new_max = calc_max(idx);
        search(idx + 1, new_max);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k)) return 0;

    cur_a[1] = 1;
    ans_max = 0;
    search(2, n);

    for (int i = 1; i <= k; ++i) {
        cout << ans_a[i] << (i == k ? "" : " ");
    }
    cout << "\n";
    cout << "MAX=" << ans_max << "\n";

    return 0;
}
