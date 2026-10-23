/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 15:58
 * update_at: 2026-10-23 16:24
 */
// brute.cpp：小数据暴力解，把“新建的每一条边”看成一个选择，用选择序列递归枚举。
// 实测 n <= 11 可跑（星形图 n=11 约 0.7s），n = 13 已超时，所以只用于对拍与理解题意。
// 做法：从 k = 0 开始从小到大枚举 k 条新边（端点对允许重复），
// 一旦某个方案让整张图没有桥，k 就是答案。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;   // 暴力只处理小数据，n 超过这个范围枚举量直接爆炸
const int MAXE = 400;  // 原边 + 新边的总条数上限

int n, m;
int eu[MAXE], ev[MAXE];  // 原图的边
int edge_total;

int pair_u[MAXN * MAXN], pair_v[MAXN * MAXN];  // 所有可能的端点对 (i, j)，i < j
int pair_cnt;

int choose[MAXN];  // choose[dep]：第 dep 条新边选的是第几个端点对
int answer;

// 并查集，用来判断删掉某条边后图是否还连通
int father[MAXN];

int find_root(int x) {
    if (father[x] == x) {
        return x;
    }
    father[x] = find_root(father[x]);
    return father[x];
}

void union_pair(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);
    if (rx != ry) {
        father[rx] = ry;
    }
}

// 判断当前边集（原边 + 已经选好的 k 条新边）是否没有桥。
// 有一条边被删掉后图不连通，就说明它是桥，方案不成立。
bool no_bridge() {
    for (int skip = 0; skip < edge_total; skip++) {
        for (int i = 1; i <= n; i++) {
            father[i] = i;
        }
        for (int e = 0; e < edge_total; e++) {
            if (e == skip) {
                continue;
            }
            union_pair(eu[e], ev[e]);
        }
        int root = find_root(1);
        for (int i = 2; i <= n; i++) {
            if (find_root(i) != root) {
                return false;  // 删掉 skip 这条边后图断了，skip 是桥
            }
        }
    }
    return true;
}

// 这一层在为第 dep 条新边挑端点对：只从小到大挑，避免同一组边被重复枚举
void dfs(int dep, int need) {
    if (dep > need) {
        if (no_bridge()) {
            answer = need;
        }
        return;
    }
    for (int p = 0; p < pair_cnt; p++) {
        if (dep > 1 && p < choose[dep - 1]) {
            continue;
        }
        choose[dep] = p;
        eu[m + dep - 1] = pair_u[p];  // 第 dep 条新边接在原边的后面
        ev[m + dep - 1] = pair_v[p];
        edge_total = m + need;
        dfs(dep + 1, need);
        if (answer != -1) {
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
    }
    edge_total = m;

    pair_cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            pair_u[pair_cnt] = i;
            pair_v[pair_cnt] = j;
            pair_cnt++;
        }
    }

    answer = -1;
    for (int need = 0; need <= n; need++) {
        dfs(1, need);
        if (answer != -1) {
            break;
        }
    }
    cout << answer << "\n";

    return 0;
}
