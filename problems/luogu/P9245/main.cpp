/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:38
 * update_at: 2026-10-03 11:38
 */
// P9245 [蓝桥杯 2023 省 B] 景区导游
// 思路：
//   1. 这是一棵树，两点之间只有一条路径，所以“从 u 到 v 花多少时间”就是
//      dist[u] + dist[v] - 2 * dist[lca(u, v)]，其中 dist[x] 是根到 x 的距离。
//   2. 原路线总时间 total 是相邻两点的距离之和；跳过 A[i] 只是把两段相邻距离
//      a[i-1] -> a[i] 和 a[i] -> a[i+1] 合并成一段 a[i-1] -> a[i+1]，
//      所以答案 = total - d(a[i-1],a[i]) - d(a[i],a[i+1]) + d(a[i-1],a[i+1])。
//   3. 总时间 total 加上首/中/尾三种情况下的增量，就得到每个答案；
//      全程只需要 O(K) 次 LCA 询问，每次 O(log N)。
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 景点数上限
const int MAXM = 200005; // 无向边数上限（每条边存正反两条）
const int LOG = 20;      // 2^20 > 10^5，足够跳到根

int n, k;
int a[MAXN]; // 原定游览线路 A[1..K]

// 链式前向星存树
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
ll wt[MAXM]; // 每条边的摆渡时间

int depth[MAXN];       // 根到该点的边数
ll dist[MAXN];         // 根到该点的路径长度
int up[MAXN][LOG + 1]; // up[x][j]：x 向上跳 2^j 步到达的祖先

// 加一条无向边：u <-> v，花费时间 w。
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    to[edge_cnt] = v;
    wt[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> k;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        ll t;
        cin >> u >> v >> t;
        add_edge(u, v, t);
        add_edge(v, u, t);
    }
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }
}

// 以 1 号景点为根，BFS 求出 depth、dist 和 up[x][0]。
// 用队列而不是递归，避免 n = 10^5 的链把栈撑爆。
void build_root() {
    for (int i = 1; i <= n; i++) {
        depth[i] = -1;
    }
    queue<int> q;
    depth[1] = 0;
    dist[1] = 0;
    up[1][0] = 1; // 根的祖先设成自己，越界也不会跳出去
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (depth[v] != -1) continue;
            depth[v] = depth[u] + 1;
            dist[v] = dist[u] + wt[i];
            up[v][0] = u;
            q.push(v);
        }
    }
}

// 预处理倍增表：up[x][j] 表示 x 向上跳 2^j 步的祖先。
void build_lift() {
    for (int j = 1; j <= LOG; j++) {
        for (int x = 1; x <= n; x++) {
            up[x][j] = up[up[x][j - 1]][j - 1];
        }
    }
}

// 把 x 向上提 d 步。
int jump_up(int x, int d) {
    for (int j = 0; j <= LOG; j++) {
        if ((d >> j) & 1) {
            x = up[x][j];
        }
    }
    return x;
}

// 倍增求最近公共祖先。
int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    u = jump_up(u, depth[u] - depth[v]);

    if (u == v) return u;

    // 从大步到小步一起爬，直到两人的父亲相同。
    for (int j = LOG; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

// 树上从 u 到 v 的唯一路径长度。
ll path_len(int u, int v) {
    int w = lca(u, v);
    return dist[u] + dist[v] - 2 * dist[w];
}

void solve() {
    build_root();
    build_lift();

    // 原路线的总时间：相邻两点距离之和。
    ll total = 0;
    for (int i = 1; i <= k - 1; i++) {
        total += path_len(a[i], a[i + 1]);
    }

    for (int i = 1; i <= k; i++) {
        if (i == 1) {
            // 跳过第一个点，只要去掉第一段。
            cout << total - path_len(a[1], a[2]);
        } else if (i == k) {
            // 跳过最后一个点，只要去掉最后一段。
            cout << total - path_len(a[k - 1], a[k]);
        } else {
            // 中间的点：两段合并成一段。
            ll erase_two = path_len(a[i - 1], a[i]) + path_len(a[i], a[i + 1]);
            ll add_one = path_len(a[i - 1], a[i + 1]);
            cout << total - erase_two + add_one;
        }
        if (i != k) cout << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
