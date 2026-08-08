// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAXP = 505;

int n;
int pos[MAXN];
vector<int> watch_pos[MAXN];
vector<int> cameras_at_pos[MAXP];
int in_mask[MAXN];        // in_mask[i] : 哪些摄像头会监视第 i 个摄像头
int memo[1 << MAXN];

int solve_mask(int mask) {
    if (memo[mask] != -1) {
        return memo[mask];
    }

    int best = __builtin_popcount((unsigned) mask);
    bool can_remove = false;

    for (int i = 0; i < n; i++) {
        if (((mask >> i) & 1) == 0) {
            continue;
        }

        // 还存活的摄像头里，没有别人监视它，它就可以被砸掉。
        if ((in_mask[i] & mask) == 0) {
            can_remove = true;
            best = min(best, solve_mask(mask ^ (1 << i)));
        }
    }

    if (!can_remove) {
        memo[mask] = __builtin_popcount((unsigned) mask);
    } else {
        memo[mask] = best;
    }
    return memo[mask];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < MAXP; i++) {
        cameras_at_pos[i].clear();
    }

    for (int i = 0; i < n; i++) {
        watch_pos[i].clear();

        int m;
        cin >> pos[i] >> m;
        for (int j = 0; j < m; j++) {
            int y;
            cin >> y;
            watch_pos[i].push_back(y);
        }
        cameras_at_pos[pos[i]].push_back(i);
    }

    memset(in_mask, 0, sizeof(in_mask));
    for (int i = 0; i < n; i++) {
        bool linked[MAXN] = {};

        for (int y : watch_pos[i]) {
            for (int v : cameras_at_pos[y]) {
                if (v == i || linked[v]) {
                    continue;
                }
                linked[v] = true;
                in_mask[v] |= 1 << i;
            }
        }
    }

    int full = (1 << n) - 1;
    memset(memo, -1, sizeof(memo));
    memo[0] = 0;

    cout << solve_mask(full) << '\n';
    return 0;
}
