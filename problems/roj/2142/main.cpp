// Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
// rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
// rainboy的学习导航网站: https://idx.roj.ac.cn
// create_at: 2026-10-07 11:30
// update_at: 2026-10-07 11:30
//
// ROJ 2142《树边匹配》
// 题意：给定一棵 n 个节点的树，选出尽量多的边，使每个节点至多是其中一条边的端点
//       （即树的最大匹配，Maximum Matching on Tree），输出边数。
//
// 做法：自底向上贪心。把树以 1 为根，按层序（BFS）拿到「父亲先于儿子」的顺序 order，
//   再把 order 倒过来处理 —— 于是每个节点被处理时，它的所有儿子都已经决策完毕。
//   处理 u 时：若 u 与它的父亲 p 都还没被占用，就直接把边 (u, p) 计入匹配。
//   正确性：任一被处理到的节点 u，其子树内部的匹配已经全部结束；若此时 u 与 p 都空着，
//   把 (u, p) 配上不会比让 u 空着更差（u 空着只能把它让给某条子树外的边，收益同为 1，
//   而配 (u, p) 的同时不占用 p 的任何其他邻点以外的资源，交换论证即可）。这与
//   「叶节点优先」的经典树上最大匹配贪心等价。
//
//   为规避 n = 2e5 的链形数据爆递归栈，全程不使用递归 DFS，用显式数组模拟。
//
// 复杂度：时间 O(n)，空间 O(n)。

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 200005;  // n 的上限 2e5，留一点余量

int n;                    // 节点数
vector<int> adj[MAXN];    // 邻接表（无向树）
int parent_[MAXN];        // 每个节点的父节点，根的父记作 0（哨兵）
bool matched[MAXN];       // 该节点是否已经被某条匹配边占用
int order_[MAXN];         // BFS 访问序：父亲一定排在儿子前面

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (n <= 1) {                 // 只有一个节点：一条边都没有
        cout << 0 << "\n";
        return 0;
    }

    // 迭代 BFS 取得「父亲先于儿子」的序
    int head = 0, tail = 0;       // order_ 的队首 / 队尾
    order_[tail++] = 1;
    parent_[1] = 0;
    while (head < tail) {
        int u = order_[head++];
        for (int v : adj[u]) {
            if (v == parent_[u]) continue;   // 树上唯一的已访邻点就是父亲
            parent_[v] = u;
            order_[tail++] = v;
        }
    }

    // 倒序处理：每个节点被处理时儿子已全部决策完毕
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        int u = order_[i];
        int p = parent_[u];
        if (p != 0 && !matched[u] && !matched[p]) {   // u 与父亲都还空着
            matched[u] = true;
            matched[p] = true;
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
