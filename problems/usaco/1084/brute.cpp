/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:45
 * update_at: 2026-07-11 13:49
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int memo[15][15][2];
bool vis[15][15][2];

int dfs(int even_cnt, int odd_cnt, int need_parity) {
    if (even_cnt == 0 && odd_cnt == 0) {
        return 0;
    }

    if (vis[even_cnt][odd_cnt][need_parity]) {
        return memo[even_cnt][odd_cnt][need_parity];
    }
    vis[even_cnt][odd_cnt][need_parity] = true;

    int best = -1000000;

    // 枚举当前组使用多少头偶数牛、多少头奇数牛。
    for (int use_even = 0; use_even <= even_cnt; use_even++) {
        for (int use_odd = 0; use_odd <= odd_cnt; use_odd++) {
            if (use_even == 0 && use_odd == 0) {
                continue;
            }
            if (use_odd % 2 != need_parity) {
                continue;
            }

            int next_value = dfs(even_cnt - use_even, odd_cnt - use_odd, 1 - need_parity);
            if (best < next_value + 1) {
                best = next_value + 1;
            }
        }
    }

    memo[even_cnt][odd_cnt][need_parity] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int even_cnt = 0;
    int odd_cnt = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x % 2 == 0) {
            even_cnt++;
        } else {
            odd_cnt++;
        }
    }

    cout << dfs(even_cnt, odd_cnt, 0) << '\n';

    return 0;
}
