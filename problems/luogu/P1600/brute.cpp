// brute.cpp：对每个玩家真实沿路径跑一遍，记录在每个点的到达时间。
// 如果到达时间恰好等于观察员时间，就给该点答案加一。只适合小数据对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int LOG = 6;

int n, m;
vector<int> g[MAXN];
int w[MAXN];
int parent_arr[MAXN];
int depth_arr[MAXN];
int up[MAXN][LOG];
int answer[MAXN];

// 非递归建树，求父亲、深度和倍增祖先。
void build_tree() {
    vector<int> st;
    st.push_back(1);
    parent_arr[1] = 0;
    depth_arr[1] = 0;
    for (int j = 0; j < LOG; j++) {
        up[1][j] = 1;
    }

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_arr[u]) {
                continue;
            }

            parent_arr[v] = u;
            depth_arr[v] = depth_arr[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < LOG; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            st.push_back(v);
        }
    }
}

int kth_ancestor(int u, int k) {
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {
            u = up[u][j];
        }
    }
    return u;
}

int lca(int a, int b) {
    if (depth_arr[a] < depth_arr[b]) {
        swap(a, b);
    }

    a = kth_ancestor(a, depth_arr[a] - depth_arr[b]);
    if (a == b) {
        return a;
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}

// 真正模拟一个玩家从 s 跑到 t 的全过程。
void simulate_runner(int s, int t) {
    int p = lca(s, t);
    int tm = 0;

    // 先沿着 s -> lca 往上跑。
    int x = s;
    while (x != p) {
        if (w[x] == tm) {
            answer[x]++;
        }
        tm++;
        x = parent_arr[x];
    }

    if (w[p] == tm) {
        answer[p]++;
    }

    // 再按正向顺序走 lca -> t 这一段。
    vector<int> down;
    int y = t;
    while (y != p) {
        down.push_back(y);
        y = parent_arr[y];
    }
    reverse(down.begin(), down.end());

    for (size_t i = 0; i < down.size(); i++) {
        tm++;
        if (w[down[i]] == tm) {
            answer[down[i]]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        w[i] = 0;
        answer[i] = 0;
        parent_arr[i] = 0;
        depth_arr[i] = 0;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_tree();

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for (int i = 1; i <= m; i++) {
        int s, t;
        cin >> s >> t;
        simulate_runner(s, t);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';

    return 0;
}
