/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 09:10
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接枚举每个 x_i 的取值，检查所有不等式是否都成立；找不到就输出 NO。
// 取值上界：若有解，则一定存在一组解满足 |x_i| <= n * max|y|
// （最短路走最长简单路径最多 n-1 条边，起点距离为 0）。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 10;

struct Constraint {
    int c;
    int c2;
    int y;
};

int n, m;
Constraint e[maxn * 4];
int x[maxn];
long long bound;

// 检查所有两端都已赋值的约束
bool check_prefix(int dep) {
    for (int i = 1; i <= m; ++i) {
        if (e[i].c <= dep && e[i].c2 <= dep) {
            if (x[e[i].c] - x[e[i].c2] > e[i].y) return false;
        }
    }
    return true;
}

bool dfs(int dep) {
    if (dep > n) return true;
    for (long long v = -bound; v <= bound; ++v) {
        x[dep] = (int)v;
        if (!check_prefix(dep)) continue;
        if (dfs(dep + 1)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    long long max_abs = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].c >> e[i].c2 >> e[i].y;
        max_abs = max(max_abs, (long long)abs(e[i].y));
    }
    bound = (long long)n * max_abs;

    if (!dfs(1)) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 1; i <= n; ++i) cout << x[i] << " \n"[i == n];

    return 0;
}
