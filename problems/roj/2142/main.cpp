/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 11:30
 * update_at: 2026-10-12 14:55
 */
// main.cpp：自底向上贪心求树的最大匹配——儿子都决策完后，u 与父亲都还空着就配掉父边。
//
// 一个结点的两个字段聚合成 struct Node：父亲编号、是否已被匹配边占用，
// 对应 fa[] / matched[] 两个平行数组，这里按结点下标收进 node[u]。
// order[] 兼作显式 BFS 队列，倒着扫一遍就得到"儿子先于父亲"的后序效果，
// 全程不递归：n = 2e5 的链形数据也不会爆栈。

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int maxn = 200005; // 题面 n ≤ 2e5

struct Node {
    int fa;       // 父亲编号，根的父亲是 0
    bool matched; // 是否已经被某条匹配边占用
};

Node node[maxn];     // node[u]：编号 u 的结点
vector<int> g[maxn]; // g[u]：u 的邻接表（无向树）
int order[maxn];     // BFS 序兼队列：order[i] 是第 i 个出队的结点，父亲一定排在儿子前面
int n;               // 结点数
ll ans;              // 匹配边数

// 加一条无向边：树边两个方向都要存，BFS 时才走得通
void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

// 读入建树：n-1 条边
void read_tree() {
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b);
    }
}

// BFS 求"父亲先于儿子"的序：order 兼作队列，head 是队首
void bfs_order() {
    int head = 0, tail = 0;
    order[tail++] = 1;
    node[1].fa = 0; // 以 1 为根
    while (head < tail) {
        int u = order[head++];
        for (int v : g[u]) {
            if (v == node[u].fa) {
                continue; // 树上唯一的已访邻点就是父亲
            }
            node[v].fa = u;
            order[tail++] = v;
        }
    }
}

// 自底向上贪心：倒着扫 BFS 序，u 被处理时它的所有儿子都已决策完。
// u 与父亲都还空着就配 (u, fa[u])：交换论证保证这样不会比最优解差
void greedy_match() {
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        int p = node[u].fa;
        if (p != 0 && !node[u].matched && !node[p].matched) {
            node[u].matched = true;
            node[p].matched = true;
            ans++;
        }
    }
}

void solve() {
    read_tree();
    bfs_order();
    greedy_match();
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    if (!(cin >> n)) {
        return 0; // 空输入直接退出
    }
    solve();
    return 0;
}
