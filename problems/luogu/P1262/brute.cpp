/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-22 21:50
 * update_at: 2026-10-22 21:50
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举所有可收买者的子集。
// 本层在设计"第 dep 个可收买者买不买"，到叶子时判断能否控制全部间谍。
//
// 题意直接建模：买下一个集合 S 后，从 S 出发沿"掌握证据"的有向边能走到的人
// 全部被控制。所以暴力只需枚举 S 的每个子集，做一次可达性标记，检查是否覆盖了
// 所有人，在所有可行子集里取花费最小者。无解时输出买下全部可收买者仍然走不到的人
// 里编号最小的那个（买得越多可达范围只会更大，所以全买就是最大可达集）。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 3005;
const int maxm = 8005;
const int INF = 1e9;

int n, p, r;

int buyer[maxn];   // buyer[i] = 第 i 个可收买者（1..p）
int price[maxn];   // price[i] = 收买 buyer[i] 的价格
int cost[maxn];    // cost[v] = 收买 v 的价格，INF 表示不可收买

int eu[maxm], ev[maxm];  // 第 i 条边 eu[i] -> ev[i]

int choose_[maxn];  // choose_[i] = 第 i 个可收买者是否被买下

int best_cost = INF;  // 当前最优总花费

// 从选中的可收买者出发做可达性标记，返回 true 表示全部 n 人都被控制
bool check() {
    static bool reach[maxn];
    static int que[maxn];

    for (int v = 1; v <= n; v++) reach[v] = false;

    int head = 0, tail = 0;
    for (int i = 1; i <= p; i++) {
        if (choose_[i]) {
            int v = buyer[i];
            if (!reach[v]) {
                reach[v] = true;
                que[tail++] = v;
            }
        }
    }

    // 邻接表用邻接矩阵太慢，这里按边表线性扫描（小数据够用）
    while (head < tail) {
        int u = que[head++];
        for (int i = 1; i <= r; i++) {
            if (eu[i] == u && !reach[ev[i]]) {
                reach[ev[i]] = true;
                que[tail++] = ev[i];
            }
        }
    }

    for (int v = 1; v <= n; v++) {
        if (!reach[v]) return false;
    }
    return true;
}

// 这一层在决定"第 dep 个可收买者买不买"
void dfs(int dep, int sum) {
    if (sum >= best_cost) return;  // 剪枝：已经不比当前最优更好

    if (dep > p) {
        if (check()) best_cost = min(best_cost, sum);
        return;
    }

    choose_[dep] = 0;
    dfs(dep + 1, sum);

    choose_[dep] = 1;
    dfs(dep + 1, sum + price[dep]);
    choose_[dep] = 0;
}

void read_input() {
    cin >> n;
    cin >> p;
    fill(cost, cost + n + 1, INF);
    for (int i = 1; i <= p; i++) {
        int v, c;
        cin >> v >> c;
        buyer[i] = v;
        price[i] = c;
        cost[v] = c;
    }
    cin >> r;
    for (int i = 1; i <= r; i++) {
        cin >> eu[i] >> ev[i];
    }
}

void solve() {
    dfs(1, 0);

    if (best_cost < INF) {
        cout << "YES\n" << best_cost << "\n";
        return;
    }

    // 无解：买下所有人仍然控制不到的人，取编号最小
    for (int i = 1; i <= p; i++) choose_[i] = 1;
    check();

    static bool reach[maxn];
    for (int v = 1; v <= n; v++) reach[v] = false;
    static int que[maxn];
    int head = 0, tail = 0;
    for (int i = 1; i <= p; i++) {
        int v = buyer[i];
        if (!reach[v]) { reach[v] = true; que[tail++] = v; }
    }
    while (head < tail) {
        int u = que[head++];
        for (int i = 1; i <= r; i++) {
            if (eu[i] == u && !reach[ev[i]]) {
                reach[ev[i]] = true;
                que[tail++] = ev[i];
            }
        }
    }
    for (int v = 1; v <= n; v++) {
        if (!reach[v]) { cout << "NO\n" << v << "\n"; return; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
