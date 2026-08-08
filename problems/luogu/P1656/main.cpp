#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 4005;

struct EdgeAnswer {
    int u, v;

    bool operator<(const EdgeAnswer &other) const {
        if (u != other.u) {
            return u < other.u;
        }
        return v < other.v;
    }
};

int n, m;

// 链式前向星存图。
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

// Tarjan 求桥时使用的时间戳。
int dfn[MAXN], low[MAXN], dfs_clock;

vector<EdgeAnswer> answer;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 由于这里的边编号从 1 开始，所以一对反向边分别是 (1,2)、(3,4) ...
// 这个函数返回某条边对应的反向边编号。
int reverse_edge(int id) {
    if (id & 1) {
        return id + 1;
    }
    return id - 1;
}

// u: 当前点
// in_edge: 进入 u 的那条边的编号
// 不能简单写成 v != fa，因为无向图里可能有重边。
void tarjan(int u, int in_edge) {
    dfn[u] = low[u] = ++dfs_clock;

    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];

        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);

            // 如果 v 子树回不到 u 或 u 的祖先，那么 u-v 就是桥。
            if (low[v] > dfn[u]) {
                int a = u;
                int b = v;
                if (a > b) {
                    swap(a, b);
                }
                answer.push_back({a, b});
            }
        }
        else if (i != reverse_edge(in_edge)) {
            // 这里遇到的是返祖边，用祖先的 dfn 更新 low。
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, -1);
        }
    }

    sort(answer.begin(), answer.end());
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i].u << ' ' << answer[i].v << '\n';
    }

    return 0;
}
