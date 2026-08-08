#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举所有点对，用根到点异或值计算路径异或。

const int MAXN = 505;

int n;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
unsigned int weight_edge[MAXN * 2];
unsigned int xor_root[MAXN];

void add_edge(int u, int v, unsigned int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_edge[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dfs(int u, int parent) {
    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (v == parent) {
            continue;
        }
        xor_root[v] = xor_root[u] ^ weight_edge[i];
        dfs(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        unsigned int w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dfs(1, 0);

    unsigned int answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            answer = max(answer, xor_root[i] ^ xor_root[j]);
        }
    }
    cout << answer << '\n';

    return 0;
}
