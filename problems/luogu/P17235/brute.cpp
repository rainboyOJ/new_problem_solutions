/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-12 09:47
 */
// brute.cpp：小数据暴力解，把每条边是否反转看成 01 选择序列来递归枚举。
// 只适合 n,m 很小的数据（如 Subtask 1 的 n,m <= 15）验证与对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXM = 20;

int n, m, k;             // n 个节点、m 条边、棋子初始所在的节点 k
int eu[MAXM], ev[MAXM];  // 第 i 条有向边：起点 eu[i]，终点 ev[i]
int choose_edge[MAXM];   // choose_edge[i] 表示第 i 条边是否反转：0 保持原方向，1 反转
int answer_found;        // 是否已经找到一组合法方案
int answer_choose[MAXM]; // 找到的合法方案中每条边的反转选择（0/1）
vector<int> adj[MAXN];   // 反转后的邻接表：adj[u] 保存 u 的所有出边指向的节点

// 检查当前完整选择序列 choose_edge[1..m] 对应的图，进行 n 轮游戏后是否恰好剩 1 枚棋子。
bool check_answer() {
    for (int u = 1; u <= n; u++) adj[u].clear();

    // 按 choose_edge 决定是否交换边的两端，建出反转后的邻接表
    for (int i = 1; i <= m; i++) {
        int u = eu[i], v = ev[i];
        if (choose_edge[i] == 1) swap(u, v); // 反转后 u 变终点、v 变起点
        adj[u].push_back(v);
    }

    bool state[MAXN]; // state[u] = 1 表示节点 u 当前有棋子
    memset(state, 0, sizeof(state));
    state[k] = 1; // 初始棋子放在节点 k

    for (int step = 1; step <= n; step++) {
        // 把两轮规则合并：下一轮节点 u 有棋子 <=> u 有出边指向当前有棋子的节点。
        // 有棋子：只有全部出边指向的节点都没有棋子才移除，否则保留；
        // 无棋子：只要有一个出边指向的节点有棋子就放置。
        bool next_state[MAXN];
        memset(next_state, 0, sizeof(next_state));
        for (int u = 1; u <= n; u++) {
            for (int i = 0; i < (int)adj[u].size(); i++) {
                int v = adj[u][i]; // u 的出边指向 v
                if (state[v]) next_state[u] = 1;
            }
        }
        // 一轮中所有节点同时更新，等全部算完再整体赋值
        for (int u = 1; u <= n; u++) state[u] = next_state[u];
    }

    // 数一下 n 轮后还剩几枚棋子
    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        if (state[u]) cnt++;
    }
    return cnt == 1;
}

// 01 选择序列递归：第 dep 层选择第 dep 条边是否反转。
void dfs(int dep) {
    if (answer_found) return; // 已经找到方案，剪掉剩余分支
    if (dep == m + 1) {       // 一条完整选择序列已生成，统一检查合法性
        if (check_answer()) {
            answer_found = 1;
            for (int i = 1; i <= m; i++) answer_choose[i] = choose_edge[i];
        }
        return;
    }

    // 这一层在决定第 dep 条边的反转状态：0 不反转，1 反转
    for (int x = 0; x <= 1; x++) {
        choose_edge[dep] = x;
        dfs(dep + 1);
        if (answer_found) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= m; i++) cin >> eu[i] >> ev[i];

        answer_found = 0;
        dfs(1); // 枚举全部 2^m 种反转方案

        if (!answer_found) {
            cout << "No\n";
        }
        else {
            cout << "Yes\n";
            for (int i = 1; i <= m; i++) cout << answer_choose[i];
            cout << '\n';
        }
    }
    return 0;
}
