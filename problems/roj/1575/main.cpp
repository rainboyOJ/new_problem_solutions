/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:48
 * update_at: 2026-10-06 00:48
 */

#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const int MAXQ = 105;

int n, q;

// children[u][0] = (左子节点, 边权); children[u][1] = (右子节点, 边权)
// 叶子节点对应的 children 为空
vector<pair<int, int> > children[MAXN];

// dp[u][k] 表示以 u 为根的子树中保留 k 条边能获得的最大苹果数
int dp[MAXN][MAXQ];

// 构建以根节点 1 为起点的有向二叉树
void build_tree() {
    // 用邻接表读取无向边
    vector<pair<int, int> > adj[MAXN];
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    // 从根节点 1 开始 BFS，把子节点加入 children
    int queue[MAXN];
    int head = 0, tail = 0;
    bool visited[MAXN] = {false};
    visited[1] = true;
    queue[tail++] = 1;
    while (head < tail) {
        int u = queue[head++];
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (!visited[v]) {
                visited[v] = true;
                children[u].push_back(make_pair(v, w));
                queue[tail++] = v;
            }
        }
    }
}

// 树形背包 DFS：计算以 u 为根的子树保留 k 条边的最大权值
int dfs(int u, int k) {
    if (k == 0 || children[u].empty()) {
        return 0;
    }
    if (dp[u][k] != -1) {
        return dp[u][k];
    }

    int l = children[u][0].first;
    int wl = children[u][0].second;
    int r = children[u][1].first;
    int wr = children[u][1].second;

    int res = 0;

    // 只保留左子树：必须选边 (u, l)
    res = max(res, dfs(l, k - 1) + wl);
    // 只保留右子树：必须选边 (u, r)
    res = max(res, dfs(r, k - 1) + wr);

    // 左右子树都保留：两条边必选，剩余 k-2 条边在左右子树之间分配
    for (int i = 0; i <= k - 2; i++) {
        res = max(res, dfs(l, i) + wl + dfs(r, k - 2 - i) + wr);
    }

    dp[u][k] = res;
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    build_tree();

    // 初始化记忆化数组
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= q; j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n", dfs(1, q));
    return 0;
}
