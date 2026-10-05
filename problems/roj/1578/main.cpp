/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:49
 * update_at: 2026-10-05 09:49
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 节点数上限（本题 N 远小于此，留足余量）
vector<int> g[MAXN];     // g[u] 存与节点 u 相邻的所有节点，无向树双向加边
int parent_node[MAXN];   // parent_node[u]：以 root 为根时 u 的父亲，根的父亲记为 -1
int order[MAXN];         // 自顶向下的遍历顺序（正序为拓扑序，逆序即自底向上）
int stk[MAXN];           // 手动栈，替代递归 DFS，避免深树爆栈
int in_degree[MAXN];     // 输入中每条边只出现一次，入度为 0 的节点即为树根
ll dp0[MAXN];            // dp0[u]：u 不放士兵时，覆盖 u 子树内所有边的最少士兵数
ll dp1[MAXN];            // dp1[u]：u 放士兵时，覆盖 u 子树内所有边的最少士兵数

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int u, k;
        scanf("%d %d", &u, &k);
        for (int j = 0; j < k; j++) {
            int v;
            scanf("%d", &v);
            g[u].push_back(v);
            g[v].push_back(u);
            in_degree[v]++;
        }
    }

    // 输入给出的边由父指向子且每条边只出现一次，入度为 0 的节点就是树根
    int root = 0;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            root = i;
            break;
        }
    }

    // 显式栈做一遍 DFS，得到自顶向下的访问顺序
    for (int i = 0; i < n; i++) {
        parent_node[i] = -1;
    }
    int top = 0;
    stk[top++] = root;
    int order_cnt = 0;
    while (top > 0) {
        int u = stk[--top];
        order[order_cnt++] = u;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_node[u]) {
                continue;
            }
            parent_node[v] = u;
            stk[top++] = v;
        }
    }

    // dp 初值：不选 u 至少要 0 人；选 u 则先记上 u 自己这 1 名士兵
    for (int i = 0; i < n; i++) {
        dp0[i] = 0;
        dp1[i] = 1;
    }

    // 逆拓扑序自底向上转移：
    // u 不选时，边 (u, v) 只能靠 v 覆盖，故子节点必须全选，取 dp1[v]；
    // u 选时，子节点 v 可选可不选，取 min(dp0[v], dp1[v])。
    for (int idx = order_cnt - 1; idx >= 0; idx--) {
        int u = order[idx];
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_node[u]) {
                continue;
            }
            dp0[u] += dp1[v];
            dp1[u] += min(dp0[v], dp1[v]);
        }
    }

    printf("%lld\n", min(dp0[root], dp1[root]));
    return 0;
}
