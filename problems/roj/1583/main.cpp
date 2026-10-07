/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:10
 * update_at: 2026-10-05 10:10
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 10005; // m <= 10^4

int m, n;                  // m 节点总数，n 叶子个数（节点 1..n 恰好是全部叶子）
int color[MAXN];           // color[u]：叶子 u 的 c_u，0 表示黑，1 表示白，仅 1..n 有效
vector<int> g[MAXN];       // 树的邻接表
int fa[MAXN];              // fa[u]：以 root 为根时 u 的父亲，根的 fa 为 0
int order[MAXN];           // BFS 顺序，逆序即为自底向上的树形 DP 计算顺序
// dp[u][s]：根到 u 的路径上最后一个有色节点的颜色为 s 时，u 子树全部合法所需的最少着色数
// s = 0 表示黑，s = 1 表示白，s = 2 表示路径上尚无有色节点
ll dp[MAXN][3];

// 以 root 为根建立父子关系与 BFS 顺序（迭代写法，深链也不会爆栈）
void build_order(int root) {
    int head = 0;
    int tail = 0;
    fa[root] = 0;
    order[tail] = root;
    tail++;
    while (head < tail) {
        int u = order[head];
        head++;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == fa[u]) continue; // 只有父亲这一个邻居已经访问过
            fa[v] = u;
            order[tail] = v;
            tail++;
        }
    }
}

void solve() {
    cin >> m >> n;
    for (int u = 1; u <= n; u++) {
        cin >> color[u];
    }
    for (int i = 1; i <= m - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // 题目要求根节点的度数大于 1；答案与根的选取无关，任取一个满足条件的节点作为根
    int root = 1;
    for (int u = 1; u <= m; u++) {
        if (g[u].size() > 1) {
            root = u;
            break;
        }
    }

    build_order(root);

    for (int idx = m - 1; idx >= 0; idx--) { // 逆 BFS 序：保证孩子先于父亲算完
        int u = order[idx];
        // 累加"u 不着色时，子树沿用上方颜色 s"的代价
        ll sum_black = 0;
        ll sum_white = 0;
        ll sum_none = 0;
        int child_cnt = 0; // u 的孩子个数，为 0 说明 u 是叶子
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == fa[u]) continue;
            sum_black += dp[v][0];
            sum_white += dp[v][1];
            sum_none += dp[v][2];
            child_cnt++;
        }

        if (child_cnt == 0) {
            // 叶子：上方颜色已经是 c_u 就不用着色；上方是另一种颜色或尚无颜色，都必须给它着色
            dp[u][0] = (color[u] == 0) ? 0 : 1;
            dp[u][1] = (color[u] == 1) ? 0 : 1;
            dp[u][2] = 1;
        } else {
            // 内部节点：不着色则沿用上方状态 s；着色则付 1 个代价，孩子的状态全部换成该颜色
            ll paint_black = 1 + sum_black;
            ll paint_white = 1 + sum_white;
            dp[u][0] = min(sum_black, min(paint_black, paint_white));
            dp[u][1] = min(sum_white, min(paint_black, paint_white));
            dp[u][2] = min(sum_none, min(paint_black, paint_white));
        }
    }

    cout << dp[root][2] << endl; // 根上方没有任何有色节点，入状态是"尚无"
}

int main() {
    solve();
    return 0;
}
