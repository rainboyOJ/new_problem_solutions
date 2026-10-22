/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 00:00
 * update_at: 2026-10-21 00:00
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 01 序列枚举每条道路"免费 / 收费"：dfs(dep) 决定第 dep 条道路选不选，
// 到叶子统一检查三件事：恰好 n-1 条、整图连通、鹅卵石路恰好 k 条。
// 复杂度 O(2^m * (n+m))，只适合 m <= 20 左右的小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;   // 小数据村庄数上限
const int MAXM = 25;   // 小数据道路数上限

int n, m, k;
int eu[MAXM];      // eu[i]：第 i 条道路的端点 u
int ev[MAXM];      // ev[i]：第 i 条道路的端点 v
int ec[MAXM];      // ec[i]：第 i 条道路类型，0 鹅卵石 1 水泥
int choose_[MAXM]; // choose_[i]：第 i 条道路选(1)/不选(0)
int parent[MAXN];  // check 里用的并查集

// 小工具：并查集找根（路径压缩）
int find_root(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find_root(parent[x]);
}

// 检查一个完整的选边方案：n-1 条、连通、鹅卵石路恰 k 条。
bool check() {
    int total = 0, cobble = 0;
    for (int i = 1; i <= m; i++)
        if (choose_[i]) {
            total++;
            if (ec[i] == 0) cobble++;
        }
    if (total != n - 1 || cobble != k) return false;  // 不是生成树或鹅卵石数不对

    for (int i = 1; i <= n; i++) parent[i] = i;
    for (int i = 1; i <= m; i++)
        if (choose_[i]) {
            int ru = find_root(eu[i]);
            int rv = find_root(ev[i]);
            if (ru != rv) parent[ru] = rv;  // 合并；若有环 total 已不对，无需再查
        }
    // n-1 条边 + 无环 等价于 生成树；这里直接数连通块兜底
    int blocks = 0;
    for (int i = 1; i <= n; i++)
        if (find_root(i) == i) blocks++;
    return blocks == 1;
}

// 01 序列递归：这一层在决定第 dep 条道路选不选。
bool dfs(int dep) {
    if (dep > m) return check();  // 完整方案已生成，统一检查
    choose_[dep] = 0;             // 不选第 dep 条
    if (dfs(dep + 1)) return true;
    choose_[dep] = 1;             // 选第 dep 条
    return dfs(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) cin >> eu[i] >> ev[i] >> ec[i];

    if (!dfs(1))
        cout << "no solution" << "\n";
    else {
        for (int i = 1; i <= m; i++)
            if (choose_[i]) cout << eu[i] << " " << ev[i] << " " << ec[i] << "\n";
    }
    return 0;
}
