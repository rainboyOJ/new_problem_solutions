/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 11:10
 * update_at: 2026-08-04 11:10
 */

// brute.cpp：小数据暴力解，使用选择序列递归枚举所有挖矿路径。
// 每一层递归在选择"下一步去哪个编号更大的连通地窖"，走到底时更新最优方案。
// 只能处理小数据：所有路径数可能是指数级。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
int a[MAXN];            // a[i]：第 i 个地窖的地雷数
int conn[MAXN][MAXN];   // conn[i][j] = 1 表示 i 到 j 有路径（i < j）

int path[MAXN];         // 当前枚举到的路径
int ans_path[MAXN];     // 最优路径
int ans_cnt;            // 最优路径长度
int ans_sum;            // 最优路径的地雷总数

// 当前路径已走到第 dep 步，位于地窖 cur，已累计 sum 个地雷
void dfs(int dep, int cur, int sum) {
    // 结算当前方案：以 cur 结尾的这条路径
    if (ans_sum < sum) {
        ans_sum = sum;
        ans_cnt = dep;
        for (int i = 1; i <= dep; i++)
            ans_path[i] = path[i];
    }

    // 选择下一步：只能去编号更大且连通的地窖
    for (int nxt = cur + 1; nxt <= n; nxt++) {
        if (conn[cur][nxt] == 1) {
            path[dep + 1] = nxt;
            dfs(dep + 1, nxt, sum + a[nxt]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            cin >> conn[i][j];

    // 可以从任意地窖开始挖
    for (int start = 1; start <= n; start++) {
        path[1] = start;
        dfs(1, start, a[start]);
    }

    for (int i = 1; i <= ans_cnt; i++)
        cout << ans_path[i] << " ";
    cout << '\n' << ans_sum << '\n';

    return 0;
}
