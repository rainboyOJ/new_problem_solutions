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
int ans;

bool cmp_segment(const Segment &a, const Segment &b) {
    if (a.l != b.l) {
        return a.l < b.l;
    }
    return a.r < b.r;
}

// dfs(pos, last_end, cnt) 表示处理到第 pos 个比赛，
// 上一个已选比赛结束于 last_end，目前已经选了 cnt 个。
void dfs_choose(int pos, int last_end, int cnt) {
    if (pos > n) {
        ans = max(ans, cnt);
        return;
    }

    // 选择 0：不选当前比赛。
    dfs_choose(pos + 1, last_end, cnt);

    // 选择 1：如果时间不冲突，就选当前比赛。
    if (seg[pos].l >= last_end) {
        dfs_choose(pos + 1, seg[pos].r, cnt + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> seg[i].l >> seg[i].r;
    }

    sort(seg + 1, seg + n + 1, cmp_segment);
    ans = 0;
    dfs_choose(1, 0, 0);

    cout << ans << '\n';
    return 0;
}
