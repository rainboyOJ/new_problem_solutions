/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-21 08:30
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接枚举每个小朋友的糖果数，检查五类要求是否全部成立，取总糖果数最小的可行解。
//
// 取值上界：若无解则不必枚举；若有解，把所有人按"严格多于"关系排成链，
// 链长最多 n 个点（出现环就已经矛盾），所以每个值不超过 n。故枚举 1..n 足够。
// 这是最笨也最贴近题意的做法，与 main.cpp 的 SCC + 最长路完全不共享实现，
// 因此适合用来独立验证 main.cpp 的正确性。复杂度 O(n^n)，只在 n 很小时可用。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 6;  // 只枚举极小数据：n <= 5

struct Demand {
    int kind;
    int a;
    int b;
};

int n, k;
Demand d[maxn * 4];
int candy[maxn];
long long best;

// 检查所有两端都已赋值的要求
bool check_prefix(int dep) {
    for (int i = 1; i <= k; i++) {
        if (d[i].a > dep || d[i].b > dep) continue;
        int xa = candy[d[i].a];
        int xb = candy[d[i].b];
        if (d[i].kind == 1) {
            if (xa != xb) return false;
        } else if (d[i].kind == 2) {
            if (!(xa < xb)) return false;
        } else if (d[i].kind == 3) {
            if (!(xa >= xb)) return false;
        } else if (d[i].kind == 4) {
            if (!(xa > xb)) return false;
        } else {
            if (!(xa <= xb)) return false;
        }
    }
    return true;
}

void dfs(int dep, long long sum) {
    if (sum >= best) return;  // 剪枝：已经不比当前最优更好
    if (dep > n) {
        best = sum;
        return;
    }
    // 每人至少一颗，上界取 n 足够（严格链最多 n 个点）
    for (int v = 1; v <= n; v++) {
        candy[dep] = v;
        if (!check_prefix(dep)) continue;
        dfs(dep + 1, sum + v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        cin >> d[i].kind >> d[i].a >> d[i].b;
    }

    best = (long long)1e18;
    dfs(1, 0);

    cout << (best == (long long)1e18 ? -1 : best) << '\n';
    return 0;
}
