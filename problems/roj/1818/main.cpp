/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:36
 * update_at: 2026-10-08 06:36
 */

// 树形博弈 DP（minimax + 双关键字字典序）
//   结点 u 由谁取，只看它到根的深度奇偶：偶数层（根为第 0 层）Alice 取，
//   奇数层 Bob 取；取完 u 之后由**对手**在 u 的儿子里挑一个继续。
//   记 f(u) = (bob[u], alice[u]) 为从 u 取到叶子这一段里两人的得分。
//     偶数层 u：Alice 取 num[u]，Bob 挑儿子 v* = argmax (bob[v], -alice[v])
//               （先让自己多，再让 Alice 少）→ alice[u]=num[u]+alice[v*], bob[u]=bob[v*]
//     奇数层 u：Bob 取 num[u]，Alice 挑儿子 v* = argmin (bob[v], -alice[v])
//               （先让 Bob 少，再让自己多）→ bob[u]=num[u]+bob[v*], alice[u]=alice[v*]
//   num[u] 对 u 的所有儿子分支是同一个常数，故选择只由儿子的 f 决定，可自底向上合并。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 200005; // 无向存边，最多 2*(n-1) 条

typedef long long ll;

ll n;
ll num[MAXN]; // 第 i 堆的石子数

int head[MAXN];                 // 链式前向星
int to[MAXM], nxt[MAXM], ecnt;  // 无向边存储

int indeg[MAXN]; // 入度：有向树上入度为 0 的结点就是根（它就是被 Alice 先取的那个点）
int par[MAXN];   // BFS 的父结点
int dep[MAXN];   // 到根的深度，根的深度为 0
int order[MAXN]; // BFS 序：父亲一定排在儿子前面
int ocnt;

ll alice[MAXN]; // 子树内 Alice 在双方最优策略下的得分
ll bob[MAXN];   // 子树内 Bob 在双方最优策略下的得分

// 加一条无向边（题面给的是 u 是 v 的父亲，但无向遍历对方向更宽容）
void add_edge(int u, int v) {
    ecnt++;
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
        indeg[v]++;
    }
}

void solve() {
    // 迭代 BFS 定序：n = 1e5 的链不许递归，队列就是 order 数组本身
    int root = 1;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            root = i;
            break;
        }
    }

    ocnt = 1;
    order[1] = root;
    par[root] = 0;
    dep[root] = 0;
    for (int i = 1; i <= ocnt; i++) {
        int u = order[i];
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (v == par[u]) continue; // 不回走父结点
            par[v] = u;
            dep[v] = dep[u] + 1;
            ocnt++;
            order[ocnt] = v;
        }
    }

    // 逆 BFS 序做 DP：儿子先算完
    for (int i = ocnt; i >= 1; i--) {
        int u = order[i];
        int best = 0;
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (v == par[u]) continue;
            if (best == 0) {
                best = v;
                continue;
            }
            if (dep[u] % 2 == 0) {
                // 这一层的选择权在 Bob：先 bob 大，再 alice 小
                if (bob[v] > bob[best] || (bob[v] == bob[best] && alice[v] < alice[best]))
                    best = v;
            } else {
                // 这一层的选择权在 Alice：先 bob 小，再 alice 大
                if (bob[v] < bob[best] || (bob[v] == bob[best] && alice[v] > alice[best]))
                    best = v;
            }
        }

        if (dep[u] % 2 == 0) {
            // Alice 取走 num[u]；best == 0 说明 u 是叶子，对手没有可选的儿子
            alice[u] = num[u] + (best == 0 ? 0 : alice[best]);
            bob[u] = (best == 0 ? 0 : bob[best]);
        } else {
            bob[u] = num[u] + (best == 0 ? 0 : bob[best]);
            alice[u] = (best == 0 ? 0 : alice[best]);
        }
    }

    cout << alice[root] << " " << bob[root] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
