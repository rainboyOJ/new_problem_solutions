#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
const int MAXM = 2000000 + 5;

static int n;
static int head[MAXN];
static int to[MAXM];
static int nxt[MAXM];
static int weight_arr[MAXM];
static int edge_cnt;

static int parent_arr[MAXN];
static int parent_weight[MAXN];
static int subtree_size[MAXN];
static int order_arr[MAXN];
static int stack_arr[MAXN];

void add_edge(int u, int v, int w) {
    ++edge_cnt;
    to[edge_cnt] = v;
    weight_arr[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int top = 0;
    int order_cnt = 0;
    stack_arr[++top] = 1;
    parent_arr[1] = 0;

    // 先用迭代 DFS 建出父子关系与访问顺序，避免深递归爆栈。
    while (top > 0) {
        int u = stack_arr[top--];
        order_arr[++order_cnt] = u;

        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (v == parent_arr[u]) {
                continue;
            }
            parent_arr[v] = u;
            parent_weight[v] = weight_arr[e];
            stack_arr[++top] = v;
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        subtree_size[i] = 1;
    }

    // 逆序回推子树大小，并统计每条父边的贡献。
    for (int i = order_cnt; i >= 2; --i) {
        int u = order_arr[i];
        long long diff = llabs(1LL * n - 2LL * subtree_size[u]);
        ans += 1LL * parent_weight[u] * diff;
        subtree_size[parent_arr[u]] += subtree_size[u];
    }

    cout << ans << '\n';
    return 0;
}
