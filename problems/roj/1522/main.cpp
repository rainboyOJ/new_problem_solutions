/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:05
 * update_at: 2026-10-05 06:05
 */

// 灾区即无向图的割点：一次 Tarjan DFS 维护 dfn/low，
// 非根点存在孩子 low >= dfn，或根在 DFS 树里有 >= 2 棵子树，即为灾区。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 20005; // N < 100，边数最多约 99*98/2，开两倍余量

typedef long long ll;

int n, m_cnt;          // m_cnt：当前块的边表长度
int head[MAXN];        // head[u]：u 的第一条边在边表中的编号，0 表示没有
int nxt[MAXM], to_[MAXM]; // 链式前向星：同起点的下一条边、这条边指向的点

int dfn[MAXN];       // dfn[u]：DFS 访问序号，0 表示未访问
int low[MAXN];       // low[u]：u 的子树内经回边能到达的最小 dfn
bool is_cut[MAXN];   // is_cut[u]：u 是否为灾区（割点）
int timer_cnt;       // DFS 时间戳，从 1 开始，0 留给"未访问"

// 加一条 u -> v 的有向边；无向边要正反各加一次。
void add_edge(int u, int v) {
    m_cnt++;
    to_[m_cnt] = v;
    nxt[m_cnt] = head[u];
    head[u] = m_cnt;
}

// Tarjan 求割点：father == 0 表示 u 是当前 DFS 树的根。
void dfs(int u, int father) {
    timer_cnt++;
    dfn[u] = low[u] = timer_cnt;
    int children = 0; // u 在 DFS 树中的子树数（只对根判据有用）

    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to_[i];
        if (v == father) continue; // 无向图唯一的父边不算回边
        if (dfn[v] != 0) {
            // 回边：v 是祖先，用它的 dfn 压低 low[u]
            if (dfn[v] < low[u]) low[u] = dfn[v];
        } else {
            children++;
            dfs(v, u);
            if (low[v] < low[u]) low[u] = low[v];
            // 孩子 v 的子树绕不开 u 回到 u 的祖先：删掉 u 后 v 那块必然断开
            // 注意 father != 0：根的判据单独处理
            if (father != 0 && low[v] >= dfn[u]) is_cut[u] = true;
        }
    }

    // 根没有祖先，看子树数：>= 2 棵子树时删根至少剩两块
    if (father == 0 && children > 1) is_cut[u] = true;
}

// 处理一组数据：建图 + 求割点数量并输出。
void solve() {
    m_cnt = 0;
    timer_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        dfn[i] = 0;
        is_cut[i] = false;
    }

    // 每行 "u v1 v2 ..." 描述 u 的全部邻居；每条边至少在某一行出现一次，
    // 同一条边可能重复出现，这里直接重复登记，不影响割点判定。
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        int first;
        if (!(iss >> first)) continue; // 跳过空行（含上一行 N 后残留的换行）
        if (first == 0) break;         // 单独一行 0 结束本块
        int v;
        while (iss >> v) { // 无向边：双向登记
            add_edge(first, v);
            add_edge(v, first);
        }
    }

    ll ans = 0; // 题目数据默认 ll
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) dfs(i, 0); // 图保证连通；逐点开搜兜底非连通
    }
    for (int i = 1; i <= n; i++) {
        if (is_cut[i]) ans++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 每组第一行是 N，最后的单独 0 结束输入；N 之后改用 getline 读整行邻居表
    while (cin >> n && n != 0) {
        solve();
    }

    return 0;
}
