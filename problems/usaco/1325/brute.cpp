/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:40
 * update_at: 2026-07-11 16:41
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, k;
int T;
int active_pos[MAXN];
int order_arr[MAXN];
int tmp_value[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> T;
    for (int i = 1; i <= k; i++) {
        cin >> active_pos[i];
    }
    for (int i = 0; i < n; i++) {
        order_arr[i] = i;
    }

    // 小数据暴力：逐分钟模拟活动位置轮转，然后活动位置整体右移。
    for (int t = 1; t <= T; t++) {
        for (int i = 1; i <= k; i++) {
            tmp_value[i] = order_arr[active_pos[i]];
        }

        for (int i = 1; i <= k; i++) {
            int from = i - 1;
            if (from == 0) from = k;
            order_arr[active_pos[i]] = tmp_value[from];
        }

        for (int i = 1; i <= k; i++) {
            active_pos[i]++;
            if (active_pos[i] == n) active_pos[i] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << order_arr[i];
    }
    cout << '\n';

    return 0;
}
