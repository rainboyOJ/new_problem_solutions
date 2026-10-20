/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 14:35
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接枚举每个农场的作物数，检查三类信息是否全部成立；找不到就输出 No。
// 取值上界：若有解，则一定存在一组解落在 [0, n*maxc] 内
// （约束只比较差值，可以整体平移成非负；最短路走最长简单路径最多 n-1 条边）。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 8;
const int bound = 60;  // 小数据下 n*maxc 的保守上界

struct Info {
    int type;
    int a;
    int b;
    int c;
};

int n, m;
Info e[maxn * 4];
int x[maxn];

// 检查所有两端都已赋值的条件
bool check_prefix(int dep) {
    for (int i = 1; i <= m; i++) {
        if (e[i].a > dep || e[i].b > dep) continue;
        if (e[i].type == 1) {
            // a 比 b 至少多 c
            if (x[e[i].a] - x[e[i].b] < e[i].c) return false;
        } else if (e[i].type == 2) {
            // a 比 b 至多多 c
            if (x[e[i].a] - x[e[i].b] > e[i].c) return false;
        } else {
            // 一样多
            if (x[e[i].a] != x[e[i].b]) return false;
        }
    }
    return true;
}

bool dfs(int dep) {
    if (dep > n) return true;
    for (int v = 0; v <= bound; v++) {
        x[dep] = v;
        if (!check_prefix(dep)) continue;
        if (dfs(dep + 1)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].type;
        cin >> e[i].a >> e[i].b;
        if (e[i].type == 3) {
            e[i].c = 0;
        } else {
            cin >> e[i].c;
        }
    }

    cout << (dfs(1) ? "Yes" : "No") << '\n';
    return 0;
}
