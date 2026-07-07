// brute.cpp：小数据暴力解，使用 01 序列递归枚举每个比赛选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

struct Segment {
    int l;
    int r;
};

int n;
Segment seg[MAXN]; // 小数据下保存所有比赛区间
int choose_match[MAXN]; // choose_match[i] = 0/1，表示第 i 个比赛不选/选
int ans;

bool is_conflict(int x, int y) {
    // 两个比赛时间有重叠，就不能同时选择。
    if (seg[x].r <= seg[y].l) return false;
    if (seg[y].r <= seg[x].l) return false;
    return true;
}

bool check() {
    // 叶子节点统一检查当前完整 01 序列是否合法。
    for (int i = 1; i <= n; i++) {
        if (choose_match[i] == 0) continue;
        for (int j = i + 1; j <= n; j++) {
            if (choose_match[j] == 0) continue;
            if (is_conflict(i, j)) return false;
        }
    }
    return true;
}

int calc_answer() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_match[i] == 1) cnt++;
    }
    return cnt;
}

// dfs(dep) 只负责生成完整的 01 序列，不在递归中提前判断合法性。
void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }

    for (int i = 0; i <= 1; i++) {
        choose_match[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> seg[i].l >> seg[i].r;
    }

    ans = 0;
    dfs_choose(1);

    cout << ans << '\n';
    return 0;
}
