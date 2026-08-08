#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n;
int w[MAXN][MAXN];
int all_mask;
map<long long, int> memo_win;
map<long long, int> memo_best;

// 计算某一方当前军队中的最强组合。
int best_pair_value(int mask) {
    int ans = -1000000000;
    for (int i = 0; i < n; i++) {
        if (((mask >> i) & 1) == 0) {
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if ((mask >> j) & 1) {
                ans = max(ans, w[i][j]);
            }
        }
    }
    return ans;
}

long long encode_state(int xmask, int cmask, int turn) {
    return ((long long) xmask << 21) | ((long long) cmask << 1) | turn;
}

pair<int, int> dfs(int xmask, int cmask, int turn) {
    long long key = encode_state(xmask, cmask, turn);
    if (memo_win.count(key)) {
        return make_pair(memo_win[key], memo_best[key]);
    }

    int free_mask = all_mask ^ xmask ^ cmask;
    if (free_mask == 0) {
        int x_best = best_pair_value(xmask);
        int c_best = best_pair_value(cmask);
        if (x_best > c_best) {
            memo_win[key] = 1;
            memo_best[key] = x_best;
        }
        else {
            memo_win[key] = 0;
            memo_best[key] = -1000000000;
        }
        return make_pair(memo_win[key], memo_best[key]);
    }

    if (turn == 0) {
        int can_win = 0;
        int best_value = -1000000000;
        for (int i = 0; i < n; i++) {
            if ((free_mask >> i) & 1) {
                pair<int, int> ret = dfs(xmask | (1 << i), cmask, 1);
                if (ret.first) {
                    can_win = 1;
                    best_value = max(best_value, ret.second);
                }
            }
        }
        memo_win[key] = can_win;
        memo_best[key] = best_value;
        return make_pair(can_win, best_value);
    }
    else {
        // 计算机的策略是：
        // 从“小涵已选武将”与“当前自由武将”的所有配对中，
        // 找到默契值最大的那一对，并抢走其中的自由武将。
        int choose = -1;
        int best_match = -1;
        for (int i = 0; i < n; i++) {
            if (((xmask >> i) & 1) == 0) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                if ((free_mask >> j) & 1) {
                    if (w[i][j] > best_match) {
                        best_match = w[i][j];
                        choose = j;
                    }
                }
            }
        }
        pair<int, int> ret = dfs(xmask, cmask | (1 << choose), 0);
        memo_win[key] = ret.first;
        memo_best[key] = ret.second;
        return ret;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cin >> w[i][j];
            w[j][i] = w[i][j];
        }
    }

    all_mask = (1 << n) - 1;

    pair<int, int> ret = dfs(0, 0, 0);
    cout << ret.first << '\n';
    if (ret.first) {
        cout << ret.second << '\n';
    }

    return 0;
}
