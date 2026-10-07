/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:47
 * update_at: 2026-10-05 23:47
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 16;
const int INF = 1e9;

int n;
// rects[i] = {y1, x1, y2, x2, color}
int rects[MAXN][5];
// pre_mask[i] 的第 u 位为 1 表示矩形 u 是 i 的紧靠上方矩形
int pre_mask[MAXN];
// memo[mask][color] 记忆化，color 范围 0..20，0 表示手中无刷子
int memo[1 << MAXN][21];
bool vis[1 << MAXN][21];

// 返回涂完剩余矩形所需的最少额外拿起刷子次数
int dfs(int mask, int cur_color) {
    if (mask == (1 << n) - 1) return 0;
    if (vis[mask][cur_color]) return memo[mask][cur_color];
    vis[mask][cur_color] = true;

    // 贪心：若手中有同色刷子，把所有可涂的同色矩形一次性涂完
    int nxt_mask = mask;
    for (int i = 0; i < n; ++i) {
        if ((mask >> i & 1)) continue;               // 已涂
        if ((mask & pre_mask[i]) != pre_mask[i]) continue; // 上方未涂完
        if (rects[i][4] != cur_color) continue;      // 颜色不同
        nxt_mask |= 1 << i;
    }
    if (nxt_mask != mask) {
        memo[mask][cur_color] = dfs(nxt_mask, cur_color);
        return memo[mask][cur_color];
    }

    // 枚举当前所有可涂矩形的颜色，换刷子
    int ans = INF;
    bool has_color[21] = {false};
    for (int i = 0; i < n; ++i) {
        if ((mask >> i & 1)) continue;
        if ((mask & pre_mask[i]) != pre_mask[i]) continue;
        int c = rects[i][4];
        if (!has_color[c]) {
            has_color[c] = true;
            ans = min(ans, 1 + dfs(mask, c));
        }
    }
    memo[mask][cur_color] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> rects[i][0] >> rects[i][1] >> rects[i][2] >> rects[i][3] >> rects[i][4];
    }
    // 预处理每个矩形的紧靠上方矩形掩码
    for (int v = 0; v < n; ++v) {
        int mask = 0;
        for (int u = 0; u < n; ++u) {
            if (rects[u][2] == rects[v][0]) { // u 的下边界贴合 v 的上边界
                if (!(rects[u][3] <= rects[v][1] || rects[u][1] >= rects[v][3])) {
                    mask |= 1 << u;
                }
            }
        }
        pre_mask[v] = mask;
    }
    cout << dfs(0, 0) << "\n";
    return 0;
}
