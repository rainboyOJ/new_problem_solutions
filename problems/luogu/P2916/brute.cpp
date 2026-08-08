// brute.cpp：枚举所有生成树，再枚举起点，直接按定义比较总时间。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 30;
const long long INF = (1LL << 60);

struct Edge {
    int u, v, len;
} edges[MAXM];

int n, p;
int cost[MAXN];
int picked[MAXM];
int deg[MAXN];
int fa[MAXN];
long long best_answer;

void init_dsu() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        deg[i] = 0;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

void unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x != y) {
        fa[x] = y;
    }
}

void check_tree(int picked_cnt) {
    if (picked_cnt != n - 1) {
        return;
    }

    init_dsu();
    long long road_sum = 0;

    for (int i = 1; i <= picked_cnt; i++) {
        Edge &e = edges[picked[i]];
        road_sum += e.len;
        deg[e.u]++;
        deg[e.v]++;
        unite(e.u, e.v);
    }

    int root = find_root(1);
    for (int i = 2; i <= n; i++) {
        if (find_root(i) != root) {
            return;
        }
    }

    long long talk_sum = 0;
    for (int i = 1; i <= n; i++) {
        talk_sum += 1LL * deg[i] * cost[i];
    }

    for (int start = 1; start <= n; start++) {
        best_answer = min(best_answer, road_sum * 2 + talk_sum + cost[start]);
    }
}

void dfs(int pos, int picked_cnt) {
    if (picked_cnt > n - 1) {
        return;
    }
    if (pos > p) {
        check_tree(picked_cnt);
        return;
    }

    picked[picked_cnt + 1] = pos;
    dfs(pos + 1, picked_cnt + 1);
    dfs(pos + 1, picked_cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }
    for (int i = 1; i <= p; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].len;
    }

    best_answer = INF;
    dfs(1, 0);
    cout << best_answer << '\n';

    return 0;
}
