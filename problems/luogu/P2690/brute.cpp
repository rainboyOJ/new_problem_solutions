// brute.cpp：小数据暴力搜索，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXT = 35;

int t, w;
int a[MAXT];
int best_ans;

void dfs(int minute_idx, int used_move, int pos, int got) {
    if (minute_idx > t) {
        best_ans = max(best_ans, got);
        return;
    }

    // 这一分钟开始前不移动。
    int add = (pos == a[minute_idx] ? 1 : 0);
    dfs(minute_idx + 1, used_move, pos, got + add);

    // 这一分钟开始前移动到另一棵树。
    if (used_move < w) {
        int new_pos = 3 - pos;
        int add2 = (new_pos == a[minute_idx] ? 1 : 0);
        dfs(minute_idx + 1, used_move + 1, new_pos, got + add2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t >> w;
    for (int i = 1; i <= t; i++) {
        cin >> a[i];
    }

    best_ans = 0;
    dfs(1, 0, 1, 0);

    cout << best_ans << '\n';
    return 0;
}
