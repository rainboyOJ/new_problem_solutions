/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:19
 * update_at: 2026-08-13 13:19
 */
// brute.cpp：小数据暴力解，把每一步按钮操作看成选择序列来递归枚举。
// 每个递归层代表一次按钮选择（向上或向下），用 vis[] 保证路径不重复访问楼层。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, s, t;            // n: 楼层数, s: 起点楼层, t: 终点楼层
int k[MAXN];            // k[i] 表示第 i 层能向上/向下移动的层数
bool vis[MAXN];         // vis[i] 表示当前路径是否已经到过第 i 层
int ans = 0x3f3f3f3f;   // 当前找到的最少按键次数，初始为无穷大

// 当前在楼层 u，已经按了 step 次按钮。
// 递归的每一层在做一次选择：这次按钮是向上还是向下。
void dfs(int u, int step) {
    if (u == t) {   // 这条路径到达了终点，用它的按键次数更新答案
        if (step < ans) ans = step;
        return;
    }
    if (step >= ans) return;    // 按键次数已经不会比当前答案更优，剪枝

    // 选择 1：向上跳 k[u] 层
    int v1 = u + k[u];
    if (v1 >= 1 && v1 <= n && !vis[v1]) {
        vis[v1] = true;
        dfs(v1, step + 1);
        vis[v1] = false;
    }
    // 选择 2：向下跳 k[u] 层
    int v2 = u - k[u];
    if (v2 >= 1 && v2 <= n && !vis[v2]) {
        vis[v2] = true;
        dfs(v2, step + 1);
        vis[v2] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s >> t;
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }

    vis[s] = true;
    dfs(s, 0);

    // 一条到达终点的路径都没找到，输出 -1。
    if (ans == 0x3f3f3f3f) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }
    return 0;
}
