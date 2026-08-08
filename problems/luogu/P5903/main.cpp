#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;

const int MAXN = 500005;
const int LOG = 20;

int n, q;
ui seed_value;
int parent_node[MAXN];
int head[MAXN], to[MAXN], nxt[MAXN], edge_cnt;
int depth_node[MAXN];
int up[MAXN][LOG + 1];
int root_node;

ui get(ui x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    seed_value = x;
    return seed_value;
}

void add_child(int parent, int child) {
    edge_cnt++;
    to[edge_cnt] = child;
    nxt[edge_cnt] = head[parent];
    head[parent] = edge_cnt;
}

void read_input() {
    cin >> n >> q >> seed_value;
    for (int i = 1; i <= n; i++) {
        cin >> parent_node[i];
        if (parent_node[i] == 0) {
            root_node = i;
        } else {
            add_child(parent_node[i], i);
        }
    }
}

void build_ancestor() {
    queue<int> que;
    depth_node[root_node] = 1;
    up[root_node][0] = 0;
    que.push(root_node);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int j = 1; j <= LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            depth_node[v] = depth_node[u] + 1;
            up[v][0] = u;
            que.push(v);
        }
    }
}

int kth_ancestor(int x, int k) {
    for (int j = 0; j <= LOG; j++) {
        if ((k & (1 << j)) != 0) {
            x = up[x][j];
        }
    }
    return x;
}

void solve() {
    build_ancestor();

    int last_answer = 0;
    unsigned long long final_answer = 0;

    for (int i = 1; i <= q; i++) {
        int x = (int)(((get(seed_value) ^ (ui)last_answer) % (ui)n) + 1);
        int k = (int)((get(seed_value) ^ (ui)last_answer) % (ui)depth_node[x]);
        int current_answer = kth_ancestor(x, k);
        last_answer = current_answer;
        final_answer ^= 1ULL * (unsigned int)i * (unsigned int)current_answer;
    }

    cout << final_answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
