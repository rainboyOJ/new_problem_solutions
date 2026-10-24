/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * brute.cpp：P1220 小数据暴力（n<=8）。
 * 不用区间假设，直接枚举关灯顺序：状态 = (当前位置, 已关灯集合)，
 * 每步精确模拟：走向下一盏未关的灯，路上所有亮灯燃烧 (距离) 秒，到达后关掉它。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, c;
ll pos_[10], w[10];
ll ans;

// 已关集合 mask，站在 p，当前已烧电量 cur
void dfs(int p, int mask, ll cur) {
    if (mask == (1 << n) - 1) {
        ans = min(ans, cur);
        return;
    }
    // 剪枝
    if (cur >= ans) return;
    for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) continue;
        ll dist = llabs(pos_[i+1] - pos_[p]);
        // 路上亮灯燃烧：所有未关的灯（包括目标灯自己）烧 dist 秒
        ll burn = 0;
        for (int j = 0; j < n; ++j)
            if (!(mask & (1 << j))) burn += w[j+1];
        ll ncur = cur + burn * dist;
        if (ncur >= ans) continue;
        dfs(i + 1, mask | (1 << i), ncur);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> c;
    for (int i = 1; i <= n; ++i) cin >> pos_[i] >> w[i];
    ans = LLONG_MAX;
    dfs(c, 1 << (c - 1), 0); // 起点的灯先关掉，不烧电
    cout << ans << "\n";
    return 0;
}
