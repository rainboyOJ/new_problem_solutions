// brute.cpp：小数据暴力搜索，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, k;
int a[MAXN];
int best_ans;

int win_score(int my_gesture, int opp_gesture) {
    if (my_gesture == 0 && opp_gesture == 2) {
        return 1;
    }
    if (my_gesture == 1 && opp_gesture == 0) {
        return 1;
    }
    if (my_gesture == 2 && opp_gesture == 1) {
        return 1;
    }
    return 0;
}

void dfs(int idx, int used_change, int cur_gesture, int win_cnt) {
    if (idx > n) {
        best_ans = max(best_ans, win_cnt);
        return;
    }

    // 这一轮保持当前手势。
    dfs(idx + 1, used_change, cur_gesture, win_cnt + win_score(cur_gesture, a[idx]));

    // 这一轮前切换到另外两种手势。
    if (used_change < k) {
        for (int s = 0; s < 3; s++) {
            if (s == cur_gesture) {
                continue;
            }
            dfs(idx + 1, used_change + 1, s, win_cnt + win_score(s, a[idx]));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        char ch;
        cin >> ch;
        if (ch == 'H') {
            a[i] = 0;
        }
        else if (ch == 'P') {
            a[i] = 1;
        }
        else {
            a[i] = 2;
        }
    }

    best_ans = 0;
    for (int s = 0; s < 3; s++) {
        dfs(1, 0, s, 0);
    }

    cout << best_ans << '\n';
    return 0;
}
