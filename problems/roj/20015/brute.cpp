/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 19:19
 * update_at: 2026-08-28 19:19
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// 每条边是一个"选择对象"：choose[i] = 0 表示不切第 i 条边，1 表示切开。
// 递归先生成完整的 choose[]，到叶子节点再统一检查：
// 切开后树被分成若干连通块，统计权和恰为 k 的连通块个数，更新最优答案。
// 任何"把树切成若干连通块"的方案都唯一对应一组切边选择，因此枚举 2^(n-1) 种
// 选择就枚举了所有方案。适合 n <= 15 的小数据，用于对拍验证 main.cpp。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, k;
int a[MAXN];                // 点权
int eu[MAXN], ev[MAXN];     // 第 i 条边的两个端点
int choose[MAXN];           // choose[i] = 0/1：第 i 条边 不切/切开
int ans;                    // 最优答案

bool vis[MAXN];

// 检查当前完整 choose[1..n-1] 是否是一组合法切边方案，并统计答案。
void check() {
    // 只保留未切开的边，做连通块扫描
    for (int i = 1; i <= n; i++) vis[i] = false;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        // 用 DFS 找出包含 i 的连通块，累加块内点权和
        int sum = 0;
        stack<int> st;
        st.push(i);
        vis[i] = true;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            sum += a[u];
            for (int e = 1; e < n; e++) {
                if (choose[e] == 1) continue; // 这条边被切开了
                int v = -1;
                if (eu[e] == u) v = ev[e];
                else if (ev[e] == u) v = eu[e];
                if (v != -1 && !vis[v]) {
                    vis[v] = true;
                    st.push(v);
                }
            }
        }
        if (sum == k) cnt++;
    }
    if (ans < cnt) ans = cnt;
}

// 第 dep 层选择第 dep 条边切 / 不切，dep == n 时所有选择已生成完毕。
void dfs(int dep) {
    if (dep == n) { // 已经决策了 n-1 条边（dep 从 1 到 n-1）
        check();
        return;
    }
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int read_int() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    int t = read_int();
    while (t--) {
        n = read_int();
        k = read_int();
        for (int i = 1; i <= n; i++) a[i] = read_int();
        for (int i = 1; i < n; i++) {
            eu[i] = read_int();
            ev[i] = read_int();
        }

        ans = 0;
        dfs(1); // 枚举所有切边选择
        printf("%d\n", ans);
    }
    return 0;
}